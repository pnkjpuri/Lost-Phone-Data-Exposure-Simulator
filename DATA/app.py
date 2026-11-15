import json
import os
import subprocess
from flask import Flask, jsonify, render_template, request

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/simulate', methods=['POST'])
def simulate():
    data = request.get_json(silent=True) or {}
    
    hide_notifs = bool(data.get('hide_notifs', False))
    app_lock = bool(data.get('app_lock', False))
    enable_fde = bool(data.get('enable_fde', False))
    sim_pin = bool(data.get('sim_pin', False))
    remote_wipe = bool(data.get('remote_wipe', False))

    # Build CLI flags for the C binary
    exe_name = "simulator.exe" if os.name == 'nt' else "simulator"
    exe_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), exe_name)
    
    cmd = [exe_path]
    if hide_notifs: cmd.append("--hide-notifs")
    if app_lock: cmd.append("--app-lock")
    if enable_fde: cmd.append("--enable-fde")
    if sim_pin: cmd.append("--sim-pin")
    if remote_wipe: cmd.append("--remote-wipe")

    c_output = {}
    if os.path.exists(exe_path):
        try:
            res = subprocess.run(cmd, capture_output=True, text=True, check=True)
            c_output = json.loads(res.stdout)
        except Exception as e:
            print("C Engine Execution Error:", e)

    # Calculate deterministic fallback/verified metrics if C binary returns older keys
    identity_exp = 85
    financial_exp = 95
    cloud_exp = 70

    if hide_notifs:
        identity_exp -= 25
        financial_exp -= 30
    if app_lock:
        financial_exp -= 30
        cloud_exp -= 35
    if sim_pin:
        identity_exp -= 20
        financial_exp -= 25
    if enable_fde:
        identity_exp -= 20
        cloud_exp -= 20
    if remote_wipe:
        identity_exp = 5
        financial_exp = 5
        cloud_exp = 5

    identity_exp = max(5, identity_exp)
    financial_exp = max(5, financial_exp)
    cloud_exp = max(5, cloud_exp)

    overall_score = c_output.get('exposure_score')
    if overall_score is None:
        overall_score = int((identity_exp + financial_exp + cloud_exp) / 3)

    attack_path = c_output.get('attack_path')
    if not attack_path:
        if remote_wipe:
            attack_path = ["Remote Find/Wipe Active: Device Erased & All Attack Paths Severed"]
        elif hide_notifs and app_lock and sim_pin and enable_fde:
            attack_path = ["All Vectors Hardened: Attack Path Blocked (Cost: INF)"]
        elif not hide_notifs and not sim_pin:
            attack_path = [
                "Step 1: Physical Lockscreen Access (0s)",
                "Step 2: Read Bank SMS OTP Preview (10s)",
                "Step 3: SIM Swap / Primary Email 2FA Reset (20s)",
                "Step 4: Complete Financial & Cloud Takeover (15s)"
            ]
        elif not app_lock:
            attack_path = [
                "Step 1: Physical Lockscreen / App Access (0s)",
                "Step 2: Open Unprotected Notes & Banking Apps (15s)",
                "Step 3: Extract Stored PINs & Hijack Session (10s)"
            ]
        else:
            attack_path = [
                "Step 1: Physical Hardware Possession (0s)",
                "Step 2: Unencrypted Storage Extraction via USB (25s)",
                "Step 3: Offline Token & Session Replay (20s)"
            ]

    ranked_assets = c_output.get('ranked_assets')
    if ranked_assets is None:
        ranked_assets = []
        if financial_exp > 20:
            ranked_assets.append({"name": "Bank OTP & UPI Apps", "score": financial_exp, "domain": "Financial"})
        if identity_exp > 20:
            ranked_assets.append({"name": "Identity & Passport Scans", "score": identity_exp, "domain": "Identity"})
        if cloud_exp > 20:
            ranked_assets.append({"name": "Email & Cloud OAuth Sessions", "score": cloud_exp, "domain": "Work/Cloud"})
        ranked_assets.sort(key=lambda x: x['score'], reverse=True)

    return jsonify({
        "exposure_score": overall_score,
        "attack_time_seconds": c_output.get("attack_time_seconds", 45),
        "domains": c_output.get("domains", {
            "identity": identity_exp,
            "financial": financial_exp,
            "cloud": cloud_exp
        }),
        "attack_path": attack_path,
        "ranked_assets": ranked_assets
    })

if __name__ == '__main__':
    app.run(debug=True)