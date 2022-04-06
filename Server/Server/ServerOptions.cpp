#include "ServerOptions.h"

void GetTime(char* sendBuff) {
	time_t timer;
	time(&timer);
	// Parse the current time to printable string.
	strcpy(sendBuff, ctime(&timer));
	sendBuff[strlen(sendBuff) - 1] = '\0'; //to remove the new-line from the created string
}

void GetTimeWithoutDate(char* sendBuff) {
	time_t timer;
	time(&timer);
    tm* justTime = localtime(&timer);
	strftime(sendBuff, 255, "%H:%M:%S", justTime);
}

void GetTimeSinceEpoch(char* sendBuff) {
	time_t timer;
	time(&timer);
	_ltoa(timer, sendBuff, 10);
	sendBuff[strlen(sendBuff) - 1] = '\0'; //to remove the new-line from the created string
}

void GetClientToServerDelayEstimation(char* sendBuff){

	DWORD tickTime = GetTickCount(); // GetTick returns DWORD
	_itoa(tickTime, sendBuff, 10);
}

void MeasureRTT(char* sendBuff) {
	GetTime(sendBuff);
}

void GetTimeWithoutDateOrSeconds(char* sendBuff) {
	time_t timer;
	time(&timer);
	tm* justTime = localtime(&timer);
	strftime(sendBuff, 255, "%H:%M", justTime);
}
void GetYear(char* sendBuff) {
	time_t timer;
	time(&timer);
	tm* justTime = localtime(&timer);
	strftime(sendBuff, 255, "%Y", justTime);
}

void GetMonthAndDay(char* sendBuff) {
	time_t timer;
	time(&timer);
	tm* justTime = localtime(&timer);
	strftime(sendBuff, 255, "%B,%A", justTime);
}

void GetSecondsSinceBeginningOfMonth(char* sendBuff) {
	time_t timer;
	time(&timer);
	tm* startTime = localtime(&timer);
	startTime->tm_hour = 0;
	startTime->tm_min = 0;
	startTime->tm_sec = 0;
	startTime->tm_mday = 1;
	time_t stime = mktime(startTime);
	int sec = difftime(timer, stime);
	_itoa(sec, sendBuff, 10);
}

void GetWeekOfYear(char* sendBuff) {
	time_t timer;
	time(&timer);
	tm* justTime = localtime(&timer);
	strftime(sendBuff, 255, "%U", justTime);
}

void GetDaylightSavings(char* sendBuff) {
	time_t timer;
	time(&timer);
	tm* justTime = localtime(&timer);
	_itoa(justTime->tm_isdst, sendBuff, 10);
}
void GetTimeWithoutDateInCity(SOCKET m_socket, char* recvBuff, char* sendBuff, sockaddr client_addr, int client_addr_len) {
	int bytesRecv = 0;

	bytesRecv = recvfrom(m_socket, recvBuff, 255 , 0, &client_addr, &client_addr_len); // Recieve another request for the city index.

	if (SOCKET_ERROR == bytesRecv)
	{
		cout << "UDP Server: Error at recvfrom(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		return;
	}

	recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
	cout << "UDP Server: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";

	time_t timer;
	time(&timer);

	tm* UTCTime = gmtime(&timer); // get utc time
	int city = atoi(recvBuff);

	switch (city)
	{
	case 1:
		UTCTime->tm_hour = (UTCTime->tm_hour + 9) % 24; //UTC +9
		strftime(sendBuff, 255, "Tokyo, Japan: %H:%M:%S", UTCTime);
		break;

	case 2:
		UTCTime->tm_hour = (UTCTime->tm_hour + 11) % 24; //UTC +11
		strftime(sendBuff, 255, "Melbourne, Australia: %H:%M:%S", UTCTime);
		break;

	case 3:
		UTCTime->tm_hour = (UTCTime->tm_hour + (-7)) % 24; //UTC -7
		strftime(sendBuff, 255, "San Francisco, USA: %H:%M:%S", UTCTime);
		break;

	case 4:
		UTCTime->tm_hour = (UTCTime->tm_hour + 0) % 24; //UTC +0
		strftime(sendBuff, 255, "Porto, Portugal: %H:%M:%S", UTCTime);
		break;

	default:
		strftime(sendBuff, 255, "UTC: %H:%M:%S", UTCTime);
		break;
	}

}

void MeasureTimeLap(char* sendBuff) {

	time_t ctime;
	long long currTime;
	if (isStart) {
		prevTime = time(&ctime);
		strcpy(sendBuff,"Time lap measurment has started.");
		isStart = false;
	}
	else {
		currTime = time(&ctime);
		_ltoa((currTime - prevTime), sendBuff, 10);
		strcat(sendBuff, " seconds.");
		isStart = true;
	}
	
}


