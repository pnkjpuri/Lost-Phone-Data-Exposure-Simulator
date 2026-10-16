# 🛡️ PhoneExposure Lab — Lost Phone Exposure Simulator

An interactive cybersecurity risk modeling engine and web sandbox that visually simulates data exposure vectors when an unencrypted or weakly secured mobile device is lost or stolen.

---

## 🛠️ Data Structures & Core System Architecture

PhoneExposure Lab bridges a low-level ANSI C algorithmic engine with a web dashboard via a Python Flask API bridge.

* **Security Controls Flag Engine (Hash Table):** Evaluates active configuration flags (`hide_notifs`, `app_lock`, `enable_fde`, `sim_pin`, `remote_wipe`) in $O(1)$ constant time using linked-list chaining.
* **Exploit Path Traversal (Directed Graph + Dijkstra's Algorithm):** Calculates the shortest time and vulnerability sequence for an attacker to achieve account takeover ($O((V + E) \log V)$).
* **Asset Exposure Ranking (Max-Heap Priority Queue):** Dynamically ranks compromised personal data by sensitivity score (1–100) in $O(\log N)$ time.
* **Directory Hierarchy Mapping (N-ary Tree):** Models folder structures using Left-Child Right-Sibling pointer representations.

---

## 📁 Repository Structure

```text
DATA/
├── include/
│   └── simulator.h      # Shared C structure definitions & function prototypes
├── src/
│   ├── auth_vault.c     # Hash Table implementation for control flags
│   ├── attack_graph.c   # Graph edge & vertex management
│   ├── pathfinder.c     # Dijkstra shortest path algorithm
│   ├── risk_evaluator.c # Max-Heap priority queue implementation
│   ├── filesystem.c     # N-ary file tree traversal
│   └── main.c           # Dynamic JSON CLI output wrapper
├── templates/
│   └── index.html       # High-contrast dual-panel web dashboard
└── app.py               # Python Flask bridge executing compiled C binary
