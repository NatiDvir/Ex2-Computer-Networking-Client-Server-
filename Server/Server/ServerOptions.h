#include "Server.h"

void GetTime(char* sendBuff);
void GetTimeWithoutDate(char* sendBuff);
void GetTimeSinceEpoch(char* sendBuff);
void GetClientToServerDelayEstimation(char* sendBuff);
void MeasureRTT(char* sendBuff);
void GetTimeWithoutDateOrSeconds(char* sendBuff);
void GetYear(char* sendBuff);
void GetMonthAndDay(char* sendBuff);
void GetSecondsSinceBeginningOfMonth(char* sendBuff);
void GetWeekOfYear(char* sendBuff);
void GetDaylightSavings(char* sendBuff);
void GetTimeWithoutDateInCity(SOCKET m_socket, char* recvBuff, char* sendBuff, sockaddr client_addr, int client_addr_len);
void MeasureTimeLap(char* sendBuff);
