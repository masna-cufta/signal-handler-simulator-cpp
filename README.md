# Signal Handler Simulator (C++)

A simple C++ simulation of POSIX signal handling using `sigaction`.  
The program demonstrates how higher-priority signals interrupt lower-priority ones, simulating context saving, restoring, and a basic execution "stack".

---

## 🚀 Features

- Signal handlers for signals 1 to 5
- Priority-based signal preemption
- Context saving (KON), flag tracking (K_Z), and stack simulation
- Uses `sigaction`, `sleep`, `getpid()` and terminal output

---

## 🛠️ Build & Run

```bash
g++ -o signal_sim signal_sim.cpp
./signal_sim
