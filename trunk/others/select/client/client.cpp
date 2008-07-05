#include <winsock2.h>
#include <windows.h>
#include <iostream.h>
#include <string>
#include <map>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr;
	memset((void*)&addr, 0,  sizeof(sockaddr));
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1000);

	int ret = connect(s, (sockaddr*)&addr, sizeof(addr));
	
	const int  buf_size= 1024;
	char buffer[buf_size];
	while (1) {
		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(s, &readfds);

		int x = select(0, &readfds, NULL, NULL, NULL);
		if (FD_ISSET(s, &readfds)) {
			int len = recv(s, buffer, buf_size, 0);
			buffer[len] = '\0';
			cout<<buffer<<endl;
		}
	}

	WSACleanup();
}