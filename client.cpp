#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;
#pragma comment(lib, "ws2_32.lib")

bool fn_dll() {
    WSAData data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
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
    string message;
    cout << "Enter message to send: " << endl;
    getline(cin, message);
    int bytesent = send(s, message.c_str(), message.length(), 0);
    if (bytesent == SOCKET_ERROR) {
        cout << "Failed to send message" << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }
    else {
        cout << "Successfully sent message" << endl;
    }


    WSACleanup();
}
