#include "../../headers/global/structure.h"

void iniTabP(tabP p)
{
    for (int i = 0; i < 10; i++)
    {
        strcpy(p[i].nom, "AAAAAAA");
        p[i].ID = i + 1;
        p[i].scoreNavale = -1;
        p[i].scorePoker = -1;
        p[i].scoreLoto = -1;
        p[i].scoreSudoku = -1;
        p[i].scoreTotal = -1;
    }
}
