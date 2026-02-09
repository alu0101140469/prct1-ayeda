/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Simulator.h
 * @brief Definición de la clase Simulator que usa Tape y Ant para gestionar la simulación de la hormiga.
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Ant.h"
#include "Tape.h"
#include <string>

/**
 * @brief Gestiona la simulación y contiene una Tape y una Ant, y controla los pasos.
 */
class Simulator {
public:
    /**
     * @brief Crea un simulador dado el tamaño de cinta, posición y orientación de la hormiga.
     * @param sizeX ancho
     * @param sizeY alto
     * @param antX pos X inicial de la hormiga
     * @param antY pos Y inicial de la hormiga
     * @param orient orientación inicial de la hormiga
     */
    Simulator(unsigned sizeX, unsigned sizeY,
              unsigned antX, unsigned antY, Ant::Orientation orient);

    /**
     * @brief Inicializa celdas negras desde una lista de coordenadas
     * @param blacks vector de pares (x,y)
     */
    void initializeBlacks(const std::vector<std::pair<unsigned, unsigned>>& blacks);

    /**
     * @brief Ejecuta la simulación de forma interactiva.
     *        Tiene la opción de pasos uno a uno o ejecutar N pasos.
     */
    void runInteractive();

    /**
     * @brief Ejecuta N pasos (si N==0 se ejecuta hasta que la hormiga salga o se termine).
     * @param steps número de pasos a ejecutar (0 = hasta final)
     * @return número de pasos efectivamente ejecutados
     */
    unsigned runSteps(unsigned steps);

    /**
     * @brief Guarda el estado actual en un fichero
     * @param filename nombre de fichero de salida
     * @return true si se salvó correctamente
     */
    bool saveState(const std::string& filename) const;

private:
    Tape m_tape;
    Ant  m_ant;
    unsigned m_stepCount; // Contador de pasos ejecutados

    void display() const; // Muestra la cinta con la hormiga en su posición actual
};

#endif