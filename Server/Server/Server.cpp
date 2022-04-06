#include "ServerOptions.h"


// TO DO: CLIENT DELAY , MEASURE RTT , ANNOTATIONS //

void main()
{

	WSAData wsaData;

	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Time Server: Error at WSAStartup()\n";
		return;
	}


	SOCKET m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


	if (INVALID_SOCKET == m_socket)
	{
		cout << "Time Server: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	
	sockaddr_in serverService;
	
	serverService.sin_family = AF_INET;

	serverService.sin_addr.s_addr = INADDR_ANY;	//inet_addr("127.0.0.1");
	
	serverService.sin_port = htons(TIME_PORT);

	if (SOCKET_ERROR == bind(m_socket, (SOCKADDR*)&serverService, sizeof(serverService)))
	{
		cout << "Time Server: Error at bind(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		return;
	}

	// Waits for incoming requests from clients.

	// Send and receive data.
	sockaddr client_addr;
	int client_addr_len = sizeof(client_addr);
	int bytesSent = 0;
	int bytesRecv = 0;
	char sendBuff[255];
	char recvBuff[255];
	int optionReq = 0;
	bool bexit = false;
	cout << "Time Server: Wait for clients' requests.\n";

	while (true)
	{
		bytesRecv = recvfrom(m_socket, recvBuff, 255, 0, &client_addr, &client_addr_len);
		if (SOCKET_ERROR == bytesRecv)
		{
			cout << "Time Server: Error at recvfrom(): " << WSAGetLastError() << endl;
			closesocket(m_socket);
			WSACleanup();
			return;
		}

		recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
		cout << "Time Server: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
		optionReq = atoi(recvBuff);
		// Answer client's request by the current time.

		switch (optionReq) {
		case 1:
			GetTime(sendBuff);
			break;

		case 2:
			GetTimeWithoutDate(sendBuff);
			break;

		case 3:
			GetTimeSinceEpoch(sendBuff);
			break;

		case 4:
			GetClientToServerDelayEstimation(sendBuff);
			break;

		case 5:
			MeasureRTT(sendBuff);
			break;

		case 6:
			GetTimeWithoutDateOrSeconds(sendBuff);
			break;

		case 7:
			GetYear(sendBuff);
			break;

		case 8:
			GetMonthAndDay(sendBuff);
			break;

		case 9:
			GetSecondsSinceBeginningOfMonth(sendBuff);
			break;

		case 10:
			GetWeekOfYear(sendBuff);
			break;

		case 11:
			GetDaylightSavings(sendBuff);
			break;

		case 12:
			GetTimeWithoutDateInCity(m_socket, recvBuff, sendBuff, client_addr, client_addr_len);
			break;

		case 13:

			MeasureTimeLap(sendBuff);
			break;
	
		default:
			break;
		}

		bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&client_addr, client_addr_len);
		if (SOCKET_ERROR == bytesSent)
		{
			cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
			closesocket(m_socket);
			WSACleanup();
			return;
		}

		cout << "Time Server: Sent: " << bytesSent << "\\" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";
	}

	// Closing connections and Winsock.
	cout << "Time Server: Closing Connection.\n";
	closesocket(m_socket);
	WSACleanup();
}