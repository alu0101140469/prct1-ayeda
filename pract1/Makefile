CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
OBJS = main.o Tape.o Ant.o Simulator.o
DEPS = Tape.h Ant.h Simulator.h
TARGET = langton

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc $(DEPS)
	$(CXX) $(CXXFLAGS) -c main.cc

Tape.o: Tape.cc Tape.h
	$(CXX) $(CXXFLAGS) -c Tape.cc

Ant.o: Ant.cc Ant.h Tape.h
	$(CXX) $(CXXFLAGS) -c Ant.cc

Simulator.o: Simulator.cc Simulator.h Tape.h Ant.h
	$(CXX) $(CXXFLAGS) -c Simulator.cc

clean:
	rm -f $(OBJS) $(TARGET)



Crea una modificación del código realizando lo siguiente y mostrando únicamente la parte nueva o modificada del código:
crear una función countActiveCells que devuelva al final de la simulación por pantalla.


Aquí tienes solo las partes nuevas o modificadas (manteniendo el estilo y Doxygen):


---

Simulator.h (añadido el prototipo)

/**
     * @brief Cuenta el número de celdas activas (negras) en la cinta.
     * @return número de celdas negras
     */
    unsigned countActiveCells() const;


---

Simulator.cc (implementación)

unsigned Simulator::countActiveCells() const
{
    unsigned count = 0;
    for (unsigned y = 0; y < m_tape.height(); ++y) {
        for (unsigned x = 0; x < m_tape.width(); ++x) {
            if (m_tape.get(x, y)) {
                ++count;
            }
        }
    }
    return count;
}


---

main.cc (inserta esta línea justo después de sim.runInteractive(); y antes de preguntar por salvar)

// Mostrar número de celdas activas al final de la simulación
    unsigned active = sim.countActiveCells();
    std::cout << "Celdas activas (negras) al final de la simulación: " << active << '\n';


---
