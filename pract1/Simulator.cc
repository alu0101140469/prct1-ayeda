/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Simulator.cc
 * @brief Implementación de Simulator que usa Tape y Ant para gestionar la simulación de la hormiga.
 */

#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

/**
* @brief Crea un simulador dado el tamaño de cinta, posición y orientación de la hormiga.
* @param sizeX ancho
* @param sizeY alto
* @param antX pos X inicial de la hormiga
* @param antY pos Y inicial de la hormiga
* @param orient orientación inicial de la hormiga
*/
Simulator::Simulator(unsigned sizeX, unsigned sizeY,
                     unsigned antX, unsigned antY, Ant::Orientation orient)
    // Inicializa la cinta y la hormiga con los parámetros dados, y el contador de pasos a 0
    : m_tape(sizeX, sizeY), m_ant(antX, antY, orient), m_stepCount(0)
{
    // Verifica que la posición inicial de la hormiga esté dentro de los límites de la cinta
    if (!m_tape.isInside(static_cast<int>(antX), static_cast<int>(antY))) {
        throw std::invalid_argument("Error Simulador: Posición inicial de la hormiga fuera de los límites de la cinta.");
    }
}

/**
* @brief Inicializa celdas negras desde una lista de coordenadas.
* @param blacks vector de pares (x,y)
*/
void Simulator::initializeBlacks(const std::vector<std::pair<unsigned, unsigned>>& blacks)
{
    // Inicializa las celdas negras en la cinta según las coordenadas dadas
    for (auto const & p : blacks) {
        unsigned x = p.first;
        unsigned y = p.second;
        // Verifica que la coordenada esté dentro de la cinta antes de ponerla negra
        if (m_tape.isInside(static_cast<int>(x), static_cast<int>(y))) {
            m_tape.set(x, y, true);
        }
    }
}

/**
* @brief Muestra la cinta con la hormiga en su posición actual.
*/
void Simulator::display() const
{
    // Muestra la cinta pero sobreescribe la celda con el símbolo de la hormiga
    for (unsigned y = 0; y < m_tape.height(); ++y) {
        for (unsigned x = 0; x < m_tape.width(); ++x) {
            // Muestra el símbolo de la hormiga si está en esta celda
            if (x == m_ant.x() && y == m_ant.y()) {
                std::cout << m_ant.symbol();
            } else {
                // Si no hay hormiga, muestra el carácter de la celda
                std::cout << m_tape.cellChar(x, y);
            }
        }
        std::cout << '\n';
    }
    // Muestra el número de paso actual
    std::cout << "Step: " << m_stepCount << '\n';
}

/**
* @brief Ejecuta N pasos (si N==0 se ejecuta hasta que la hormiga salga o se termine).
* @param steps número de pasos a ejecutar (0 = hasta final)
* @return número de pasos efectivamente ejecutados
*/
unsigned Simulator::runSteps(unsigned steps)
{
    unsigned executed = 0;
    // Ejecuta pasos hasta que se alcance el número dado o la hormiga no pueda avanzar
    while ( (steps == 0 || executed < steps) ) {
        // Ejecuta un paso de la hormiga y actualiza el contador de pasos
        bool ok = m_ant.step(m_tape);
        ++m_stepCount;
        if (!ok) {
            // Si step devuelve false la simulación termina por haber alcanzado el borde
            std::cout << "La hormiga no puede avanzar (borde alcanzado). Simulación terminada.\n";
            return executed;
        }
        // Incrementa el contador de pasos ejecutados
        ++executed;
    }
    // Si se ejecutaron todos los pasos pedidos, devuelve el número de pasos ejecutados
    return executed;
}

/**
* @brief Ejecuta la simulación de forma interactiva.
*        Tiene la opción de pasos uno a uno o ejecutar N pasos.
*/
void Simulator::runInteractive()
{
    std::cout << "Simulación de la Hormiga de Langton\n";
    std::cout << "Opciones:\n";
    std::cout << "  1) Paso a paso (pulsa ENTER para avanzar, 'q' + ENTER para salir)\n";
    std::cout << "  2) Ejecutar N pasos (introduce N, si 0 = hasta que termine)\n";
    std::cout << "Elige el modo (1 o 2): ";

    int modo = 1;
    // Lee la opción del usuario, si no es válida se queda en modo 1 por defecto
    if (!(std::cin >> modo)) {
        std::cin.clear();
        modo = 1;
    }
    std::string dummy; // para limpiar el buffer de entrada
    std::getline(std::cin, dummy); // limpia resto de la línea

    // Modo 2
    if (modo == 2) {
        std::cout << "Introduce número de pasos a ejecutar (0 = hasta final): ";
        unsigned N = 0;
        // Lee el número de pasos a ejecutar, si no es válido se ejecuta hasta el final
        if (!(std::cin >> N)) {
            N = 0;
        }
        std::getline(std::cin, dummy); // limpia resto de la línea
        // Ejecuta en bloques mostrando cada 100 pasos para no saturar la salida
        unsigned executed = 0;
        // Si N==0 se ejecuta hasta que la hormiga alcance el borde o se termine
        while (N == 0 || executed < N) {
            // Ejecuta un bloque de pasos (100 o el resto si N es menor) y muestra el estado después de cada bloque
            unsigned toRun = (N == 0) ? 100u : std::min<unsigned>(100u, N - executed);
            // Ejecuta el bloque de pasos y actualiza el contador de pasos ejecutados
            unsigned real = runSteps(toRun == 0 ? 0 : toRun);
            executed += real;
            // Muestra el estado actual después de cada bloque
            display();
            if (real < toRun) {
                // terminó por borde
                break;
            }
            if (N == 0) {
                // si N==0 pedimos cada bloque si continuar o parar
                std::cout << "Continuar? (ENTER = continuar  /  q + ENTER = salir): ";
                std::string s;
                std::getline(std::cin, s); // lee la respuesta del usuario
                // Si el usuario introduce q se sale del bucle
                if (!s.empty() && s[0] == 'q') {
                    break;
                }
            }
        }
    } else {
        // Modo 1
        std::cout << "Modo paso a paso. Pulsa ENTER para dar un paso, 'q' + ENTER para salir.\n";
        while (true) {
            // Muestra el estado actual de la cinta y la hormiga
            display();
            std::cout << "Pulsa ENTER para avanzar, 'q' + ENTER para salir: ";
            std::string line;
            std::getline(std::cin, line); // lee la entrada del usuario
            if (!line.empty() && line[0] == 'q') { // Si el usuario introduce q se sale del bucle
                std::cout << "Simulación parada por el usuario.\n";
                break;
            }
            // Ejecuta un paso de la hormiga y actualiza el contador de pasos
            bool ok = m_ant.step(m_tape);
            ++m_stepCount;
            // Si step devuelve false la simulación termina por haber alcanzado el borde
            if (!ok) {
                display();
                std::cout << "La hormiga no puede avanzar (borde alcanzado). Simulación terminada.\n";
                break;
            }
        }
    }
}

/**
* @brief Guarda el estado actual en un fichero
* @param filename nombre de fichero de salida
* @return true si se salvó correctamente
*/
bool Simulator::saveState(const std::string& filename) const
{
    std::ofstream ofs(filename);
    if (!ofs) return false;

    // Línea 1: Tamaño de la cinta
    // Línea 2: Posición inicial y orientación de la hormiga
    // Línea 3..n: Posiciones de las celdas negras

    // Escribe el tamaño de la cinta
    ofs << m_tape.width() << ' ' << m_tape.height() << '\n';
    // Escribe la posición y orientación de la hormiga
    ofs << m_ant.x() << ' ' << m_ant.y() << ' ' << static_cast<int>(m_ant.orient()) << '\n';

    // Escribe las posiciones de las celdas negras
    for (unsigned y = 0; y < m_tape.height(); ++y) {
        for (unsigned x = 0; x < m_tape.width(); ++x) {
            // Si la celda es negra, escribe su coordenada
            if (m_tape.get(x, y)) {
                // Escribe la coordenada de la celda negra
                ofs << x << ' ' << y << '\n';
            }
        }
    }

    return true;
}
