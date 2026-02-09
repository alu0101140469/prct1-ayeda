/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Tape.h
 * @brief Definición de la clase Tape (cinta bidimensional)
 */

#ifndef TAPE_H
#define TAPE_H

#include <iosfwd>
#include <string>
#include <vector>

// Representa la cinta bidimensional de la hormiga de Langton.
class Tape {
public:
    /**
     * @brief Construye una cinta sizeX x sizeY, inicialmente todas blancas (false).
     * @param sizeX número de columnas (ancho)
     * @param sizeY número de filas (alto)
     */
    Tape(unsigned sizeX, unsigned sizeY);

    /**
     * @brief Obtiene el valor de la celda (x,y), donde true = negra, false = blanca.
     * @param x coordenada X (0..sizeX-1)
     * @param y coordenada Y (0..sizeY-1)
     * @return bool estado de la celda
     */
    bool get(unsigned x, unsigned y) const;

    /**
     * @brief Fija el valor de la celda (x,y), donde true = negra, false = blanca.
     * @param x coordenada X
     * @param y coordenada Y
     * @param value nuevo valor
     */
    void set(unsigned x, unsigned y, bool value);

    /**
     * @brief Indica si un par de coordenadas está dentro de la cinta.
     * @param x coordenada X
     * @param y coordenada Y
     * @return true si está dentro
     */
    bool isInside(int x, int y) const;

    /**
     * @brief Obtiene el ancho (sizeX)
     * @return ancho
     */
    unsigned width() const;

    /**
     * @brief Obtiene la altura (sizeY)
     * @return alto
     */
    unsigned height() const;

    /**
     * @brief Devuelve el carácter apropiado para mostrar la celda (x,y), siendo ' ' o 'X'.
     * @param x coordenada X
     * @param y coordenada Y
     * @return char representación textual
     */
    char cellChar(unsigned x, unsigned y) const;

    /**
     * @brief Visualiza la cinta en flujo (sin hormiga).
     * @param os flujo de salida
     * @param tape cinta a mostrar
     * @return flujo
     */
    friend std::ostream& operator<<(std::ostream& os, Tape const& tape);

private:
    // Representación interna de la cinta con un vector de filas, 
    // cada una un vector de celdas booleanas.
    unsigned m_sizeX;
    unsigned m_sizeY;
    std::vector< std::vector<bool> > m_grid;
};

#endif