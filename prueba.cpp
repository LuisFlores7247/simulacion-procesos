#include <iostream>
#include <conio.h>
#include <windows.h>

int main() {
    char key;

    while (true) {
        if (_kbhit()) {  // Verifica si se ha presionado una tecla
            key = _getch();  // Obtiene la tecla presionada

            // Verifica qué tecla se ha presionado
            switch (key) {
                case 72: // Tecla de flecha arriba
                    std::cout << "Flecha arriba presionada" << std::endl;
                    break;
                case 80: // Tecla de flecha abajo
                    std::cout << "Flecha abajo presionada" << std::endl;
                    break;
                case 75: // Tecla de flecha izquierda
                    std::cout << "Flecha izquierda presionada" << std::endl;
                    break;
                case 77: // Tecla de flecha derecha
                    std::cout << "Flecha derecha presionada" << std::endl;
                    break;
                case 97: // Tecla de flecha derecha
                    std::cout << "Flecha a presionada" << std::endl;
                    break;
                case '\r':
                    std::cout << "Enter presiondado" << std::endl;
                    break;
                default:
                    std::cout << "Tecla no reconocida" << std::endl;
                    break;
            }
        }
        std:: cout << "Delay...";

        Sleep(0);
        // Aquí puedes poner el resto de tu lógica del programa
    }

    return 0;
}
