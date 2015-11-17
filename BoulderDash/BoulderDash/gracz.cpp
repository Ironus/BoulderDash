#include "gracz.h"


gracz::gracz()
{
    kod = 1;
    kolor = ZIELONY;
    tlo = CIEMNOCZERWONY;
    x = 0;
    y = 0;
    typ = "gracz";
}


gracz::~gracz()
{
}

void gracz::zm_wsp(short wsp1, short wsp2)
{
    x = wsp1;
    y = wsp2;
}

short gracz::wsp_x()
{
    return x;
}

short gracz::wsp_y()
{
    return y;
}