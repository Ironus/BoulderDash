#pragma once
#include "diam_kam.h"
class gracz :
    public diam_kam
{
private:
    int x;
    int y;
public:
    gracz();
    ~gracz();
    void zm_wsp(short, short);
    short wsp_x();
    short wsp_y();
};

