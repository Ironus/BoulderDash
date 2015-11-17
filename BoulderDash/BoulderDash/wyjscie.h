#pragma once
#include "diam_kam.h"
class wyjscie :
    public diam_kam
{
private:
    int diamenty_zebrane;
    int diamenty_pozostale;
    int x;
    int y;
public:
    wyjscie();
    ~wyjscie();
    void zwieksz_diamenty_zebrane();
    void zwieksz_diamenty_pozostale();
    void zeruj_diamenty();
    int zwroc_diamenty_zebrane();
    int zwrot_diamenty_pozostale();
    bool sprawdz();
    short wsp_x();
    short wsp_y();
};

