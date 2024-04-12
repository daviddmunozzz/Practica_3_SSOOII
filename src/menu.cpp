/*********************************************************************
* Class Name: menu.h
* Author/s name: Daviz Muñoz y Daniel Aguado.
* Release/Creation date: 10/4/2024
* Class version: 1.0
* Class description: Menu para introducir los parametros para crear los clientes
*
**********************************************************************/

#include <iostream>
#include <string>
#include <vector>

void lanzarMenu();
void PalabraAzar();

class Menu
{
    private:
        std::vector<std::string> conjunto_palabras  = {"hombres"};  //Pool de palabras de las que obtener la palabra de busqueda.
        int numero_clientes;                                        //Numeros de clientes que realizan busqueadas
        int busquedas_paralelas;                                    //Maximo numero de busquedas a la vez.
        std::vector<std::string> conjunto_palabras;                 //Conjunto de palabras aleatorias

    public:
        void lanzarMenu()
        {
            std::cout << "Bienvenido al buscador SSOOIGLE" << std::endl;



        };
};