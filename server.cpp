#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <vector>
#include <algorithm>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

bool fn_dll() {
    WSAData data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;

}

void interactwithclient(SOCKET clientsocket, vector<SOCKET> &clients) {
    cout << "client connected" << endl;

    char buffer[4096];
    while (1) {
        int byte_recv = recv(clientsocket, buffer, sizeof(buffer), 0);
        if (byte_recv<=0) {
            cout << "client disconnected" << endl;
            break;

        }
        string message(buffer, byte_recv);
        cout << "message from client: " << message << endl;
        for (auto client: clients) {
            if (client!=clientsocket) {
                send(client, message.c_str(), message.size(), 0);
            }
        }



    }
    auto it = find(clients.begin(), clients.end(), clientsocket);
    if (it!=clients.end()) {
        clients.erase(it);
    }
    closesocket(clientsocket);
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

    vector<SOCKET> clients;


    while (1) {
        SOCKET clientsocket  = accept(listensocket, NULL, NULL);
        if (clientsocket == INVALID_SOCKET) {
            cout << "Accept failed" << endl;
        }
        else {
            cout << "Accept ready" << endl;
        }
        clients.push_back(clientsocket);

        thread t1(interactwithclient, clientsocket, std::ref(clients));
        t1.detach();

    }

    WSACleanup();
}
