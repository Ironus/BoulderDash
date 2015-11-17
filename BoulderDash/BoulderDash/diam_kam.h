#pragma once
#include "ogolne.h"

using namespace std;

class diam_kam
{
protected:
    short kod;
    short kolor;
    short tlo;
    string typ;
    short wsp_x;
    short wsp_y;
    bool ruch;
public:
    diam_kam();
    ~diam_kam();
    void wypisz();
    string zw_typ();
    short zw_x();
    short zw_y();
    void zmien_wsp(short, short);
    void ustaw_ruch(bool);
    bool zw_ruch();
};

