#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>
#include <windows.h>
#define TIME_PORT	27015




static const char* clientOptions[14] = { "Get Time","Get Time Without Date",
"Get Time Since Epoch","Get Client To Server Delay Estimation","Measure RTT",
"Get Time Without Date Or Seconds","Get Year",
"Get Month And Day","Get Second Since Begining Of Month",
"Get Week Of Year","Get Day Light Savings",
"Get Time Without Date In City","Measure Time Lap",
"Exit"};

static const char* city[5] = { "Tokyo", "Melbourne",
	"San Francisco", "Porto", "Other City" };