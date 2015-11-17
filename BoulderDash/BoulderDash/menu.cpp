#include "menu.h"

vector<string> MENU(6);
vector<string> MENU_poziom(6);
int pole, pole_w, pole_r, k = 1;
string level;
ostringstream konwersja;
bool close = false, lvl_break = false;

void uzupelnienie_MENU()
{
    MENU[0] = "MENU";
    MENU[1] = "ROZPOCZNIJ";
    MENU[2] = "INSTRUKCJE";
    MENU[3] = "STATYSTYKI";
    MENU[4] = "RESET";
    MENU[5] = "WYJSCIE";
}

void uzupelnienie_MENU_poziom()
{
    MENU_poziom[0] = "POZIOM 1";
    MENU_poziom[1] = "POZIOM 2";
    MENU_poziom[2] = "POZIOM 3";
    MENU_poziom[3] = "POZIOM 4";
    MENU_poziom[4] = "POZIOM 5";
    MENU_poziom[5] = "POZIOM 6";
}

void wyswietl_MENU_poziom()
{
    for (unsigned i = 0; i < MENU_poziom.size(); i++)
    {
        przestaw_kursor(30, i+1);
        if (zwroc_osiagi("odbl", i + 1) == 0)
            zmien_kolor(CZARNY, CIEMNOSZARY);
        cout << MENU_poziom[i];
        zmien_kolor(CZARNY, BIALY);
    }
}

void wybor_MENU_poziom()
{
    Sleep(50);
    pole_w = 1;
    przestaw_kursor(40, pole_w);
    cout << static_cast<char>(27);
    while (true)
    {
        if ((GetAsyncKeyState(VK_RETURN)) && (zwroc_osiagi("odbl", pole_w) == 1))
            break;
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            lvl_break = true;
            break;
        }
        if (GetAsyncKeyState(VK_UP))
        {
            przestaw_kursor(40, pole_w);
            cout << static_cast<char>(0);
            if (pole_w == 1)
                pole_w = 6;
            else
                pole_w--;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            przestaw_kursor(40, pole_w);
            cout << static_cast<char>(0);
            if (pole_w == 6)
                pole_w = 1;
            else
                pole_w++;
        }
        przestaw_kursor(40, pole_w);
        cout << static_cast<char>(27);
        Sleep(125);
    }
}
void wybor_RESET()
{
    Sleep(50);
    pole_r = 27;
    przestaw_kursor(pole_r, 8);
    cout << static_cast<char>(27);
    while (true)
    {
        if (GetAsyncKeyState(VK_RETURN))
            break;
        if (GetAsyncKeyState(VK_LEFT))
        {
            przestaw_kursor(pole_r, 8);
            cout << static_cast<char>(0);
            if (pole_r == 27)
                pole_r = 45;
            else
                pole_r = 27;
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            przestaw_kursor(pole_r, 8);
            cout << static_cast<char>(0);
            if (pole_r == 45)
                pole_r = 27;
            else
                pole_r = 45;
        }
        przestaw_kursor(pole_r, 8);
        cout << static_cast<char>(27);
        Sleep(125);
    }
}

void wybor_pozycji()
{
    pole = 4;
    przestaw_kursor(40, pole);
    cout << static_cast<char>(27);
    while (true)
    {
        if (GetAsyncKeyState(VK_RETURN))
            break;
        if (GetAsyncKeyState(VK_UP))
        {
            przestaw_kursor(40, pole);
            cout << static_cast<char>(0);
            if (pole == 4)
                pole = 8;
            else
                pole--;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            przestaw_kursor(40, pole);
            cout << static_cast<char>(0);
            if (pole == 8)
                pole = 4;
            else
                pole++;
        }
        przestaw_kursor(40, pole);
        cout << static_cast<char>(27);
        Sleep(100);
    }
    gra poziom;
    switch (pole)
    {
    case 4:
        system("cls");
        uzupelnienie_MENU_poziom();
        wyswietl_MENU_poziom();
        wybor_MENU_poziom();
        przestaw_kursor(40, pole_w);
        if (lvl_break == true)
        {
            lvl_break = false;
            poziom.~poziom();
            break;
        }
        cout << static_cast<char>(0);
        konwersja << pole_w;
        level = konwersja.str();
        przestaw_kursor(45, 20);
        poziom.gra_start(level);
        poziom.~poziom();
        break;
    case 5:
        system("cls");
        przestaw_kursor(4, 3);
        cout << "Witaj, Rockfordzie!";
        przestaw_kursor(4, 6);
        cout << "Pamietasz jak wspominalem ci o kopalniach diamentow?";
        przestaw_kursor(4, 7);
        cout << "Oczywiscie, ze pamietasz...";
        przestaw_kursor(4, 8);
        cout << "Widzialem blysk w twoim oku, gdy ci o tym mowilem.";
        przestaw_kursor(4, 9);
        cout << "Przygotowalem dla ciebie mapy, na ktorych sa zaznaczone kopalnie.";
        przestaw_kursor(4, 10);
        cout << "Na start dostaniesz tylko jedna,";
        przestaw_kursor(4, 11);
        cout << "kolejne - gdy zbierzesz WSZYSTKIE diamenty z poprzedniej";
        przestaw_kursor(4, 12);
        cout << "Tylko pamietaj! Kamienie SPADAJA gdy pod nimi jest pusta przestrzen!";
        przestaw_kursor(4, 13);
        cout << "Nie daj sie zgniesc!";
        przestaw_kursor(4, 14);
        cout << "Co to ja mialem jeszcze... A tak! Diamenty sa mocno osadzone w ziemii,";
        przestaw_kursor(4, 15);
        cout << "wiec nie musisz sie obawiac, ze spadna ci na glowe.";
        przestaw_kursor(4, 16);
        cout << "Unikaj robakow! Skubane sa szybkie, a jak cie ugryza, to konczy sie to";
        przestaw_kursor(4, 17);
        cout << "tragicznie. Bedziesz pod ziemia, wiec musisz sie spieszyc!";
        przestaw_kursor(4, 18);
        cout << "Wskaznik tlenu masz ze soba, sa na nim pokazane sekundy, po uplywie";
        przestaw_kursor(4, 19);
        cout << "ktorych... No! Niewazne! Ciebie i tak to nie spotka, prawda?";
        przestaw_kursor(4, 20);
        cout << "To juz wszystko. Teraz do roboty!";
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
        break;
    case 6:
        system("cls");
        przestaw_kursor(27, 1);
        cout << MENU[3];
        przestaw_kursor(25, 3);
        cout << "POZIOM";
        przestaw_kursor(32, 3);
        cout << "|";
        przestaw_kursor(35, 3);
        cout << "CZAS";
        przestaw_kursor(24, 4);
        for (int i = 0; i < 8; i++)
            cout << "-";
        cout << "|";
        for (int i = 0; i < 7; i++)
            cout << "-";
        for (int i = 0; i < 6 * 2; i++)
        {
            przestaw_kursor(27, 5 + i);
            cout << k;
            przestaw_kursor(32, 5 + i);
            cout << "|";
            przestaw_kursor(35, 5 + i);
            int wynik_czas = zwroc_osiagi("czas", k);
            if (wynik_czas < 100)
                cout << '0';
            if (wynik_czas < 10)
                cout << '0';
            cout << wynik_czas;
            k++;
            i++;
            przestaw_kursor(24, 5 + i);
            for (int i = 0; i < 8; i++)
                cout << "-";
            cout << "|";
            for (int i = 0; i < 7; i++)
                cout << "-";
        }
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
        break;
    case 7:
        system("cls");
        przestaw_kursor(29, 0);
        cout << MENU[4];
        przestaw_kursor(8, 4);
        cout << "Czy na pewno chcesz zresetowac osiagi?";
        przestaw_kursor(8, 5);
        cout << "Wszelkie postepy w rozgrywce zostana utracone.";
        przestaw_kursor(19, 8);
        cout << "RESETUJ";
        przestaw_kursor(38, 8);
        cout << "POWROT";
        wybor_RESET();
        if (pole_r == 27)
            utworz_osiagi();
        else
            break;
    case 8:
        system("cls");
        przestaw_kursor(15, 5);
        cout << "Specjalne podziekowania dla:";
        przestaw_kursor(3, 7);
        cout << "Wojciecha \"Stacha\" Olejnika za wsparcie merytoryczne";
        przestaw_kursor(3, 8);
        cout << "i nieopisana pomoc w rozwiazywaniu bledow kompilacji";
        przestaw_kursor(3, 10);
        cout << "Eweliny \"Eve\" Janowskiej za ciagle wspieranie w trudnych chwilach";
        przestaw_kursor(3, 11); 
        cout << "i niezlomnosc przy przepisywaniu mapek";
        przestaw_kursor(30, 13);
        cout << "Konrad \"Ironus\" Zierek";
        przestaw_kursor(5, 20);
        cout << "konradz94@o2.pl |";
        przestaw_kursor(23, 20);
        cout << "ironustlbb@gmail.com |";
        przestaw_kursor(46, 20);
        cout << "konzie@st.amu.edu.pl";
        gameplay = true;
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
        break;
    }
}
void wyswietl_menu()
{
    przestaw_kursor(30, 2);
    cout << MENU[0];
    przestaw_kursor(27, 4);
    cout << MENU[1];
    przestaw_kursor(27, 5);
    cout << MENU[2];
    przestaw_kursor(27, 6);
    cout << MENU[3];
    przestaw_kursor(29, 7);
    cout << MENU[4];
    przestaw_kursor(28, 8);
    cout << MENU[5];
}
void menu_start()
{
    close = false, lvl_break = false;
    pole = 4, pole_w = 1, pole_r = 27, k = 1;
    uzupelnienie_MENU();
    wyswietl_menu();
    wybor_pozycji();
}