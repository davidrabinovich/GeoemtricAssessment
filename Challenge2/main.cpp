#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <random>
#include <thread>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;



void runServer(int port) {
	WSADATA data;
	int result = WSAStartup(MAKEWORD(2, 2), &data);
	if (result != 0) {
		cout << "WSAStarup failed - " << result << " try again";
		return;
	}
	
	sockaddr_in localAddress;
	ZeroMemory(&localAddress, sizeof(localAddress));
	localAddress.sin_family = AF_INET;
	localAddress.sin_port = htons(port);
	localAddress.sin_addr.s_addr = INADDR_ANY;
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET) {
		cout << "Failed to create socket - " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
	result = bind(ListenSocket, (sockaddr*)&localAddress, sizeof(localAddress));

	if (result == SOCKET_ERROR) {

		cout << "bind failed: " << WSAGetLastError() << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}
	//listen for connection
	result = listen(ListenSocket, SOMAXCONN);
	if (result == SOCKET_ERROR) {
		cout << "listen failed: " << WSAGetLastError() << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}
	//accept client
	cout << "server set up" << endl;
	while (true) {
		cout << "waiting to connect\n";
		SOCKET clientSocket = accept(ListenSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET) {
			cout << "accept failed: " << WSAGetLastError() << endl;
			closesocket(ListenSocket);
			WSACleanup();
			return;

		}
		const char* message = "Your mother is a hamster!";
		result = send(clientSocket, message, strlen(message), 0);
		if (result == SOCKET_ERROR) {
			cout << "send failed: " << WSAGetLastError() << endl;
			closesocket(clientSocket);
			WSACleanup();
			return;
		}
		char buffer[1024];
		result = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (result > 0) {
			buffer[result] = '\0';
			cout << "Received data from client: " << buffer << endl;


			const char* response = "Go away or I shall taunt you again";
			result = send(clientSocket, response, strlen(response), 0);
			if (result == SOCKET_ERROR) {
				std::cout << "send failed: " << WSAGetLastError() << std::endl;
				closesocket(clientSocket);
				WSACleanup();
				return;
			}
			else if (result == 0) {
				cout << "Client disconnected." << endl;
			}
			else {
				cout << "recv failed: " << WSAGetLastError() << endl;
			}
		}
	}
		closesocket(ListenSocket);
		WSACleanup();
	
}
void runClient(int port) {
	WSADATA data;
	int result = WSAStartup(MAKEWORD(2, 2), &data);
	if (result != 0) {
		cout << "WSAStarup failed - " << result << " try again";
		return;
	}
	
	sockaddr_in serverAddress;
	ZeroMemory(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == SOCKET_ERROR) {
		cout << "Client failed to connect to server - " << WSAGetLastError() << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return;
	}
	cout << "client socket made\n";

	result = connect(ConnectSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
	if (result == SOCKET_ERROR) {
		cout << "Client failed to connect to server - " << WSAGetLastError() << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return;
	}
	cout << "client connected to server" << endl;

	char buffer[1024];
	result = recv(ConnectSocket, buffer, sizeof(buffer), 0);
	if (result > 0)
	{
		buffer[result] = '\0';
		cout << "recieved message from server: " << buffer << endl;
		const char* response = "And your father smelled of elderberries!!";
		result = send(ConnectSocket, response, strlen(response), 0);
		if (result == SOCKET_ERROR) {
			cout << "send failed: " << WSAGetLastError() << endl;
			closesocket(ConnectSocket);
			WSACleanup();
			return;
		}
		else if (result == 0) {
			cout << "Client disconnected." << endl;
		}
		else {
			cout << "recv failed: " << WSAGetLastError() << endl;
		}
	}

	closesocket(ConnectSocket);
	WSACleanup();
}


	
//memset(&serverAddress, 0, sizeof(serverAddress));
//serverAddress.sin_family = AF_INET;
//serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
int main(){
	int port = (rand() % (65535 - 2000 + 1)) + 2000;
	//int port = (2003);
	thread serverThread(runServer, port);
	Sleep(10);//let thread wait for client
	thread clientThread(runClient, port);
	serverThread.join();
	clientThread.join();
	
	
	return 0;
}