# Archivos fuente
SRCS = Buscador.cpp Cliente.cpp manager.cpp Utilidades.cpp

# Directorio de los archivos de encabezado
HEADER_DIR = ../include

# Archivos de encabezado
HEADERS = $(wildcard $(HEADER_DIR)/*.hpp)

# Compilador y opciones de compilación
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread

# Archivos objeto
OBJS = $(SRCS:.cpp=.o)

# Nombre del programa ejecutable
TARGET = SSOOIIGLE

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp $(HEADERS)
    $(CXX) $(CXXFLAGS) -c $< -o $@ -I$(HEADER_DIR)

clean:
    rm -f $(OBJS) $(TARGET)
