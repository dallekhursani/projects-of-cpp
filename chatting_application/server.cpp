#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <mutex>
#include <algorithm>

#define PORT 8080

using namespace std;

vector<int> clients;
mutex clients_mutex;

void handle_client(int client_socket) {
    char buffer[1024];
    while (true) {
        ssize_t bytes = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes <= 0) {
            lock_guard<mutex> lock(clients_mutex);
            clients.erase(remove(clients.begin(), clients.end(), client_socket), clients.end());
            close(client_socket);
            break;
        }
        buffer[bytes] = '\0';

        lock_guard<mutex> lock(clients_mutex);
        for (int sock : clients) {
            if (sock != client_socket) {
                send(sock, buffer, bytes, 0);
            }
        }
    }
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);
    cout << "Server started on port " << PORT << endl;

    while (true) {
        int client_socket = accept(server_fd, nullptr, nullptr);
        {
            lock_guard<mutex> lock(clients_mutex);
            clients.push_back(client_socket);
        }
        thread(handle_client, client_socket).detach();
    }

    return 0;
}
