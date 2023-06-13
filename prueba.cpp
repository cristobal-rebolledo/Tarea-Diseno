#include <iostream>
#include <vector>

void encontrarPosibilidades(int posicionActual, int objetivo, std::vector<int>& saltos, std::vector<int>& camino) {
    if (posicionActual == objetivo) {
        // Se ha llegado al objetivo, imprimir el camino encontrado
        std::cout << "Camino encontrado: ";
        for (int salto : camino) {
            std::cout << salto << " ";
        }
        std::cout << objetivo << std::endl;
    } else if (posicionActual < objetivo) {
        // Continuar explorando posibilidades
        for (int salto : saltos) {
            camino.push_back(salto);
            encontrarPosibilidades(posicionActual + salto, objetivo, saltos, camino);
            camino.pop_back();
        }
    }
}

int main() {
    int objetivo = 10;
    std::vector<int> saltos = {1, 2, 4, 8};
    std::vector<int> camino;

    encontrarPosibilidades(1, objetivo, saltos, camino);

    return 0;
}
