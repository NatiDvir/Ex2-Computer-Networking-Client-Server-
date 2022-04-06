#include "ClientOptions.h"

void Menu() {
	cout << "Choose an option from the menu:\n";
	for (int i = 0; i < 14;i++) {
		cout << i + 1 << "." << clientOptions[i] << "\n";
	}
}
char getChoice() {

	int choice;
	bool isValidChoice = false;

	while (!isValidChoice)
	{
		cin >> choice;

		if (choice < 0 || choice > 14)
		{
			cout << "Invalid request , Please choose another option.\n";
		}
		else
		{
			isValidChoice = true;
		}
	}

	return choice;
}

void GetClientToServerDelayEstimation(SOCKET connSocket, char* sendBuff, char* recvBuff, sockaddr_in server)
{
	int bytesSent = 0;
	int bytesRecv = 0;
	DWORD prevTime = 0;
	DWORD currTime = 0;
	double avgTime = 0;
	int i;

	for (i = 0; i < 100; i++) // Sending 100 requests
	{
		bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
		if (SOCKET_ERROR == bytesSent)
		{
			cout << "UDP Client: Error at sendto(): " << WSAGetLastError() << endl;
			closesocket(connSocket);
			WSACleanup();
			return;
		}
	}


	for (i = 0; i < 100; i++) // Receiving 100 requests
	{
		
		bytesRecv = recv(connSocket, recvBuff, 255, 0);
		if (SOCKET_ERROR == bytesRecv)
		{
			cout << "UDP Client: Error at recv(): " << WSAGetLastError() << endl;
			closesocket(connSocket);
			WSACleanup();
			return;
		}
		recvBuff[bytesRecv] = '\0';
		currTime = atol(recvBuff);

		if (i == 0)
		{
			prevTime = currTime;

		}
		else {
			avgTime += (currTime - prevTime);
			prevTime = currTime;
		}    
	}

	avgTime = avgTime / 99;
	cout << "The estimated client to server delay is: " << avgTime << " milliseconds.\n";
}

void MeasureRTT(SOCKET connSocket, char* sendBuff, char* recvBuff, sockaddr_in server) {

	DWORD reqTime = 0;
	DWORD resTime = 0;
	int bytesSent = 0;
	int bytesRecv = 0;
	double avgTime = 0;
	int i;


	for (i = 0; i < 100; i++) // Sending 100 requests
	{
		bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
		if (SOCKET_ERROR == bytesSent)
		{
			cout << "UDP Client: Error at sendto(): " << WSAGetLastError() << endl;
			closesocket(connSocket);
			WSACleanup();
			return;
		}

		reqTime = GetTickCount();

		bytesRecv = recv(connSocket, recvBuff, 255, 0);
		if (SOCKET_ERROR == bytesRecv)
		{
			cout << "UDP Client: Error at recv(): " << WSAGetLastError() << endl;
			closesocket(connSocket);
			WSACleanup();
			return;
		}
		resTime = GetTickCount();
		avgTime += (resTime - reqTime);

	}
		avgTime = avgTime / 100;
		cout << "The average round trip time is: " << avgTime << " milliseconds.\n ";

}

void GetTimeWithoutDateInCity(SOCKET socket,char* sendBuff,sockaddr_in server) {
	int bytesSent = 0;
	// sent 12
	bytesSent = sendto(socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "UDP Client: Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(socket);
		WSACleanup();
		return;
	}
	cityMenu();
	int cityChoice=0;
	bool check = false;

	while (!check)
	{
		cin >> cityChoice;

		if (cityChoice < 1 || cityChoice > 5)
		{
			cout << "Please choose a number of a valid city.\n";
		}
		else
		{
			_itoa(cityChoice, sendBuff, 10);
			check = true;
		}
	}
}

void cityMenu() {
	cout << "Choose a city from the menu:\n";
	for (int i = 0; i < 5; i++) {
		cout << i + 1 << "." << city[i] << "\n";
	}
}