#include "ogolne.h"

HANDLE konsola;
bool gameplay;

void wylacz_kursor(bool widocznosc, DWORD rozmiar)
{
    if (rozmiar == 0)
        rozmiar = 20;
    CONSOLE_CURSOR_INFO kursor;
    kursor.bVisible = widocznosc;
    kursor.dwSize = rozmiar;
    SetConsoleCursorInfo(konsola, &kursor);
}

void przestaw_kursor(short x, short y) 
{
    COORD pozycja = { x, y };

    SetConsoleCursorPosition(konsola, pozycja);
}

void zmien_kolor(short tlo_kolor, short txt_kolor)
{
    SetConsoleTextAttribute(konsola, txt_kolor + 16 * tlo_kolor);
}

void utworz_osiagi()
{
    char tab[lvlx4] = { 'T', '0', '0', '0', 'F', '0', '0', '0', 'F', '0', '0', '0', 'F', '0', '0', '0', 'F', '0', '0', '0', 'F', '0', '0', '0' };
    fstream lvl("donotopen.ironus", ios::binary | ios::out | ios::in);
    for (unsigned i = 0; i < lvlx4; i++)
        lvl.write(&tab[i], sizeof(char));
    lvl.close();
}

int zwroc_osiagi(string co, int poziom)
{
    char *tab2 = new char[lvlx4];
    fstream lvl("donotopen.ironus", ios::binary | ios::out | ios::in);
    for (int i = 0; i < lvlx4; i++)
    {
        lvl.seekg(i);
        lvl.read(&tab2[i], sizeof(char));
    }
    lvl.close();
    if (co == "czas")
    {
        vector<char> wynik(3);
        wynik[0] = tab2[(poziom - 1) * 4 + 1] - 48;
        wynik[1] = tab2[(poziom - 1) * 4 + 2] - 48;
        wynik[2] = tab2[(poziom - 1) * 4 + 3] - 48;
        int czas_gracza = wynik[0] * 100 + wynik[1] * 10 + wynik[2];
        return czas_gracza;
    }
    else
    {
        if (tab2[(poziom - 1) * 4] == 'T')
            return 1;
        else
            return 0;
    }
}

void zmien_osiagi(int poziom, int czas)
{
    fstream lvl("donotopen.ironus", ios::binary | ios::out | ios::in);
    lvl.seekp((poziom - 1) * 4 + 1);
    char *tab = new char[4];
    tab[0] = (czas / 100) + 48;
    czas %= 100;
    tab[1] = (czas / 10) + 48;
    czas %= 10;
    tab[2] = czas + 48;
    tab[3] = 'T';
    int licznik;
    if (poziom < lvlx4 / 4)
        licznik = 4;
    else
        licznik = 3;
    for (int i = 0; i < licznik; i++)
        lvl.write(&tab[i], sizeof(char));
    lvl.close();
}