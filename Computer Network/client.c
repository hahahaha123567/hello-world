#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "4890"

SOCKET myConnect(struct addrinfo *result)
{
	int iResult;
	SOCKET ConnectSocket = INVALID_SOCKET;

	// Attempt to connect to an address until one succeeds
	for (struct addrinfo *ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("> socket failed with error: %ld\n", WSAGetLastError());
		}
		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
		} else {
			break;
		}
	}
	return ConnectSocket;
}

void mySendMessage(SOCKET ConnectSocket, char opcode)
{
	int iResult;
	char sendbuf[255] = {0};

	// Send an initial buffer
	sendbuf[0] = opcode;
	if (opcode == 7) {
		printf("> Please input your message:\n");
		getchar();
		gets_s(sendbuf + 1, 254);
	}
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("> Send failed with error: %d\n", WSAGetLastError());
	}
}

DWORD WINAPI receiveFunction(LPVOID lpParam)
{
	int iResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	SOCKET ConnectSocket = (SOCKET)lpParam;

	// Receive until the peer closes the connection
	do {
		ZeroMemory(recvbuf, recvbuflen);
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("%s\n", recvbuf);
		} else if (iResult == 0) {
			printf("> Connection closed\n");
		} else {
			// I donot how to avoid this error = =
			// printf("> recv failed with error: %d\n", WSAGetLastError());
		}
	} while (iResult > 0);

	return 0;
}

int main()
{
	// used in control flow
	int opCode;
	bool isConnected = false, needQuit = false;
	// used in network
	int iResult;
	WSADATA wsaData;
	struct addrinfo *result = NULL, hints;
	SOCKET ConnectSocket = (SOCKET)NULL;
	char serverName[20], port[10];
	// used in multithread
	DWORD receiveThreadId;
	HANDLE receiveThread = NULL;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("> WSAStartup failed with error: %d\n", iResult);
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	while (!needQuit) {
		// show menu
		printf("> Please input option code:\n");
		printf("  1.connect  2.quit");
		if (isConnected) {
			printf("  3.break  4.get time  5.get name  6.get client  7.send message");
		}
		printf("\n");
		scanf_s("%d", &opCode);
		switch (opCode) {
			case 1: {
				printf("> Please input server IP:\n");
				getchar();
				gets_s(serverName, 20);
				printf("> Please input port number:\n");
				gets_s(port, 10);
				// Resolve the server address and port
				iResult = getaddrinfo(serverName, port, &hints, &result);
				if (iResult != 0) {
					printf("> Getaddrinfo failed with error: %d\n", iResult);
				}
				ConnectSocket = myConnect(result);
				if (isConnected) {
					printf("> It's already connected!\n");
				} else if (ConnectSocket == INVALID_SOCKET) {
					printf("> Unable to connect to server!\n");
				} else {
					isConnected = true;
					receiveThread = CreateThread(NULL, 0, receiveFunction, (LPVOID)ConnectSocket, 0, &receiveThreadId);
					printf("> Connect success!\n");
				}
				break;
			}
			case 2: {
				needQuit = true;
				if (isConnected) {
					closesocket(ConnectSocket);
					isConnected = false;
				}
				printf("> Quit success!\n");
				break;
			}
			case 3: {
				closesocket(ConnectSocket);
				isConnected = false;
				printf("> Break success!\n");
				break;
			}
			case 4: {
				for (int i = 0; i < 1000; ++i) {
					mySendMessage(ConnectSocket, 4);
				}
				break;
			}
			case 5: {
				mySendMessage(ConnectSocket, 5);
				break;
			}
			case 6: {
				mySendMessage(ConnectSocket, 6);
				break;
			}
			case 7: {
				mySendMessage(ConnectSocket, 7);
				break;
			}
			default: {
				//
			}
		}
		Sleep(1000); // wait for receiveThread print
		printf("\n");
	}

	// cleanup
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("> shutdown failed with error: %d\n", WSAGetLastError());
	}
	freeaddrinfo(result);
	if (receiveThread != NULL) {
		CloseHandle(receiveThread);
	}
	WSACleanup();

	return 0;
}