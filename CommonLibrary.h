#pragma once

#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <string_view>
#include <memory>
#include <functional>
#include <chrono>
#include <queue>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <conio.h>

#define SERVER_PORT 3000
#define PACKET_SIZE 16

#define UP_KEY 'W'
#define DOWN_KEY 'S'
#define LEFT_KEY 'A'
#define RIGHT_KEY 'D'

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 23

