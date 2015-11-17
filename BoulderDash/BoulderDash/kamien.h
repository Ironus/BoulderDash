#pragma once
#include "diam_kam.h"
#include "ogolne.h"

class kamien : public diam_kam
{
private:
    short wsp_x;
    short wsp_y;
    bool ruch;
public:
    kamien();
    ~kamien();
    void ustaw_wsp(short, short);
    void ink_wsp_x();
    void ink_wsp_y();
    void dek_wsp_y();
    short zw_x();
    short zw_y();
    void ustaw_ruch(bool);
    bool zw_ruch();
};

