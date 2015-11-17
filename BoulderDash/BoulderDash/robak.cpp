#include "robak.h"


robak::robak()
{
    kod = 64;
    kolor = ROZOWY;
    tlo = CIEMNOCZERWONY;
    typ = "robak";
}


robak::~robak()
{
}

short robak::zw_x()
{
    return wsp_x;
}

short robak::zw_y()
{
    return wsp_y;
}

void robak::ink_wsp_x()
{
    wsp_x = wsp_x + 1;
}

void robak::dek_wsp_x()
{
    wsp_x = wsp_x - 1;
}

void robak::ink_wsp_y()
{
    wsp_y = wsp_y + 1;
}

void robak::dek_wsp_y()
{
    wsp_y = wsp_y - 1;
}