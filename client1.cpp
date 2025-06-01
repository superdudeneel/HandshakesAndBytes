#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

bool fn_dll() {
    WSAData data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void sendmessage(SOCKET s){
  string name;
  string message;
  cout << "Enter your chat name: ";
  getline(cin, name);
  while(1){
    getline(cin, message);
    string msg = name + " : " + message;
    if(message=="exit"){
        break;
    }
    int bytesend = send(s, msg.c_str(), msg.length(), 0);
    if(bytesend==SOCKET_ERROR){
      cout << "Error sending message\n";
      break;

    }

  }
  closesocket(s);
  WSACleanup();
}

void recvmessage(SOCKET s){
    char buffer[4096];
    string msg = "";

    while(1){
        int byte_recv = recv(s, buffer, sizeof(buffer), 0);
        if (byte_recv<=0) {
            cout << "client disconnected" << endl;
            break;

        }
        else{
          msg = string(buffer, byte_recv);
          cout << msg << endl;
        }
    }

    closesocket(s);
    WSACleanup();
}

int main() {

    cout << "client side code" << endl;

    if (!fn_dll()) {
        cout << "Failed to initialize lib" << endl;
        return 1;
    }
    else {
        cout << "Successfully initialized lib" << endl;
    }

    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        cout << "Failed to create socket" << endl;
    }
    else {
        cout << "Successfully created socket" << endl;
    }
    string server_addr = "127.0.0.1";
    int port = 1234;
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, server_addr.c_str(), &server_address.sin_addr);
    if (connect(s, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        cout << "Failed to connect to server" << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }
    else {
        cout << "Successfully connected to server" << endl;
    }

    thread sender_thread(sendmessage, s);
    thread recvmessage_thread(recvmessage, s);
    sender_thread.join();
    recvmessage_thread.join();

    WSACleanup();
}
