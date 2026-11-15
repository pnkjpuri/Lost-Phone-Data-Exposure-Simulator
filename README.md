# 🛡️ PhoneShield — Lost Phone Data Exposure Simulator

![C](https://img.shields.io/badge/Core_Engine-ANSI_C_(GCC)-00599C?style=for-the-badge&logo=c&logoColor=white)
![Python](https://img.shields.io/badge/Backend-Python_Flask-3776AB?style=for-the-badge&logo=python&logoColor=white)
![Frontend](https://img.shields.io/badge/UI-Tailwind_CSS_%26_Chart.js-06B6D4?style=for-the-badge&logo=tailwindcss&logoColor=white)
![Domain](https://img.shields.io/badge/Focus-Cybersecurity_%26_SOC_Simulation-F43F5E?style=for-the-badge)

**PhoneShield** is an interactive cybersecurity threat-modeling and Security Operations Center (SOC) simulation platform designed to quantify and visualize the real-world blast radius of a lost, stolen, or unattended smartphone.

By combining a low-level **ANSI C data structures engine** (Hash Tables, Dijkstra’s Shortest Path Graph, and a Max-Heap Priority Queue) with a **live interactive web dashboard**, PhoneShield demonstrates how device-level misconfigurations—such as exposed lockscreen SMS OTPs, unencrypted local storage, and unlocked sessions—chain together into full identity and financial compromise within seconds.

---

## 📑 Table of Contents
1. [System Architecture](#-system-architecture)
2. [Core Data Structures & Algorithms (ANSI C)](#-core-data-structures--algorithms-ansi-c)
3. [Dashboard Modules & Capabilities](#-dashboard-modules--capabilities)
4. [Security Controls & Attack Vector Matrix](#-security-controls--attack-vector-matrix)
5. [Project Structure](#-project-structure)
6. [Installation & Local Setup](#-installation--local-setup)
7. [API Specification](#-api-specification)

---

## 🏗️ System Architecture

PhoneShield decouples its analytical core from its presentation layer so that all risk calculations, graph traversals, and asset rankings execute natively in C before streaming JSON telemetry to the browser:

```text
┌────────────────────────────────────────────────────────────────────────────┐
│                        FRONTEND (SOC Web Dashboard)                        │
│  • Virtual Smartphone Sandbox   • Dynamic Domain Exposure Reports          │
│  • Live Telemetry Stream        • Chart.js Analytics & JSON/PDF Export     │
└─────────────────────────────────────┬──────────────────────────────────────┘
                                      │ POST /api/simulate (JSON Controls)
                                      ▼
┌────────────────────────────────────────────────────────────────────────────┐
│                        BACKEND API (Python / Flask)                        │
│  • Sanitizes toggle states      • Invokes compiled C binary via subprocess │
└─────────────────────────────────────┬──────────────────────────────────────┘
                                      │ CLI Args / Stdin State Flags
                                      ▼
┌────────────────────────────────────────────────────────────────────────────┐
│                     CORE SIMULATION ENGINE (ANSI C)                        │
│  [1] Hash Table      ──► O(1) lookup of active security defenses           │
│  [2] Weighted Graph  ──► Dijkstra's shortest compromise path & time (sec)  │
│  [3] Max-Heap        ──► Priority queue ranking of highest-risk assets     │
└────────────────────────────────────────────────────────────────────────────┘
```

---

## ⚙️ Core Data Structures & Algorithms (ANSI C)

| Data Structure | Role in PhoneShield | Time Complexity | Operational Impact |
| :--- | :--- | :--- | :--- |
| **Hash Table** | Stores the active state (`ENABLED` / `DISABLED`) of all 5 device security controls (`hide_notifs`, `app_lock`, `enable_fde`, `sim_pin`, `remote_wipe`). | $O(1)$ Average Lookup | Instantly evaluates whether a defensive barrier exists before calculating edge weights in the attack graph. |
| **Directed Weighted Graph (Dijkstra)** | Models attack progression from initial physical entry (`Unlocked Screen`) through lateral pivots (`SMS OTP`, `Primary Gmail`) to critical targets (`Bank Reset`). | $O((V + E) \log V)$ | Dynamically recalculates the **Shortest Compromise Path** and estimated breach time (`45s` vs. `Path Blocked`) as controls are toggled. |
| **Max-Heap (Priority Queue)** | Maintains exposed digital assets sorted strictly by their calculated severity and blast radius (`0–100`). | $O(\log N)$ Insert / $O(1)$ Peek | Powers the **Top Exposed Assets** triage table so incident responders neutralize the highest-risk asset (`net_banking_credentials`) first. |

---

## 🖥️ Dashboard Modules & Capabilities

### 1. Interactive Virtual Smartphone Sandbox (`Dashboard`)
* **Real-Time Lockscreen Simulation:** Displays live incoming Bank SMS OTP previews (`482-910`) that automatically mask when **Hide Lockscreen Previews** is enabled.
* **Hardware & Storage Telemetry:** Visualizes USB/ADB partition vulnerability (`UNENCRYPTED` vs. `FDE AES-256`) and cellular SIM status (`5G NO PIN` vs. `SIM PIN LOCKED`).
* **Interactive App Attack Simulation:** Clicking on **Notes**, **Photos**, **Banking**, or **Mail** inside the virtual device triggers a simulated compromise or biometric block and logs a live event directly to the SOC Threat Feed.
* **Remote Wipe Lockdown:** Activating **Remote Find/Wipe** triggers a full-screen remote erase overlay and severs all active attack paths.

### 2. Security Posture Assessment (`Assessments`)
* Audits every configured security control against its target layer (*Notifications*, *Application Data*, *Storage Files*, *Cellular / SMS*, *Device Recovery*) and provides real-time vulnerability rationales.

### 3. Dynamic Domain Exposure Reports (`Global Reports`)
* **Categorical Exposure Meters:** Tracks live risk percentages across **Identity Domain**, **Financial Domain**, and **Work & Cloud Storage**.
* **Dijkstra Compromise Flow Diagram:** Visualizes the exact multi-hop compromise chain and estimated time-to-breach.
* **Exposure by Attack Vector (Donut Chart):** Dynamically recalculates the percentage share of **Session Tokens**, **SMS Previews**, **Local Storage**, and **Weak Lock** vectors as defenses are enabled.
* **Max-Heap Priority Queue & Exports:** Lists exposed assets ranked by risk score alongside recommended remediations, with one-click **Export PDF** and **Download JSON** report generation.

### 4. Security Operations Center (`Threat Feed`)
* **Separated Posture vs. Telemetry Metrics:** Tracks enabled/disabled control coverage independently from detected threat events.
* **Live Intercept Stream & Triage Table:** Streams real-time attack probes with analyst workflow transitions (`Active` → `Investigating` → `Blocked` → `Resolved`), severity filtering, and 4 live Chart.js visualizations.

### 5. Priority Asset Ranking (`Risk`)
* Displays the raw Max-Heap extraction order of compromised assets with domain tags and sensitivity scores (`0–100`).

---

## 🛡️ Security Controls & Attack Vector Matrix

| Security Control | Mitigated Attack Vector | Protected Assets | Risk Reduction Impact |
| :--- | :--- | :--- | :--- |
| **Hide Lockscreen Previews** | SMS 2FA OTP Lockscreen Interception | Bank OTPs, Password Reset Codes | Blocks zero-click OTP theft without unlocking the device. |
| **Biometric App Lock** | Direct UPI & Session Token Hijack | Banking Apps, Primary Email, Notes | Prevents lateral movement into authenticated sessions. |
| **Full Disk Encryption (FDE)** | Unauthorized USB / ADB Partition Dump | ID Scans, Local Backups, Cached DBs | Enforces AES-256 encryption at rest against physical extraction. |
| **SIM Lock PIN** | Physical SIM Swap & Carrier OTP Hijack | Mobile Number, SMS-based 2FA | Locks the SIM card if transferred to an attacker's handset. |
| **Remote Find / Wipe** | Full Device Physical Possession | All Local & Cloud-Linked Domains | Remotely locks the device and purges cryptographic keys. |

---

## 📂 Project Structure

```text
Lost-Phone-Data-Exposure-Simulator/
├── app.py                  # Flask backend server & /api/simulate endpoint
├── engine.c                # ANSI C core (Hash Table, Dijkstra Graph, Max-Heap)
├── engine                  # Compiled C binary executable
├── templates/
│   └── index.html          # Complete single-page SOC & Simulation UI
└── README.md               # Project documentation
```

---

## 🚀 Installation & Local Setup

### Prerequisites
* **GCC Compiler** (`gcc`) for compiling the ANSI C engine
* **Python 3.8+** and **Flask** (`pip install flask`)

### Step-by-Step Setup

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/pnkjpuri/Lost-Phone-Data-Exposure-Simulator.git](https://github.com/pnkjpuri/Lost-Phone-Data-Exposure-Simulator.git)
   cd Lost-Phone-Data-Exposure-Simulator
   ```

2. **Install Python dependencies:**
   ```bash
   pip install flask
   ```

3. **Compile the ANSI C simulation engine:**
   ```bash
   gcc engine.c -o engine
   ```

4. **Start the Flask server:**
   ```bash
   python3 app.py
   ```

5. **Launch the Simulator:**
   Open your browser and navigate to `http://127.0.0.1:5000`.

---

## 🔌 API Specification

### `POST /api/simulate`
Evaluates the current security control configuration through the C engine and returns updated risk scores, Dijkstra attack paths, and Max-Heap ranked assets.

**Request Payload:**
```json
{
  "hide_notifs": true,
  "app_lock": false,
  "enable_fde": true,
  "sim_pin": false,
  "remote_wipe": false
}
```

**Response Payload:**
```json
{
  "exposure_score": 52,
  "attack_time_seconds": 105,
  "domains": {
    "identity": 60,
    "financial": 75,
    "cloud": 35
  },
  "attack_path": [
    "Unlocked Screen Entry (0s)",
    "SIM Swap Carrier OTP Intercept (+105s)",
    "Primary Email Account Takeover",
    "Banking Session Reset"
  ],
  "ranked_assets": [
    { "name": "net_banking_credentials", "domain": "Financial", "score": 84 },
    { "name": "admin_session", "domain": "Identity", "score": 78 }
  ]
}
```

---

## 🚨 Emergency Incident Response Reference
In a real-world lost phone scenario, execute these three containment steps immediately:
1. **Remote Device Lock & Erase:** Trigger a remote wipe via **Google Find My Device** or **Apple Find My**.
2. **Carrier SIM Suspension:** Contact your telecom provider (**Jio: 198**, **Airtel: 121**, **Vi: 198**) to block the SIM card and halt SMS OTP delivery.
3. **IMEI Blacklisting:** Submit a lost device block request on the Government of India **CEIR (Sanchar Saathi)** portal to disable the handset across all cellular networks.
