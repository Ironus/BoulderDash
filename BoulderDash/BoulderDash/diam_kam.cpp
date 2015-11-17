#include "diam_kam.h"

using namespace std;

diam_kam::diam_kam()
{
   
}


diam_kam::~diam_kam()
{
}

void diam_kam::wypisz()
{
    zmien_kolor(tlo, kolor);
    cout << static_cast<char>(kod);
    zmien_kolor(CZARNY, BIALY);
}

string diam_kam::zw_typ()
{
    return typ;
}

short diam_kam::zw_x()
{
    return wsp_x;
}

short diam_kam::zw_y()
{
    return wsp_y;
}

void diam_kam::zmien_wsp(short x, short y)
{
    wsp_x = x;
    wsp_y = y;
}

void diam_kam::ustaw_ruch(bool stan)
{
    ruch = stan;
}

bool diam_kam::zw_ruch()
{
    return ruch;
}