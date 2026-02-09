/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file main.cc
 * @brief Programa principal que lee fichero de inicialización y lanza la simulación.
 *
 * Ejecutar:
 *   ./langton <fichero-inicializacion>
 *
 * Formato del fichero:
 * Línea 1: sizeX sizeY
 * Línea 2: antX antY orient (orient: 0=Left,1=Right,2=Up,3=Down)
 * Línea 3..n: x y (coordenadas de celdas negras)
 */

#include "Simulator.h"
#include "Ant.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>

/**
* @brief Función principal que inicia la simulación de la hormiga de Langton.
*/
int main(int argc, char* argv[])
{
    // Verificar que se ha proporcionado un fichero de inicialización
    if (argc < 2) {
        std::cerr << "Como ejecutar: " << argv[0] << " <fichero-inicializacion>\n";
        return 1;
    }

    // Abrir el fichero de inicialización
    std::string filename = argv[1];
    std::ifstream ifs(filename);
    // Verificar que el fichero se ha abierto correctamente
    if (!ifs) {
        std::cerr << "No se pudo abrir el fichero: " << filename << '\n';
        return 1;
    }

    // Leer el tamaño del tablero
    unsigned sizeX = 0, sizeY = 0;
    if (!(ifs >> sizeX >> sizeY)) {
        // Si no se pueden leer los tamaños, mostrar un error
        std::cerr << "Formato incorrecto en la línea 1 (sizeX sizeY)\n";
        return 1;
    }

    // Leer la posición inicial de la hormiga y su orientación
    unsigned antX = 0, antY = 0;
    int orientInt = 0;
    // Verificar que se pueden leer los valores de la hormiga
    if (!(ifs >> antX >> antY >> orientInt)) {
        std::cerr << "Formato incorrecto en la línea 2 (antX antY orient)\n";
        return 1;
    }
    // Verificar que la orientación es válida (0 a 3)
    if (orientInt < 0 || orientInt > 3) {
        std::cerr << "Orientación incorrecta (debe ser 0 al 3)\n";
        return 1;
    }
    // Convertir la orientación a la enumeración correspondiente
    Ant::Orientation orient = static_cast<Ant::Orientation>(orientInt);

    // Leer las coordenadas de las celdas negras
    std::vector<std::pair<unsigned, unsigned>> blacks;
    unsigned bx, by;
    while (ifs >> bx >> by) {
        // Añadir la coordenada a la lista de celdas negras
        blacks.emplace_back(bx, by);
    }

    try {
        // Crear el simulador con los parámetros leídos
        Simulator sim(sizeX, sizeY, antX, antY, orient);
        // Inicializar las celdas negras en el simulador
        sim.initializeBlacks(blacks);

        // Ejecutar la simulación de forma interactiva
        sim.runInteractive();

        // Preguntar al usuario si desea guardar el estado de la simulación
        std::cout << "¿Quieres guardar el estado de la simulación en un fichero? (s/n): ";
        std::string respuesta;
        std::getline(std::cin, respuesta); // Leer respuesta
        if (respuesta.empty()) std::getline(std::cin, respuesta); // Leer respuesta si está vacía
        // Comprobar si la respuesta es afirmativa
        if (!respuesta.empty() && (respuesta[0] == 's' || respuesta[0] == 'S')) {
            std::cout << "Nombre de fichero de salida: ";
            std::string out;
            std::getline(std::cin, out); // Leer nombre de fichero de salida
            if (out.empty()) out = "salida.txt"; // Usar nombre por defecto si está vacío
            if (sim.saveState(out)) { // Guardar estado en el fichero
                std::cout << "Estado guardado en " << out << '\n';
            } else {
                std::cout << "Error guardando en " << out << '\n';
            }
        }
    } catch (std::exception const& e) { // Cualquier excepción que ocurra durante la simulación
        std::cerr << "Error en el simulador: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
