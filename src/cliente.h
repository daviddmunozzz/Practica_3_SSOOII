/*********************************************************************
* Class Name: cliente.h
* Author/s name: Daviz Muñoz y Daniel Aguado.
* Release/Creation date: 10/4/2024
* Class version: 1.0
* Class description: 
*
**********************************************************************
*/

#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

class Cliente
{
    private:
        int id_cliente;             //Identificador único del cliente.
        int prioridad;              //Prioridad para el uso del procesador. 0 = cuenta gratuida, 1 = cuenta con saldo, 2 = cuenta ilimitada
        int saldo;                  //Saldo disponible en caso de usar cuenta con saldo.
        std::string nombre_usuario; //Nombre de usuario para que se reconozca más fácilmente.
        std::string palabra_busqueda;//Palabra que se desea buscar.

    public:
        Cliente(int id, int prio, int saldo, std::string nombre, std::string palabra);
        void operator ()() const;
        void toString () const;

};

#endif