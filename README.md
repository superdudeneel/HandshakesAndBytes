# 💬 Multi-Client Chat Server in C++ using Winsock

This project implements a basic **multi-threaded chat server and clients** using **Winsock (Windows Sockets API)** in **C++**. The server listens for incoming TCP connections and broadcasts messages between connected clients.

---

## 📁 Files

- `server.cpp` - The server that accepts multiple clients and relays their messages.
- `client1.cpp` - A simple chat client that can send and receive messages.
- `client2.cpp` - Identical to `client1.cpp` (can simulate another user for testing).

---

## ⚙️ Requirements

- Windows OS
- `g++` from MinGW (or use Visual Studio)
- Winsock2 library (already included with Windows SDK)

---

## 🛠️ How to Compile

Using MinGW (MSYS2 or Command Prompt):

### Compile Server
```bash
g++ server.cpp -o server.exe -lws2_32
g++ client1.cpp -o client1.exe -lws2_32
g++ client2.cpp -o client2.exe -lws2_32
./server.exe
./client1.exe
./client2.exe
