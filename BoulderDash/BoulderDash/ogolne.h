#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <future>

using namespace std;

#define CZARNY 0
#define CIEMNONIEBIESKI 1
#define CIEMNOZIELONY 2
#define CIEMNOTURKUSOWY 3
#define CIEMNOCZERWONY 4
#define CIEMNOROZOWY 5
#define CIEMNOZOLTY 6
#define JASNOSZARY 7
#define CIEMNOSZARY 8
#define NIEBIESKI 9
#define ZIELONY 10
#define TURKUSOWY 11
#define CZERWONY 12
#define ROZOWY 13
#define ZOLTY 14
#define BIALY 15

#define lvlx4 24

extern HANDLE konsola;
extern bool gameplay;

void wylacz_kursor(bool, DWORD);
void przestaw_kursor(short, short);
void zmien_kolor(short, short);
void utworz_osiagi();
int zwroc_osiagi(string, int);
void zmien_osiagi(int, int);