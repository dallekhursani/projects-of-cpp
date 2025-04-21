#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

using namespace std;

void receive_messages(int socket_fd) {
    char buffer[1024];
    while (true) {
        ssize_t bytes = recv(socket_fd, buffer, sizeof(buffer), 0);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';
        cout << "\r" << buffer << "\n> " << flush;
    }
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    cout << "Connected to server.\n";

    string name;
    cout << "Enter your name: ";
    getline(cin, name);

    thread receiver(receive_messages, sock);

    string message;
    while (true) {
        cout << "> ";
        getline(cin, message);
        if (message == "/quit") break;
        string full_msg = name + ": " + message;
        send(sock, full_msg.c_str(), full_msg.length(), 0);
    }

    close(sock);
    return 0;
}
