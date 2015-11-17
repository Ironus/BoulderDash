#include "ogolne.h"
#include "menu.h"

void uru_gra()
{
    zmien_kolor(CZARNY, BIALY);
    system("cls");
    menu_start();
}

int main()
{
    konsola = GetStdHandle(STD_OUTPUT_HANDLE);
    gameplay = false;
    wylacz_kursor(0, 0);
    while (gameplay != true)
    {
        gra poziom;
        thread uruchomienie(&uru_gra);
        uruchomienie.join();
    }
    zmien_kolor(CZARNY, BIALY);
    return 0;
}