#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32.lib")
#define PORTNUM 12354
#define BUFMAX 1024

int main(int argc, char** argv) {
	//try the system start
	//system("start C:\\Users\\zack\\Desktop\\eyeTracking-offscreenCalibration\\Debug\\eyeTracking-offscreenCalibration.exe");

	//add
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
		serverAddr.sin_addr.s_addr = inet_addr("172.22.254.14");

		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		//windowsEchoLoop(sock, (SOCKADDR*)& serverAddr, sizeof(serverAddr));

		//add windowsEchoLoop
		int bytesRead;
		int sendToResult;
		char inputBuffer[BUFMAX] = { 0 };
		char recvBuffer[BUFMAX] = { 0 };

		//AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
		//automatically start the eye tracking program when this program starts
		sendto(sock, "udp client started", strlen("udp client started"), 0, (SOCKADDR*)& serverAddr, sizeof(serverAddr));
		//system("start C:\\Users\\zack\\Desktop\\eyeTracking-offscreenCalibration\\Debug\\eyeTracking-offscreenCalibration.exe");
		

		for (;;)
		{
			printf("Type message: ");
			fgets(inputBuffer, BUFMAX, stdin);

			sendToResult = sendto(sock, inputBuffer, strlen(inputBuffer), 0, (SOCKADDR*)& serverAddr, sizeof(serverAddr));

			if (sendToResult == SOCKET_ERROR) {
				wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
				closesocket(sock);
				WSACleanup();

				puts("Press any key to continue");
				getc(stdin);
				exit(sendToResult);
			}


		}
		//end
	}
	else
	{
		return EXIT_FAILURE;
	}
	//end

	puts("Press any key to continue");
	getc(stdin);

	return EXIT_SUCCESS;
}