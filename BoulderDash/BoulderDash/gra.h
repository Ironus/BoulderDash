#pragma once
#include "ogolne.h"
#include "diam_kam.h"
#include "murek.h"
#include "kamien.h"
#include "diament.h"
#include "ramka.h"
#include "wyjscie.h"
#include "ziemia.h"
#include "gracz.h"
#include "robak.h"
#include "kurz.h"

class gra
{
private: 
    string levl;

public:
    gra();
    ~gra();
    void zmien_poziom(string);
    void wyswietl_poziom();
    void robaczki();
    void sprawdzenie();
    void czas();
    void koniec(string);
    void rozgrywka();
    void gra_start(string);
};

