/*********************************************************************
*
* Class Name: manejador.h
* Author/s name: David Muñoz y Daniel Aguado
* Release/Creation date: 6/4/2024
* Class version: 2.0
* Class description: CABECERA de la clase manejador.cpp. Clase empleada
*                    para dividir el libro entre los hilos establecidos
*                    por parametro
*
**********************************************************************
*/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#ifndef MANEJADOR_H
#define MANEJADOR_H

int ContarLineas(std::string nombreFichero);                          //Cuenta las lineas del fichero.
std::vector<std::string> LeerFichero(std::string libro);              //Crea una cola de lineas de libro.
std::vector<std::string> split(std::string str, std::string patron);  //Divide la colas de linea en tantas divisiones como hilos haya, por el patron "espacio"
std::string toLower(std::string str);                                 //Convierte todas las letras en minusculas por si dieran problemas.

#endif