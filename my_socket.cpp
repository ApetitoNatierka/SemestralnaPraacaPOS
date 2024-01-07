#include "my_socket.h"
#include <stdexcept>
#include <ws2tcpip.h>
#include <winsock2.h>
#include <unistd.h>
#include <cerrno>


#define SOCKET_TERMINATE_CHAR '\0'

const char* MySocket::endMessage = ":end";  // upravit podla potreby

MySocket* MySocket::createConnection(std::string hostName, short port) {
    WSADATA wsaData;
    struct addrinfo *result = NULL;
    struct addrinfo hints;
    int iResult;

    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);  // STARTUP
    if (iResult != 0) {
        throw std::runtime_error("WSAStartup failed with error: " + std::to_string(iResult) + "\n");
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(hostName.c_str(), std::to_string(port).c_str(), &hints, &result);
    if (iResult != 0) {
        WSACleanup();   // CLEANUP
        throw std::runtime_error("getaddrinfo failed with error: " + std::to_string(iResult) + "\n");
    }

    // Create a SOCKET for connecting to server
    SOCKET connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (connectSocket == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("socket failed with error: " + std::to_string(WSAGetLastError()) + "\n");
    }

    // Connect to server
    iResult = connect(connectSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(connectSocket);
        connectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (connectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        throw std::runtime_error("Unable to connect to server.\n");
    }

    return new MySocket(connectSocket);
}

MySocket::MySocket(SOCKET socket) :
    connectSocket(socket) {

}

MySocket::~MySocket() {
    if (this->connectSocket != INVALID_SOCKET) {
        closesocket(this->connectSocket);
        this->connectSocket = INVALID_SOCKET;
    }
    WSACleanup();
}

void MySocket::sendData(const std::string &data) {
    size_t data_length = data.length();
    char* buffer = (char*)calloc(data_length + 1, sizeof(char));
    memcpy(buffer, data.c_str(), data_length);
    buffer[data_length] = SOCKET_TERMINATE_CHAR;

    int iResult = send(connectSocket, buffer, data_length + 1, 0 );
    if (iResult == SOCKET_ERROR) {
        throw std::runtime_error("send failed with error: " + std::to_string(WSAGetLastError()) + "\n");
    }
    free(buffer);
    buffer = NULL;
}

std::string MySocket::receiveData() {
    char buffer[4096];
    std::string received_data;

    while (true) {
        // Kontrola platnosti file descriptoru
        if (connectSocket == INVALID_SOCKET || connectSocket < 0) {
            throw std::runtime_error("Socket descriptor is invalid\n");
        }

        // Kontrola, či je file descriptor pripravený na čítanie
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(connectSocket, &read_fds);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000; // 100 ms

        int select_result = select(connectSocket + 1, &read_fds, NULL, NULL, &timeout);

        if (select_result == -1) {
            int error_number = errno;
            throw std::runtime_error("select failed with error: " + std::to_string(error_number) + "\n");
        } else if (select_result == 0) {
            // Timeout - file descriptor nie je pripravený na čítanie
            continue;
        }

        ssize_t bytes_received = read(connectSocket, buffer, sizeof(buffer));

        if (bytes_received > 0) {
            received_data.append(buffer, bytes_received);

            size_t null_pos = received_data.find('\0');
            if (null_pos != std::string::npos) {
                received_data.erase(null_pos);  // Odstráni '\0' z reťazca
                break;
            }
        } else if (bytes_received == 0) {
            // Server odpojil pripojenie
            break;
        } else {
            // Nastala chyba pri prijímaní dát
            int error_number = errno;
            throw std::runtime_error("read failed with error: " + std::to_string(error_number) + "\n");
        }
    }

    return received_data;
}
void MySocket::sendEndMessage() {
    this->sendData(this->endMessage);
}

#undef SOCKET_TERMINATE_CHAR