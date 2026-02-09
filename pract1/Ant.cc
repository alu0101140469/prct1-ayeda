/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Ant.cc
 * @brief Implementación de la clase Ant, para representar la hormiga en la simulación.
 */

#include "Ant.h"
#include "Tape.h"
#include <stdexcept>
#include <iostream>

/**
 * @brief Construye la hormiga en (x,y) con orientación (orient).
 * @param x coordenada X inicial
 * @param y coordenada Y inicial
 * @param orient orientación inicial (LEFT, RIGHT, UP, DOWN)
 */
Ant::Ant(unsigned x, unsigned y, Orientation orient)
    : m_x(static_cast<int>(x)), m_y(static_cast<int>(y)), m_orient(orient)
{
}

/**
 * @brief Obtiene la coordenada X actual de la hormiga.
 */
unsigned Ant::x() const
{
    return static_cast<unsigned>(m_x);
}

/**
 * @brief Obtiene la coordenada Y actual de la hormiga.
 */
unsigned Ant::y() const
{
    return static_cast<unsigned>(m_y);
}

/**
 * @brief Obtiene la orientación actual.
 */
Ant::Orientation Ant::orient() const
{
    return m_orient;
}

/**
 * @brief Representación de la hormiga como carácter según orientación: <, >, ^, v.
 * @return char con el símbolo de la hormiga
 */
char Ant::symbol() const
{
    switch (m_orient) {
    case LEFT:  return '<';
    case RIGHT: return '>';
    case UP:    return '^';
    case DOWN:  return 'v';
    default:    return '?';
    }
}

/**
 * @brief Visualiza la hormiga en un flujo de salida, mostrando su posición y orientación.
 */
std::ostream& operator<<(std::ostream& os, Ant const& ant)
{
    os << ant.symbol();
    return os;
}

/**
 * @brief Gira la hormiga hacia la izquierda.
 */
void Ant::turnLeft()
{
    switch (m_orient) {
    case LEFT:  m_orient = DOWN; break;
    case DOWN:  m_orient = RIGHT; break;
    case RIGHT: m_orient = UP; break;
    case UP:    m_orient = LEFT; break;
    }
}

/**
 * @brief Gira la hormiga hacia la derecha.
 */
void Ant::turnRight()
{
    switch (m_orient) {
    case LEFT:  m_orient = UP; break;
    case UP:    m_orient = RIGHT; break;
    case RIGHT: m_orient = DOWN; break;
    case DOWN:  m_orient = LEFT; break;
    }
}

/**
 * @brief Realiza un paso según las reglas de Langton.
 */
bool Ant::step(Tape & tape)
{
    // Comprueba que la posición actual está dentro de la cinta.
    if (!tape.isInside(m_x, m_y)) {
        // La hormiga no puede estar fuera
        return false;
    }

    // Lee color actual
    bool isBlack = tape.get(static_cast<unsigned>(m_x), static_cast<unsigned>(m_y));

    // Aplica reglas, se pinta y gira
    if (!isBlack) {
        // blanca -> negra, gira izq
        tape.set(static_cast<unsigned>(m_x), static_cast<unsigned>(m_y), true);
        turnLeft();
    } else {
        // negra -> blanca, gira dcha
        tape.set(static_cast<unsigned>(m_x), static_cast<unsigned>(m_y), false);
        turnRight();
    }

    // Calcula la nueva posición sin mover todavía, ya que podría ser inválida
    int nx = m_x;
    int ny = m_y;
    switch (m_orient) {
    case LEFT:  nx = m_x - 1; break;
    case RIGHT: nx = m_x + 1; break;
    case UP:    ny = m_y - 1; break;
    case DOWN:  ny = m_y + 1; break;
    }

    // Si el movimiento implicaría salir de la cinta, la simulación termina y no se mueve.
    // Por ejemplo, si la hormiga llega al borde o si la simulación empieza y está orientada hacia el borde.
    if (!tape.isInside(nx, ny)) {
        return false;
    }

    // Realiza el movimiento
    m_x = nx;
    m_y = ny;
    return true;
}
