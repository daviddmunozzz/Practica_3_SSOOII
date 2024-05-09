TARGET = SSOOGLEII

# Compilador y opciones de compilación
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread

# Archivos fuente
SRCS = Buscador.cpp Cliente.cpp manager.cpp sistemaPago.cpp Utilidades.cpp

# Archivos objeto
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS) $(TARGET)
