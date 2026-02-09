/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Tape.cc
 * @brief Implementación de la clase Tape (cinta bidimensional)
 */

#include "Tape.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>

/**
* @brief Construye una cinta sizeX x sizeY, inicialmente todas blancas (false).
* @param sizeX número de columnas (ancho)
* @param sizeY número de filas (alto)
*/
Tape::Tape(unsigned sizeX, unsigned sizeY)
    : m_sizeX(sizeX), m_sizeY(sizeY), m_grid(sizeY, std::vector<bool>(sizeX, false))
{
    if (sizeX == 0 || sizeY == 0) {
        // Lanzar excepción si el tamaño es inválido
        throw std::invalid_argument("El tamaño de la cinta debe ser mayor que 0");
    }
}

/**
* @brief Obtiene el valor de la celda (x,y), donde true = negra, false = blanca.
* @param x coordenada X (0..sizeX-1)
* @param y coordenada Y (0..sizeY-1)
* @return bool estado de la celda
*/
bool Tape::get(unsigned x, unsigned y) const
{
    if (x >= m_sizeX || y >= m_sizeY) {
        // Lanzar excepción si las coordenadas están fuera de rango
        throw std::out_of_range("Tape::get: coordenadas fuera de rango");
    }
    return m_grid[y][x];
}

/**
* @brief Fija el valor de la celda (x,y), donde true = negra, false = blanca.
* @param x coordenada X
* @param y coordenada Y
* @param value nuevo valor
*/
void Tape::set(unsigned x, unsigned y, bool value)
{
    if (x >= m_sizeX || y >= m_sizeY) {
        // Lanzar excepción si las coordenadas están fuera de rango
        throw std::out_of_range("Tape::set: coordenadas fuera de rango");
    }
    m_grid[y][x] = value;
}

/**
* @brief Indica si un par de coordenadas está dentro de la cinta.
* @param x coordenada X
* @param y coordenada Y
* @return true si está dentro
*/
bool Tape::isInside(int x, int y) const
{
    return x >= 0 && y >= 0 && static_cast<unsigned>(x) < m_sizeX && static_cast<unsigned>(y) < m_sizeY;
}

/**
* @brief Obtiene el ancho (sizeX)
* @return ancho
*/
unsigned Tape::width() const
{
    return m_sizeX;
}

/**
* @brief Obtiene la altura (sizeY)
* @return alto
*/
unsigned Tape::height() const
{
    return m_sizeY;
}

/**
* @brief Devuelve el carácter apropiado para mostrar la celda (x,y), siendo ' ' o 'X'.
* @param x coordenada X
* @param y coordenada Y
* @return char representación textual
*/
char Tape::cellChar(unsigned x, unsigned y) const
{
    return get(x, y) ? 'X' : ' ';
}

/**
* @brief Visualiza la cinta en flujo (sin hormiga).
* @param os flujo de salida
* @param tape cinta a mostrar
* @return flujo
*/
std::ostream& operator<<(std::ostream& os, Tape const& tape)
{
    // Imprime cada fila de la cinta, usando cellChar para cada celda
    for (unsigned y = 0; y < tape.m_sizeY; ++y) {
        for (unsigned x = 0; x < tape.m_sizeX; ++x) {
            os << tape.cellChar(x, y);
        }
        os << '\n';
    }
    return os;
}
