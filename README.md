# PhoneShield — Lost Phone Data Exposure Simulator

An interactive cybersecurity simulation platform that models physical and digital data exposure risks when a smartphone is lost or unattended. Powered by a high-performance **ANSI C data structures engine** and a real-time **Security Operations Center (SOC) web dashboard**.

---

## Core Architecture & Data Structures

* **C Simulation Engine:**
  * **Hash Tables:** Maps device security controls (`Hide Lockscreen Previews`, `Biometric App Lock`, `Full Disk Encryption`, `SIM Lock PIN`, `Remote Find/Wipe`) for $O(1)$ posture lookup.
  * **Dijkstra’s Shortest Path Graph:** Computes the fastest attacker compromise chain (e.g., *Unlocked Screen → SMS OTP → Primary Gmail → Bank Reset*) and dynamically updates compromise time as defenses are toggled.
  * **Max-Heap Priority Queue:** Ranks high-value exposed assets (`net_banking_credentials`, `admin_session`, `personal_backup.zip`) by calculated risk score for incident triage.
* **Interactive SOC Web Dashboard:**
  * **Virtual Smartphone Sandbox:** Live lockscreen OTP previews, USB/ADB storage status, SIM PIN state, interactive app click interception, and remote wipe simulation.
  * **Dynamic Domain Exposure Reports:** Real-time risk breakdown across *Identity*, *Financial*, and *Work & Cloud Storage* domains, live **Exposure by Attack Vector** donut chart, Dijkstra attack flow diagram, and JSON/PDF export.
  * **SOC Threat Feed & Telemetry:** Simulated real-time attack stream with incident lifecycle transitions (`Active` → `Investigating` → `Blocked` → `Resolved`) and live Chart.js analytics.

---

## Tech Stack

* **Backend & Core Engine:** C (GCC), Python (Flask)
* **Frontend:** HTML5, Tailwind CSS, Bootstrap 5, Chart.js, Vanilla JavaScript

---

## Setup & Usage

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/pnkjpuri/Lost-Phone-Data-Exposure-Simulator.git](https://github.com/pnkjpuri/Lost-Phone-Data-Exposure-Simulator.git)
   cd Lost-Phone-Data-Exposure-Simulator
