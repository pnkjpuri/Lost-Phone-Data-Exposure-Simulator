# app.py
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
    target_dir = data.get("dir", "mock_phone")
    hide_notifs = data.get("hide_notifs", False)
    enable_fde = data.get("enable_fde", False)
    app_lock = data.get("app_lock", False)

    exe_path = os.path.join(os.getcwd(), "simulator.exe")
    
    cmd = [exe_path, target_dir]
    if hide_notifs: cmd.append("--hide-notifs")
    if enable_fde: cmd.append("--enable-fde")
    if app_lock: cmd.append("--app-lock")

    try:
        result = subprocess.run(cmd, capture_output=True, text=True, check=True)
        response_data = json.loads(result.stdout)
        return jsonify(response_data)
    except Exception as e:
        return jsonify({"error": "C Engine Execution Failed", "details": str(e)}), 500

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=5000, debug=True)