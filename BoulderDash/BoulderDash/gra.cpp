#include "gra.h"

vector<vector <diam_kam> > MAPA(0);
vector<kamien> KAMIENIE(0);
vector<robak> ROBAKI(0);
gracz g;
wyjscie w;
bool wygrana = false;
bool zgnieciony = false;
bool koniec_czasu = false;
bool ukaszony = false;
bool escape = false;
string sec_const;
int czas_gracza;
int najlepszy_czas = 1;
int rozgrywany_lvl = 0;

gra::gra()
{
}


gra::~gra()
{
}

void gra::zmien_poziom(string ilvl)
{
    levl = ilvl;
}

void gra::wyswietl_poziom()
{
    w.zeruj_diamenty();
    fstream txtlvl;
    char mapa_objekt;
    MAPA.resize(22);
    for (int i = 0; i < 22; i++)
        MAPA[i].resize(40);
    txtlvl.open(levl + ".txt", ios::in);
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            txtlvl >> mapa_objekt;
            if (mapa_objekt == static_cast<int>(68))
            {
                diament d;
                d.ustaw_wsp(i, j);
                MAPA[i][j] = d;
                w.zwieksz_diamenty_pozostale();
            }
            else if (mapa_objekt == static_cast<int>(71))
            {
                MAPA[i][j] = g;
                g.zm_wsp(i, j);
            }
            else if (mapa_objekt == static_cast<int>(75))
            {
                kamien k;
                k.ustaw_wsp(i, j);
                MAPA[i][j] = k;
            }
            else if (mapa_objekt == static_cast<int>(77))
            {
                murek m;
                m.zmien_wsp(i, j);
                MAPA[i][j] = m;
            }
            else if (mapa_objekt == static_cast<int>(82))
            {
                ramka r;
                r.zmien_wsp(i, j);
                MAPA[i][j] = r;
            }
            else if (mapa_objekt == static_cast<int>(83))
            {
                robak s;
                s.zmien_wsp(i, j);
                MAPA[i][j] = s;
            }
            else if (mapa_objekt == static_cast<int>(87))
            {
                w.zmien_wsp(i, j);
                MAPA[i][j] = w;
            }
            else if (mapa_objekt == static_cast<int>(90))
            {
                ziemia z;
                z.zmien_wsp(i, j);
                MAPA[i][j] = z;
            }
        }
    }
    txtlvl >> sec_const;
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            przestaw_kursor(j, i);
            MAPA[i][j].wypisz();
        }
    }
    przestaw_kursor(42, 3);
    cout << "Pozostaly";
    przestaw_kursor(46, 4);
    cout << "czas:";
    przestaw_kursor(41, 6);
    cout << "Twoj czas:";
    txtlvl.close();
}

void gra::koniec(string typ)
{
    Sleep(10);
    if (wygrana == true)
    {
        system("cls");
        przestaw_kursor(30, 7);
        cout << "WYGRANA";
        przestaw_kursor(20, 10);
        cout << "Twoj czas: " << czas_gracza << " sekund";
        przestaw_kursor(15, 11);
        cout << "Najlepszy czas: ";
        if (czas_gracza < najlepszy_czas || najlepszy_czas == 0)
        {
            najlepszy_czas = czas_gracza;
            zmien_osiagi(rozgrywany_lvl, czas_gracza);
        }
        if (najlepszy_czas < 100)
            cout << '0';
        if (najlepszy_czas < 10)
            cout << 0;
        cout << najlepszy_czas;
    }
    else
    {
        system("cls");
        przestaw_kursor(30, 7);
        cout << "PRZEGRANA";
        przestaw_kursor(25, 8);
        cout << "Zabity przez: ";
        if (typ == "robak")
            cout << "robaka";
        else if (typ == "czas")
            cout << "brak tlenu";
        else
            cout << "kamien";
        przestaw_kursor(10, 10);
        cout << "Zebranych diamentow: " << w.zwroc_diamenty_zebrane();
        przestaw_kursor(9, 11);
        cout << "Wszystkich diamentow: " << w.zwrot_diamenty_pozostale();
    }
    bool close = false;
    while (close == false)
    {
        for (char button = 0; button < 256; button++)
        {
            if (GetAsyncKeyState(button))
            {
                close = true;
                break;
            }
        }
        Sleep(1);
    }
    close = false;
}

void gra::robaczki()
{
    string outbuf;
    LPWORD buferkoloru;
    buferkoloru = new WORD[outbuf.length()];
    COORD cWhere;
    HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwCharsWritten;
    int opoznienie = 300;
    while(true)
    {
        if (wygrana == true || zgnieciony == true || koniec_czasu == true || escape == true || ukaszony == true)
            break;
        for (int i = 0; i < 22; i++)
        {
            for (int j = 0; j < 40; j++)
            {
                if (MAPA[i][j].zw_typ() == "robak")
                {
                    robak r;
                    r.zmien_wsp(i, j);
                    if (MAPA[i][j].zw_ruch() == true)
                        r.ustaw_ruch(true);
                    ROBAKI.push_back(r);
                }
            }
        }
        for (unsigned i = 0; i < ROBAKI.size(); i++)
        {
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(95);
            memset(buferkoloru, (CZARNY << 4) + CZARNY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            ROBAKI[i].ink_wsp_y();
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(64);
            memset(buferkoloru, (CIEMNOCZERWONY << 4) + ROZOWY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y()] = ROBAKI[i];
            kurz K;
            MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y() - 1] = K;
            if (MAPA[ROBAKI[i].zw_x() + 1][ROBAKI[i].zw_y()].zw_typ() == "gracz")
            {
                ukaszony = true;
                break;
            }
            if (wygrana == true || zgnieciony == true || koniec_czasu == true || escape == true)
                break;
        }
            Sleep(opoznienie);
        for (unsigned i = 0; i < ROBAKI.size(); i++)
        {
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(95);
            memset(buferkoloru, (CZARNY << 4) + CZARNY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            ROBAKI[i].ink_wsp_x();
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(64);
            memset(buferkoloru, (CIEMNOCZERWONY << 4) + ROZOWY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y()] = ROBAKI[i];
            kurz K;
            MAPA[ROBAKI[i].zw_x() - 1][ROBAKI[i].zw_y()] = K;
            if (MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y() - 1].zw_typ() == "gracz")
            {
                ukaszony = true;
                break;
            }
            if (wygrana == true || zgnieciony == true || koniec_czasu == true || escape == true)
                break;
        }
            Sleep(opoznienie);
        for (unsigned i = 0; i < ROBAKI.size(); i++)
        {
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(95);
            memset(buferkoloru, (CZARNY << 4) + CZARNY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            ROBAKI[i].dek_wsp_y();
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(64);
            memset(buferkoloru, (CIEMNOCZERWONY << 4) + ROZOWY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y()] = ROBAKI[i];
            kurz K;
            MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y() + 1] = K;
            if (MAPA[ROBAKI[i].zw_x() - 1][ROBAKI[i].zw_y()].zw_typ() == "gracz")
            {
                ukaszony = true;
                break;
            }
            if (wygrana == true || zgnieciony == true || koniec_czasu == true || escape == true)
                break;
        }
            Sleep(opoznienie);
        for (unsigned i = 0; i < ROBAKI.size(); i++)
        {
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(95);
            memset(buferkoloru, (CZARNY << 4) + CZARNY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            ROBAKI[i].dek_wsp_x();
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(64);
            memset(buferkoloru, (CIEMNOCZERWONY << 4) + ROZOWY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y()] = ROBAKI[i];
            kurz K;
            MAPA[ROBAKI[i].zw_x() + 1][ROBAKI[i].zw_y()] = K;
            if (MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y() + 1].zw_typ() == "gracz")
            {
                ukaszony = true;
                break;
            }
            if (wygrana == true || zgnieciony == true || koniec_czasu == true || escape == true)
                break;
        }
            Sleep(opoznienie);
    }
    ROBAKI.clear();
}

void gra::sprawdzenie()
{
    string outbuf;
    LPWORD buferkoloru;
    buferkoloru = new WORD[outbuf.length()];
    COORD cWhere;
    HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwCharsWritten;
    while (true)
    {
        for (int i = 0; i < 22; i++)
        {
            for (int j = 0; j < 40; j++)
            {
                if (MAPA[i][j].zw_typ() == "kamien")
                {
                    kamien k;
                    k.ustaw_wsp(i, j);
                    if (MAPA[i][j].zw_ruch() == true)
                        k.ustaw_ruch(true);
                    KAMIENIE.push_back(k);
                }
            }
        }
        if (wygrana == true || zgnieciony == true || koniec_czasu == true || escape == true || ukaszony == true)
            break;
        for (unsigned i = 0; i < KAMIENIE.size(); i++)
        {
            if (MAPA[KAMIENIE[i].zw_x() + 1][KAMIENIE[i].zw_y()].zw_typ() != "gracz" && MAPA[KAMIENIE[i].zw_x() + 1][KAMIENIE[i].zw_y()].zw_typ() != "kurz")
                KAMIENIE[i].ustaw_ruch(false);
            if (MAPA[KAMIENIE[i].zw_x() + 1][KAMIENIE[i].zw_y()].zw_typ() == "kurz")
            {
                cWhere.X = KAMIENIE[i].zw_y();
                cWhere.Y = KAMIENIE[i].zw_x();
                outbuf = static_cast<char>(95);
                memset(buferkoloru, (CZARNY << 4) + CZARNY, 1);
                WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
                WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
                KAMIENIE[i].ink_wsp_x();
                cWhere.X = KAMIENIE[i].zw_y();
                cWhere.Y = KAMIENIE[i].zw_x();
                outbuf = static_cast<char>(15);
                memset(buferkoloru, (CIEMNOCZERWONY << 4) + JASNOSZARY, 1);
                WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
                WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
                KAMIENIE[i].ustaw_ruch(true);
                MAPA[KAMIENIE[i].zw_x()][KAMIENIE[i].zw_y()] = KAMIENIE[i];
                kurz K;
                MAPA[KAMIENIE[i].zw_x() - 1][KAMIENIE[i].zw_y()] = K;
                Sleep(200);
                if (MAPA[KAMIENIE[i].zw_x() + 1][KAMIENIE[i].zw_y()].zw_typ() == "gracz")
                    zgnieciony = true;
            }
            if (MAPA[KAMIENIE[i].zw_x() + 1][KAMIENIE[i].zw_y()].zw_typ() == "kamien" && MAPA[KAMIENIE[i].zw_x()][KAMIENIE[i].zw_y() + 1].zw_typ() == "kurz" && MAPA[KAMIENIE[i].zw_x() + 1][KAMIENIE[i].zw_y() + 1].zw_typ() == "kurz")
            {
                cWhere.X = KAMIENIE[i].zw_y();
                cWhere.Y = KAMIENIE[i].zw_x();
                outbuf = static_cast<char>(95);
                memset(buferkoloru, (CZARNY << 4) + CZARNY, 1);
                WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
                WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
                KAMIENIE[i].ink_wsp_y();
                cWhere.X = KAMIENIE[i].zw_y();
                cWhere.Y = KAMIENIE[i].zw_x();
                outbuf = static_cast<char>(15);
                memset(buferkoloru, (CIEMNOCZERWONY << 4) + JASNOSZARY, 1);
                WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
                WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
                KAMIENIE[i].ustaw_ruch(true);
                MAPA[KAMIENIE[i].zw_x()][KAMIENIE[i].zw_y()] = KAMIENIE[i];
                kurz K;
                MAPA[KAMIENIE[i].zw_x()][KAMIENIE[i].zw_y() - 1] = K;
                Sleep(200);
            }
            if (MAPA[KAMIENIE[i].zw_x() + 1][KAMIENIE[i].zw_y()].zw_typ() == "kamien" && MAPA[KAMIENIE[i].zw_x()][KAMIENIE[i].zw_y() - 1].zw_typ() == "kurz" && MAPA[KAMIENIE[i].zw_x() + 1][KAMIENIE[i].zw_y() - 1].zw_typ() == "kurz")
            {
                cWhere.X = KAMIENIE[i].zw_y();
                cWhere.Y = KAMIENIE[i].zw_x();
                outbuf = static_cast<char>(95);
                memset(buferkoloru, (CZARNY << 4) + CZARNY, 1);
                WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
                WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
                KAMIENIE[i].dek_wsp_y();
                cWhere.X = KAMIENIE[i].zw_y();
                cWhere.Y = KAMIENIE[i].zw_x();
                outbuf = static_cast<char>(15);
                memset(buferkoloru, (CIEMNOCZERWONY << 4) + JASNOSZARY, 1);
                WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
                WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
                KAMIENIE[i].ustaw_ruch(true);
                MAPA[KAMIENIE[i].zw_x()][KAMIENIE[i].zw_y()] = KAMIENIE[i];
                kurz K;
                MAPA[KAMIENIE[i].zw_x()][KAMIENIE[i].zw_y() + 1] = K;
                Sleep(200);
            }
        }
        KAMIENIE.resize(0);
    }
}

void gra::czas()
{
    string sec = sec_const;
    string czas_g;
    czas_gracza = 0;
    int odejmowanie_czasu = 1;
    string outbuf;
    LPWORD buferkoloru;
    buferkoloru = new WORD[outbuf.length()];
    COORD cWhere;
    HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwCharsWritten;
    while (true)
    {
        if (zgnieciony == true || wygrana == true || escape == true || ukaszony == true)
            break;
        if (odejmowanie_czasu == 0)
        {
            koniec_czasu = true;
            break;
        }
        cWhere.X = 52;
        cWhere.Y = 4;
        outbuf = sec;
        istringstream iss(sec);
        iss >> odejmowanie_czasu;
        odejmowanie_czasu--;
        ostringstream ss;
        ss << odejmowanie_czasu;
        sec = ss.str();
        if (sec.length() == 2)
            sec.insert(0, " ");
        if (sec.length() == 1)
            sec.insert(0, "  ");
        WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
        cWhere.X = 52;
        cWhere.Y = 6;
        ostringstream ss2;
        ss2 << czas_gracza;
        czas_g = ss2.str();
        if (czas_g.length() == 2)
            czas_g.insert(0, " ");
        if (czas_g.length() == 1)
            czas_g.insert(0, "  ");
        outbuf = czas_g;
        WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
        czas_gracza++;
        Sleep(1000);
    }
}

void gra::rozgrywka()
{
    int opoznienie = 125;
    while (true)
    {
        if (zgnieciony == true)
        {
            wygrana = false;
            koniec("kamien");
            break;
        }
        if (koniec_czasu == true)
        {
            wygrana = false;
            koniec("czas");
            break;
        }
        if (ukaszony == true)
        {
            wygrana = false;
            koniec("robak");
            break;
        }
        przestaw_kursor(g.wsp_y(), g.wsp_x());
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            escape = true;
            break;
        }
        else if (GetAsyncKeyState(VK_UP))
        {
            if ((MAPA[g.wsp_x() - 1][g.wsp_y()].zw_typ()) == "ziemia")
            {
                kurz k;
                MAPA[g.wsp_x()][g.wsp_y()] = k;
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                MAPA[g.wsp_x() - 1][g.wsp_y()] = g;
                g.zm_wsp(g.wsp_x() - 1, g.wsp_y());
                przestaw_kursor(g.wsp_y(), g.wsp_x());
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
            }
            else if ((MAPA[g.wsp_x() - 1][g.wsp_y()].zw_typ()) == "diament")
            {
                kurz k;
                MAPA[g.wsp_x()][g.wsp_y()] = k;
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                MAPA[g.wsp_x() - 1][g.wsp_y()] = g;
                g.zm_wsp(g.wsp_x() - 1, g.wsp_y());
                przestaw_kursor(g.wsp_y(), g.wsp_x());
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                w.zwieksz_diamenty_zebrane();
            }
            else if ((MAPA[g.wsp_x() - 1][g.wsp_y()].zw_typ()) == "kurz")
            {
                kurz k;
                MAPA[g.wsp_x()][g.wsp_y()] = k;
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                MAPA[g.wsp_x() - 1][g.wsp_y()] = g;
                g.zm_wsp(g.wsp_x() - 1, g.wsp_y());
                przestaw_kursor(g.wsp_y(), g.wsp_x());
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
            }
            else if ((MAPA[g.wsp_x() - 1][g.wsp_y()].zw_typ()) == "wyjscie")
            {
                if (w.zwroc_diamenty_zebrane() == w.zwrot_diamenty_pozostale())
                {
                    wygrana = true;
                    g.zm_wsp(g.wsp_x() - 1, g.wsp_y());
                    koniec(MAPA[g.wsp_x() - 1][g.wsp_y()].zw_typ());
                    break;
                }
            }
            else if ((MAPA[g.wsp_x() - 1][g.wsp_y()].zw_typ()) == "robak")
            {
                wygrana = false;
                koniec(MAPA[g.wsp_x() - 1][g.wsp_y()].zw_typ());
                break;
            }
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            if ((MAPA[g.wsp_x() + 1][g.wsp_y()].zw_typ()) == "ziemia")
            {
                kurz k;
                MAPA[g.wsp_x()][g.wsp_y()] = k;
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                MAPA[g.wsp_x() + 1][g.wsp_y()] = g;
                g.zm_wsp(g.wsp_x() + 1, g.wsp_y());
                przestaw_kursor(g.wsp_y(), g.wsp_x());
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
            }
            else if ((MAPA[g.wsp_x() + 1][g.wsp_y()].zw_typ()) == "diament")
            {
                kurz k;
                MAPA[g.wsp_x()][g.wsp_y()] = k;
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                MAPA[g.wsp_x() + 1][g.wsp_y()] = g;
                g.zm_wsp(g.wsp_x() + 1, g.wsp_y());
                przestaw_kursor(g.wsp_y(), g.wsp_x());
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                w.zwieksz_diamenty_zebrane();
            }
            else if ((MAPA[g.wsp_x() + 1][g.wsp_y()].zw_typ()) == "kurz")
            {
                kurz k;
                MAPA[g.wsp_x()][g.wsp_y()] = k;
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                MAPA[g.wsp_x() + 1][g.wsp_y()] = g;
                g.zm_wsp(g.wsp_x() + 1, g.wsp_y());
                przestaw_kursor(g.wsp_y(), g.wsp_x());
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
            }
            else if ((MAPA[g.wsp_x() + 1][g.wsp_y()].zw_typ()) == "wyjscie")
            {
                if (w.zwroc_diamenty_zebrane() == w.zwrot_diamenty_pozostale())
                {
                    wygrana = true;
                    g.zm_wsp(g.wsp_x() + 1, g.wsp_y());
                    koniec(MAPA[g.wsp_x() + 1][g.wsp_y()].zw_typ());
                    break;
                }
            }
            else if ((MAPA[g.wsp_x() + 1][g.wsp_y()].zw_typ()) == "robak")
            {
                wygrana = false;
                koniec(MAPA[g.wsp_x() + 1][g.wsp_y()].zw_typ());
                break;
            }
        }
        else if (GetAsyncKeyState(VK_LEFT))
        {
            if ((MAPA[g.wsp_x()][g.wsp_y() - 1].zw_typ()) == "ziemia")
            {
                kurz k;
                MAPA[g.wsp_x()][g.wsp_y()] = k;
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                MAPA[g.wsp_x()][g.wsp_y() - 1] = g;
                g.zm_wsp(g.wsp_x(), g.wsp_y() - 1);
                przestaw_kursor(g.wsp_y(), g.wsp_x());
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
            }
            else if ((MAPA[g.wsp_x()][g.wsp_y() - 1].zw_typ()) == "diament")
            {
                kurz k;
                MAPA[g.wsp_x()][g.wsp_y()] = k;
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                MAPA[g.wsp_x()][g.wsp_y() - 1] = g;
                g.zm_wsp(g.wsp_x(), g.wsp_y() - 1);
                przestaw_kursor(g.wsp_y(), g.wsp_x());
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                w.zwieksz_diamenty_zebrane();
            }
            else if ((MAPA[g.wsp_x()][g.wsp_y() - 1].zw_typ()) == "kamien")
            {
                if ((MAPA[g.wsp_x()][g.wsp_y() - 2].zw_typ()) == "kurz")
                {
                    kurz k;
                    kamien km;
                    MAPA[g.wsp_x()][g.wsp_y()] = k;
                    MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                    MAPA[g.wsp_x()][g.wsp_y() - 2] = km;
                    przestaw_kursor(g.wsp_y() - 2, g.wsp_x());
                    MAPA[g.wsp_x()][g.wsp_y() - 2].wypisz();
                    MAPA[g.wsp_x()][g.wsp_y() - 1] = g;
                    g.zm_wsp(g.wsp_x(), g.wsp_y() - 1);
                    przestaw_kursor(g.wsp_y(), g.wsp_x());
                    MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                }
            }
            else if ((MAPA[g.wsp_x()][g.wsp_y() - 1].zw_typ()) == "kurz")
            {
                kurz k;
                MAPA[g.wsp_x()][g.wsp_y()] = k;
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                MAPA[g.wsp_x()][g.wsp_y() - 1] = g;
                g.zm_wsp(g.wsp_x(), g.wsp_y() - 1);
                przestaw_kursor(g.wsp_y(), g.wsp_x());
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
            }
            else if ((MAPA[g.wsp_x()][g.wsp_y() - 1].zw_typ()) == "wyjscie")
            {
                if (w.zwroc_diamenty_zebrane() == w.zwrot_diamenty_pozostale())
                {
                    wygrana = true;
                    g.zm_wsp(g.wsp_x(), g.wsp_y() - 1);
                    koniec(MAPA[g.wsp_x()][g.wsp_y() - 1].zw_typ());
                    break;
                }
            }
            else if ((MAPA[g.wsp_x()][g.wsp_y() - 1].zw_typ()) == "robak")
            {
                wygrana = false;
                koniec(MAPA[g.wsp_x()][g.wsp_y() - 1].zw_typ());
                break;
            }
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            if ((MAPA[g.wsp_x()][g.wsp_y() + 1].zw_typ()) == "ziemia")
            {
                kurz k;
                MAPA[g.wsp_x()][g.wsp_y()] = k;
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                MAPA[g.wsp_x()][g.wsp_y() + 1] = g;
                g.zm_wsp(g.wsp_x(), g.wsp_y() + 1);
                przestaw_kursor(g.wsp_y(), g.wsp_x());
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
            }
            else if ((MAPA[g.wsp_x()][g.wsp_y() + 1].zw_typ()) == "diament")
            {
                kurz k;
                MAPA[g.wsp_x()][g.wsp_y()] = k;
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                MAPA[g.wsp_x()][g.wsp_y() + 1] = g;
                g.zm_wsp(g.wsp_x(), g.wsp_y() + 1);
                przestaw_kursor(g.wsp_y(), g.wsp_x());
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                w.zwieksz_diamenty_zebrane();
            }
            else if ((MAPA[g.wsp_x()][g.wsp_y() + 1].zw_typ()) == "kamien")
            {
                if ((MAPA[g.wsp_x()][g.wsp_y() + 2].zw_typ()) == "kurz")
                {
                    kurz k;
                    kamien km;
                    MAPA[g.wsp_x()][g.wsp_y()] = k;
                    MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                    MAPA[g.wsp_x()][g.wsp_y() + 2] = km;
                    przestaw_kursor(g.wsp_y() + 2, g.wsp_x());
                    MAPA[g.wsp_x()][g.wsp_y() + 2].wypisz();
                    MAPA[g.wsp_x()][g.wsp_y() + 1] = g;
                    g.zm_wsp(g.wsp_x(), g.wsp_y() + 1);
                    przestaw_kursor(g.wsp_y(), g.wsp_x());
                    MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                }
            }
            else if ((MAPA[g.wsp_x()][g.wsp_y() + 1].zw_typ()) == "kurz")
            {
                kurz k;
                MAPA[g.wsp_x()][g.wsp_y()] = k;
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
                MAPA[g.wsp_x()][g.wsp_y() + 1] = g;
                g.zm_wsp(g.wsp_x(), g.wsp_y() + 1);
                przestaw_kursor(g.wsp_y(), g.wsp_x());
                MAPA[g.wsp_x()][g.wsp_y()].wypisz();
            }
            else if ((MAPA[g.wsp_x()][g.wsp_y() + 1].zw_typ()) == "wyjscie")
            {
                if (w.zwroc_diamenty_zebrane() == w.zwrot_diamenty_pozostale())
                {
                    wygrana = true;
                    g.zm_wsp(g.wsp_x(), g.wsp_y() + 1);
                    koniec(MAPA[g.wsp_x()][g.wsp_y() + 1].zw_typ());
                    break;
                }
            }
            else if ((MAPA[g.wsp_x()][g.wsp_y() + 1].zw_typ()) == "robak")
            {
                wygrana = false;
                koniec(MAPA[g.wsp_x()][g.wsp_y() + 1].zw_typ());
                break;
            }
        }
        Sleep(opoznienie);
    }
}

void gra::gra_start(string poziom)
{
    wygrana = false;
    zgnieciony = false;
    koniec_czasu = false;
    escape = false;
    ukaszony = false;
    system("cls");   
    string l_poz;
    l_poz = poziom.substr(poziom.size() - 1);
    zmien_poziom(l_poz);
    int levl;
    istringstream iss(l_poz);
    iss >> levl;
    najlepszy_czas = zwroc_osiagi("czas", levl);
    rozgrywany_lvl = levl;
    wyswietl_poziom();
    thread robsy(&gra::robaczki, this);
    thread spr(&gra::sprawdzenie, this);
    thread time(&gra::czas, this);
    rozgrywka();
    robsy.join();
    spr.join();
    time.join();
}
