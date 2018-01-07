#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Mstcpip.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Ntdll.lib")

#define MAX_THREAD_NUM 10
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "4890"

typedef struct YazawaNico {
	SOCKET pClientSocket;
	bool *pNeedQuit;
} Nico;

struct addrinfo * init()
{
	int iResult;
	WSADATA wsaData;
	struct addrinfo *result = NULL, hints;
	int nameLen = 20;
	char name[20];
	char ipv4[20];

	// get host name
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("> WSAStartup failed with error: %d\n", iResult);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	GetComputerName(name, &nameLen);
	iResult = getaddrinfo(name, DEFAULT_PORT, &hints, &result);
	struct sockaddr_in *sockaddr_ipv4 = (struct sockaddr_in *) result->ai_addr;
	RtlIpv4AddressToString(&(sockaddr_ipv4->sin_addr), ipv4);
	printf("> Current IP address: %s, port number: %s\n", ipv4, DEFAULT_PORT);

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("> getaddrinfo failed with error: %d\n", iResult);
	}
	return result;
}

DWORD WINAPI exitFunction(LPVOID lpParam)
{
	bool *pNeedQuit = (bool *)lpParam;
	char key = 0;

	while (!*pNeedQuit) {
		scanf_s("%c", &key, 1);
		if (key == 'q') {
			*pNeedQuit = true;
		}
	}
	// cannot send signal to main thread = =
	exit(0);
	
	return 0;
}

DWORD WINAPI clientFunction(LPVOID lpParam)
{
	int iResult;
	int iSendResult;

	Nico data = *(Nico *)lpParam;
	SOCKET ClientSocket = data.pClientSocket;
	bool *pCurrNeedQuit = data.pNeedQuit;

	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	char sendbuf[DEFAULT_BUFLEN];
	int sendbuflen = DEFAULT_BUFLEN;

	// Receive until the peer shuts down the connection
	while(!(*pCurrNeedQuit)) {
		ZeroMemory(recvbuf, recvbuflen);
		ZeroMemory(sendbuf, sendbuflen);
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("> Receive info type: %c\n", recvbuf[0]+'0');
			// key control flow
			switch (recvbuf[0]) {
				case 4: {
					SYSTEMTIME sys;
					GetLocalTime(&sys);
					snprintf(sendbuf, sendbuflen, "%4d/%02d/%02d %02d:%02d:%02d", 
						sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
					break;
				}
				case 5: {
					GetComputerName(sendbuf, &sendbuflen);
					break;
				}
				case 6: {
					// deprecated
					// struct hostent *phostinfo = gethostbyname("");
					// char *p = inet_ntoa(*((struct in_addr *)(*phostinfo->h_addr_list)));

					int iResult;
					struct addrinfo *result = NULL, hints;
					char ipv4[20];
					ZeroMemory(&hints, sizeof(hints));
					hints.ai_family = AF_INET;
					hints.ai_socktype = SOCK_STREAM;
					hints.ai_protocol = IPPROTO_TCP;
					hints.ai_flags = AI_PASSIVE;
					GetComputerName(sendbuf, &sendbuflen);
					sendbuflen = DEFAULT_BUFLEN;
					iResult = getaddrinfo(sendbuf, DEFAULT_PORT, &hints, &result);
					struct sockaddr_in *sockaddr_ipv4 = (struct sockaddr_in *) result->ai_addr;
					RtlIpv4AddressToString(&(sockaddr_ipv4->sin_addr), ipv4);
					ZeroMemory(sendbuf, sendbuflen);
					snprintf(sendbuf, DEFAULT_BUFLEN, "server: %s:%s", ipv4, DEFAULT_PORT);
					break;
				}
				case 7: {
					printf("> Get message from client:\n%s\n ", recvbuf + 1);
					break;
				}
				default: {
					printf("> invalid opcode\n");
				}
			}

			iSendResult = send(ClientSocket, sendbuf, strlen(sendbuf), 0);
			printf("> Send: %s\n", sendbuf);
			if (iSendResult == SOCKET_ERROR) {
				printf("> Send failed with error: %d\n", WSAGetLastError());
			}
		} else if (iResult == 0) {
			printf("> Connection closing...\n");
			break;
		} else {
			// I donot know how to avoid this error = =
			// printf("> recv failed with error: %d\n", WSAGetLastError());
			break;
		}
	}
	// shutdown the send connection
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("> Shutdown failed with error: %d\n", WSAGetLastError());
	}
	closesocket(ClientSocket);

	return 0;
}

int main(void)
{
	int iResult;
	bool needQuit = false;

	SOCKET ListenSocket = INVALID_SOCKET;

	struct addrinfo *result = init();

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("> socket failed with error: %ld\n", WSAGetLastError());
	}
	// Setup the TCP listening socket, bind
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("> bind failed with error: %d\n", WSAGetLastError());
	}
	// listen
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("> listen failed with error: %d\n", WSAGetLastError());
	}
	// detect quit signal
	DWORD exitThreadId;
	HANDLE exitThread = NULL;
	exitThread = CreateThread(NULL, 0, exitFunction, &needQuit, 0, &exitThreadId);
	printf("> Server boot success!\n> (Input q to quit)\n");
	// accept in loop
	DWORD clientThreadsId[MAX_THREAD_NUM];
	HANDLE clientThreads[MAX_THREAD_NUM];
	Nico data[MAX_THREAD_NUM];
	int threadIndex = 0;
	while (!needQuit) {
		data[threadIndex].pClientSocket = INVALID_SOCKET;
		data[threadIndex].pClientSocket = accept(ListenSocket, NULL, NULL);
		data[threadIndex].pNeedQuit = &needQuit;
		if (data[threadIndex].pClientSocket == INVALID_SOCKET) {
			printf("> Accept failed with error: %d\n", WSAGetLastError());
		} else {
			clientThreads[threadIndex] = CreateThread(NULL, 0, clientFunction, &data[threadIndex], 0, &clientThreadsId[threadIndex]);
			threadIndex++;
		}
	}
	
	// cleanup
	closesocket(ListenSocket);
	freeaddrinfo(result);
	WSACleanup();

	return 0;
}