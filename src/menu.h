/*********************************************************************
* Class Name: menu.h
* Author/s name: Daviz Muñoz y Daniel Aguado.
* Release/Creation date: 10/4/2024
* Class version: 1.0
* Class description: 
*
*
**********************************************************************/

#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

class Menu
{
    private:
        int numero_clientes;                        //Numeros de clientes que realizan busqueadas
        int busquedas_paralelas;                    //Maximo numero de busquedas a la vez.
        std::vector<std::string> conjunto_palabras; //Conjunto de palabras aleatorias

    public:
        void lanzarMenu() const;    //Logica del menu
        void PalabraAzar() const;   //Asignamos palabra al azar

};

#endif

//Incluir aquí el diccionario de palabras para añadir al azar al crear los usuarios
//Al crear los clientes, esperar 2 segundos para crear el otro