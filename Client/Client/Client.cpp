#include "ClientOptions.h"
#define _CRT_SECURE_NO_WARNINGS

// TO DO: CLIENT DELAY , MEASURE RTT , ANNOTATIONS //

void main()
{

	// Initialize Winsock (Windows Sockets).
	WSAData wsaData;
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Time Client: Error at WSAStartup()\n";
		return;
	}

	// Client side:
	// Create a socket and connect to an internet address.
	SOCKET connSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == connSocket)
	{
		cout << "Time Client: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// For a client to communicate on a network, it must connect to a server.
	// Need to assemble the required data for connection in sockaddr structure.
	// Create a sockaddr_in object called server. 
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(TIME_PORT);

	// Send and receive data.
	bool exit = false;
	int bytesSent = 0;
	int bytesRecv = 0;
	char sendBuff[255];
	char recvBuff[255];
	int choice=0;
	bool skip = false; // To skip sending another request to server.
	while (!exit) {
		Menu();
		int option = getChoice();
		_itoa(option, sendBuff, 10);

		switch (option) {
		case 4:
			GetClientToServerDelayEstimation(connSocket, sendBuff, recvBuff, server);
			skip = true;
			break;
		case 5:
			MeasureRTT(connSocket, sendBuff, recvBuff, server);
			skip = true;
			break;
		case 12:
			GetTimeWithoutDateInCity(connSocket, sendBuff, server);
			skip = false;
			break;
		case 14:
			cout << "**__________________________________________________**\n";
			cout << "Thanks for using this useless app. See you next time!\n";
			cout << "**__________________________________________________**\n";
			skip = true;
			exit = true;
			break;
		default:
			skip = false;
			break;
		}

		if (!skip) {
			bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}
			cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

			// Gets the server's answer using simple recieve (no need to hold the server's address).
			bytesRecv = recv(connSocket, recvBuff, 255, 0);
			if (SOCKET_ERROR == bytesRecv)
			{
				cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}

			recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
			cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";

		}
	}
	// Closing connections and Winsock.
	cout << "Time Client: Closing Connection.\n";
	closesocket(connSocket);

	system("pause");
}