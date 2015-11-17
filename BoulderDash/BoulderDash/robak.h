#pragma once
#include "diam_kam.h"
#include "ogolne.h"

class robak :
    public diam_kam
{
public:
    robak();
    ~robak();
    short zw_x();
    short zw_y();
    void ink_wsp_x();
    void dek_wsp_x();
    void ink_wsp_y();
    void dek_wsp_y();
};

