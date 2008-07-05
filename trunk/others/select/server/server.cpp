
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <map>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

char data[] = "";

DWORD WINAPI ServerThread(LPVOID lpParam) {
	SOCKET s = (SOCKET)lpParam;
	std::string str;
	while (1) {
		cin>>str;
		if (str == "exit")
			break;
		else {
			send(s, str.c_str(), str.length(), 0);
		}
	}
	return 0;
}

int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);

	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr;
	memset((void*)&addr, 0,  sizeof(sockaddr));
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1000);

	if (SOCKET_ERROR == bind(server_socket, (sockaddr*)&addr, sizeof(addr))) {
		cout<< "bind failed" << endl;
		return 0;
	}

	if (SOCKET_ERROR == listen(server_socket, 5)) {
		cout << "listen failed ..." << endl;
		return 0;
	}

	while (1) {
		sockaddr_in client_addr;
		int name_len = sizeof(client_addr);
		DWORD dwThreadid;
		SOCKET client_socket = accept(server_socket, (sockaddr*)&client_addr, &name_len);
		HANDLE hThread = CreateThread(NULL, 1, 
			ServerThread, (LPVOID)client_socket, 0, &dwThreadid);
	}


	closesocket(server_socket);
	WSACleanup();
}