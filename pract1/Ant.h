/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Ant.h
 * @brief Definición de la clase Ant, para representar la hormiga en la simulación.
 */

#ifndef ANT_H
#define ANT_H

#include <iosfwd>

class Tape; // forward declaration 
// se usa para evitar incluir Tape.h aquí, ya que Ant solo lo necesita en el método step().

/// Representa la hormiga que se mueve sobre Tape
class Ant {
public:
    /// Orientacion de la hormiga: Izquierda (0), Derecha (1), Arriba (2), Abajo (3)
    enum Orientation { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3 };

    /**
     * @brief Construye la hormiga en (x,y) con orientación (orient).
     * @param x coordenada X inicial
     * @param y coordenada Y inicial
     * @param orient orientación inicial (LEFT, RIGHT, UP, DOWN)
     */
    Ant(unsigned x, unsigned y, Orientation orient);

    /**
     * @brief Realiza un paso según las reglas de Langton:
     * Si la celda es blanca (0) entonces la pinta negra (1), gira a la izquierda y avanza.
     * Si la celda es negra (1) entonces la pinta blanca (0), gira a la derecha y avanza.
     *
     * @param tape referencia a la cinta donde está la hormiga
     * @return true si el paso se realizó y la hormiga quedó dentro de la cinta,
     *         false si el paso no se puede realizar porque implicaría salir de la cinta
     *         (en ese caso la hormiga no se mueve y la simulación debe terminar).
     */
    bool step(Tape & tape);

    /**
     * @brief Obtiene la coordenada X actual de la hormiga.
     */
    unsigned x() const;

    /**
     * @brief Obtiene la coordenada Y actual de la hormiga.
     */
    unsigned y() const;

    /**
     * @brief Obtiene la orientación actual.
     */
    Orientation orient() const;

    /**
     * @brief Representación de la hormiga como carácter según orientación: <, >, ^, v.
     * @return char con el símbolo de la hormiga
     */
    char symbol() const;

    /**
     * @brief Visualiza la hormiga en un flujo de salida, mostrando su posición y orientación.
     */
    friend std::ostream& operator<<(std::ostream& os, Ant const& ant);

private:
    // Representación interna de la posición y orientación de la hormiga.
    int m_x;
    int m_y;
    Orientation m_orient;

    void turnLeft();
    void turnRight();
};

#endif