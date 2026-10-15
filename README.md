Set-Content -Path "README.md" -Value '# 🛡️ Lost Phone Data Exposure Simulator

An interactive cybersecurity risk modeling engine and web application that simulates data exposure when an unencrypted mobile device is lost or stolen.

## 🚀 Key Features & DSA Architecture

* **File System Representation (N-ary Tree):** Models folder hierarchies (`/storage/DCIM`, `/Documents`) using Left-Child Right-Sibling pointers.
* **Attack Path Computation (Dijkstra + Min-Heap):** Calculates the shortest time (in seconds) for an attacker to achieve full account takeover ($O((V+E)\log V)$).
* **Asset Exposure Ranking (Max-Heap):** Dynamically ranks compromised personal data by sensitivity score (1–100) in $O(\log N)$ time.
* **Credential Storage (Hash Table):** Simulates $O(1)$ extraction of saved OAuth session tokens and browser passwords using linked-list chaining.
* **Interactive Web Dashboard (Flask + Bootstrap):** Real-time smartphone simulation interface with live security control toggles.

---

## 🛠️ Tech Stack

* **Backend Engine:** ANSI C (C99 Standard)
* **API Wrapper:** Python 3 (Flask)
* **Frontend UI:** HTML5, CSS3, JavaScript, Bootstrap 5
* **Build Tools:** GCC, Make, Git, Valgrind

---

## 🏃 Quickstart Guide

### 1. Build the C Engine
```bash
gcc -Iinclude src/*.c -o simulator.exe
