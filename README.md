# 🔌 WinSocket Chat – C++ Socket Programming (Client & Server)

This project demonstrates a basic **TCP client-server communication** setup using **Winsock** in C++. It consists of:

- 🖥️ A **server** that listens for incoming client connections.
- 💬 A **client** that connects to the server and sends a message.

---

## 📁 Files

- `server.cpp` – Implements the TCP server
- `client.cpp` – Implements the TCP client

---

## ⚙️ Requirements

- Windows OS
- C++ compiler (Visual Studio / g++ with MinGW)
- Winsock2 (comes with Windows SDK)

---

## 🛠️ How to Build

### 🧱 Compile Server

```bash
g++ server.cpp -o server -lws2_32
