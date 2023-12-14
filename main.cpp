#include "Funciones.h"
#include "colores.h"

using namespace std;

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    int consoleWidth = consoleInfo.dwSize.X;

    srand(time(NULL));

    system("cls");

    iniciarSimulacion(consoleWidth);

    int leftPadding = (consoleWidth - 40) / 2;

    gotoxy(leftPadding, 6);
    system("pause");
    system("cls");

    return 0;
}
