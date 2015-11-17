#include "diament.h"


diament::diament()
{
    kod = 4;
    kolor = NIEBIESKI;
    tlo = CIEMNOCZERWONY;
    typ = "diament";
    ruch = false;
}


diament::~diament()
{
}

void diament::ustaw_wsp(short x, short y)
{
    wsp_x = x;
    wsp_y = y;
}

void diament::ink_wsp_x()
{
    wsp_x = wsp_x + 1;
}

void diament::ink_wsp_y()
{
    wsp_y = wsp_y + 1;
}

void diament::dek_wsp_y()
{
    wsp_y = wsp_y - 1;
}

short diament::zw_x()
{
    return wsp_x;
}

short diament::zw_y()
{
    return wsp_y;
}

void diament::ustaw_ruch(bool stan)
{
    ruch = stan;
}

bool diament::zw_ruch()
{
    return ruch;
}
