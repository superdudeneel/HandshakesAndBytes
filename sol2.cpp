#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;
#pragma comment(lib, "ws2_32.lib")

bool fn_dll() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

int main() {
    cout << "server side code" << endl;

    if (!fn_dll()) {
        cout << "failed to initialize the dll" << endl;
    } else {
        cout << "DLL success" << endl;
    }

    SOCKET listensocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listensocket == INVALID_SOCKET) {
        cout << "failed to create socket" << endl;
    } else {
        cout << "socket success" << endl;
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(1234);

    if (InetPton(AF_INET, "127.0.0.1", &server_address.sin_addr) != 1) {
        cout << "address structure failed" << endl;
        closesocket(listensocket);
        WSACleanup();
        return 1;
    }

    if (bind(listensocket, (sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        cout << "bind failed" << endl;
    } else {
        cout << "bind success" << endl;
    }

    if (listen(listensocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "listen failed" << endl;
        closesocket(listensocket);
        WSACleanup();
        return 1;
    } else {
        cout << "listen success" << endl;
    }

    cout << "Server is up and running" << endl;

    SOCKET clientsocket = accept(listensocket, nullptr, nullptr);
    if (clientsocket == INVALID_SOCKET) {
        cout << "accept failed" << endl;
    } else {
        cout << "accept success" << endl;
    }

    char buffer[4096];
    int bytes_received = recv(clientsocket, buffer, sizeof(buffer), 0);
    string message(buffer, bytes_received);
    cout << "message from client: " << message << endl;

    closesocket(clientsocket);
    closesocket(listensocket);
    WSACleanup();

    return 0;
}
