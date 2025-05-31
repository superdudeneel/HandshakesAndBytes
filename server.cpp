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
    if (!fn_dll()) {
        cout << "DLL failed to iniliaze" << endl;
        return 1;
    }
    else {
        cout << "DLL initialized" << endl;

    }

    SOCKET listensocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listensocket == INVALID_SOCKET) {
        cout << "SOCKET creation failed" << endl;
        return 1;
    }
    else {
        cout << "SOCKET created" << endl;

    }

    sockaddr_in server_address;
    server_address.sin_family  = AF_INET;
    server_address.sin_port = htons(1234);
    if (InetPton(AF_INET, "127.0.0.1", &server_address.sin_addr.s_addr)!=1) {
        cout << "Server address not valid" << endl;
        closesocket(listensocket);
        WSACleanup();
        return 1;
    }
    else {
        cout << "Server structure valid" << endl;

    }
    if (bind(listensocket, (sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        cout << "Server bind failed" << endl;
        closesocket(listensocket);
        WSACleanup();
        return 1;
    }
    else {
        cout << "Server bind ready" << endl;
    }

    if (listen(listensocket, SOMAXCONN)!=SOCKET_ERROR) {
        cout << "Server listening" << endl;
    }
    else {
        cout << "Server listening failed" << endl;
        closesocket(listensocket);
        WSACleanup();
        return 1;
    }

    SOCKET clientsocket  = accept(listensocket, NULL, NULL);
    if (clientsocket == INVALID_SOCKET) {
        cout << "Accept failed" << endl;
    }
    else {
        cout << "Accept ready" << endl;
    }

    while (true) {
        char buffer[4096];
        int bytes_received = recv(clientsocket, buffer, sizeof(buffer), 0);
        string message(buffer, bytes_received);
        if (message == "quit") {
            closesocket(clientsocket);
            closesocket(listensocket);
            break;

        }
        cout << "message from client: " << message << endl;

    }



    WSACleanup();
}
