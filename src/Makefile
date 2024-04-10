EXE := exec/
CD := mkdir -p

CC := g++
CCOMPILE := -o
THREAD := -pthread
STDIO := -std=c++17
FILE := SSOOIIGLE
LIBRARY := ../library/
EXTENSION := .cpp
LK := ln
DL := rm
all: dir file

file:
	$(CC) $(FILE)$(EXTENSION) $(CCOMPILE) $(EXE)$(FILE) classBusqueda$(EXTENSION) Manejador$(EXTENSION) $(THREAD) $(STDIO)
dir:
	$(CD) $(DIR) $(EXE)

open:
	nano $(FILE)$(EXTENSION)

solution1:
	./$(EXE)$(FILE) $(LIBRARY)El\ Oro\ Y\ La\ Ceniza\ -\ Abecassis\ Eliette\ .txt oro 3

solution2:
	./$(EXE)$(FILE) $(LIBRARY)SEAMOS\ PERSONAS\ DE\ INFLUENCIA\ -\ JOHN\ MAXWELL.txt personas 13

solution3:
	./$(EXE)$(FILE) $(LIBRARY)21\ LEYES\ DEL\ LIDERAZGO\ -\ JOHN\ C.\ MAXWELL.txt liderazgo 50

clean:
	$(DL) $(EXE)$(FILE)
	$(DL)dir $(EXE)
