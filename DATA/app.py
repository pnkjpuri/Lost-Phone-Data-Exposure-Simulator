from flask import Flask, render_template, jsonify, request
import subprocess
import json
import os

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/api/simulate", methods=["POST"])
def simulate():
    data = request.json or {}
    hide_notifs = data.get("hide_notifs", False)
    app_lock = data.get("app_lock", False)
    enable_fde = data.get("enable_fde", False)
    sim_pin = data.get("sim_pin", False)
    remote_wipe = data.get("remote_wipe", False)
    time_min = data.get("time_min", 0)
    threat = data.get("threat", "casual")

    exe_path = os.path.join(os.getcwd(), "simulator.exe")

    cmd = [exe_path]
    if hide_notifs: cmd.append("--hide-notifs")
    if app_lock: cmd.append("--app-lock")
    if enable_fde: cmd.append("--enable-fde")
    if sim_pin: cmd.append("--sim-pin")
    if remote_wipe: cmd.append("--remote-wipe")
    if threat == "thief": cmd.append("--thief")
    cmd.append(f"--time={time_min}")

    try:
        result = subprocess.run(cmd, capture_output=True, text=True, check=True)
        response_data = json.loads(result.stdout)
        return jsonify(response_data)
    except Exception as e:
        return jsonify({"error": "C Engine Failure", "details": str(e)}), 500

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=5000, debug=True)