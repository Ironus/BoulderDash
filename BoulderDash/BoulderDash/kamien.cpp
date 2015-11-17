#include "kamien.h"

kamien::kamien()
{
    kod = 15;
    kolor = JASNOSZARY;
    tlo = CIEMNOCZERWONY;
    typ = "kamien";
    ruch = false;
}


kamien::~kamien()
{
}

void kamien::ustaw_wsp(short x, short y)
{
    wsp_x = x;
    wsp_y = y;
}

void kamien::ink_wsp_x()
{
    wsp_x = wsp_x + 1;
}

void kamien::ink_wsp_y()
{
    wsp_y = wsp_y + 1;
}

void kamien::dek_wsp_y()
{
    wsp_y = wsp_y - 1;
}

short kamien::zw_x()
{
    return wsp_x;
}

short kamien::zw_y()
{
    return wsp_y;
}

void kamien::ustaw_ruch(bool stan)
{
    ruch = stan;
}

bool kamien::zw_ruch()
{
    return ruch;
}