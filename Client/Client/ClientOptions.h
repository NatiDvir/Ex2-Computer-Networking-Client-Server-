#include "Client.h"

void Menu();
char getChoice();
//void GetClientToServerDelayEstimation();
//void MeasureRTT();
void GetTimeWithoutDateInCity(SOCKET connSocket, char* sendBuff, sockaddr_in server);
void cityMenu();
void GetClientToServerDelayEstimation(SOCKET connSocket, char* sendBuff, char* recvBuff, sockaddr_in server);
void MeasureRTT(SOCKET connSocket, char* sendBuff, char* recvBuff, sockaddr_in server);



