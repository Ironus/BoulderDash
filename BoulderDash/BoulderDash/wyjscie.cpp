#include "wyjscie.h"


wyjscie::wyjscie()
{
    kod = 20;
    kolor = TURKUSOWY;
    tlo = CIEMNOCZERWONY;
    typ = "wyjscie";
    diamenty_zebrane = 0;
    diamenty_pozostale = 0;
}


wyjscie::~wyjscie()
{
}

void wyjscie::zwieksz_diamenty_zebrane()
{
    diamenty_zebrane++;
}

void wyjscie::zwieksz_diamenty_pozostale()
{
    diamenty_pozostale++;
}

void wyjscie::zeruj_diamenty()
{
    diamenty_zebrane = 0;
    diamenty_pozostale = 0;
}

int wyjscie::zwroc_diamenty_zebrane()
{
    return diamenty_zebrane;
}

int wyjscie::zwrot_diamenty_pozostale()
{
    return diamenty_pozostale;
}

bool wyjscie::sprawdz()
{
    if (diamenty_zebrane == diamenty_pozostale)
        return true;
    else
        return false;
}

short wyjscie::wsp_x()
{
    return x;
}

short wyjscie::wsp_y()
{
    return y;
}