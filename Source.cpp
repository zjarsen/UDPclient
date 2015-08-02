#define PLATFORM_WINDOWS  1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PLATFORM PLATFORM_WINDOWS
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#define PORTNUM 12354
#define BUFMAX 1024

void windowsEchoLoop(SOCKET, SOCKADDR*, size_t);
int windowsEchoClient();

int main(int argc, char** argv) {
	windowsEchoClient();

	puts("Press any key to continue");
	getc(stdin);

	return EXIT_SUCCESS;
}

int windowsEchoClient()
{
	SOCKET sock;
	sockaddr_in serverAddr;
	WSADATA wsaDat;

	int wsaError = WSAStartup(MAKEWORD(2, 2), &wsaDat);

	if (!wsaError)
	{
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		if (sock == INVALID_SOCKET)
		{
			wprintf(L"socket function failed with error = %d\n", WSAGetLastError());
			exit(-1);
		}

		ZeroMemory(&serverAddr, sizeof(serverAddr));

		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(PORTNUM);
		serverAddr.sin_addr.s_addr = inet_addr("10.42.0.1");

		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		windowsEchoLoop(sock, (SOCKADDR*)& serverAddr, sizeof(serverAddr));
	}
	else
	{
		return EXIT_FAILURE;
	}
}

void windowsEchoLoop(SOCKET sock, SOCKADDR* serverAddr, size_t serverlen)
{
	int bytesRead;
	int sendToResult;
	char inputBuffer[BUFMAX] = { 0 };
	char recvBuffer[BUFMAX] = { 0 };

	for (;;)
	{
		printf("Type message: ");
		fgets(inputBuffer, BUFMAX, stdin);

		sendToResult = sendto(sock, inputBuffer, strlen(inputBuffer), 0, serverAddr, serverlen);

		if (sendToResult == SOCKET_ERROR) {
			wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
			closesocket(sock);
			WSACleanup();

			puts("Press any key to continue");
			getc(stdin);
			exit(sendToResult);
		}

		
	}
}