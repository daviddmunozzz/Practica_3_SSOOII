/*********************************************************************
* Class Name: cliente.h
* Author/s name: Daviz Muñoz y Daniel Aguado.
* Release/Creation date: 17/4/2024
* Class version: 1.0
* Class description: Clase abstracta cliente de la que derivan gratuida,
*                    saldo e ilimitada.
*
**********************************************************************
*/

#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <atomic>
#include "PeticionPago.h"
#include "PeticionBusqueda.h"

class Cliente
{
    private:
        int id_cliente;                 //Identificador único del cliente.
        std::string palabra_busqueda;   //Palabra que se desea buscar.
        std::queue<PeticionBusqueda> colaPetBusqueda;

    public:
        Cliente(int _id_cliente, std::string _palabra_busqueda, std::queue<PeticionBusqueda>& _petBusqueda)
        : id_cliente(_id_cliente), palabra_busqueda(_palabra_busqueda), colaPetBusqueda(_petBusqueda) {}
        void operator ()() const;
        void depositarPeticion() const;
};

class Gratuita: public Cliente
{
    private:
        std::atomic <int> busquedas_restantes = 5;                                              //Busquedas por gastar al usuario gratuido
    public:
        Gratuita(int _id_cliente, std::string _palabra_busqueda, std::queue<PeticionBusqueda>& colaPetBusqueda)
        : Cliente(_id_cliente, _palabra_busqueda, colaPetBusqueda) {} //Constructor cliente gratuida
};

class Saldo: public Cliente
{
    private:
       std::atomic <int> creditos = 7;                                            //Creditos que dispone el cliente para gastar
    public: 
        Saldo(int _id_cliente, std::string _palabra_busqueda, std::queue<PeticionBusqueda>& colaPetBusqueda)
        : Cliente(_id_cliente, _palabra_busqueda, colaPetBusqueda) {} //Constructor cliente gratuida
};

class Ilimitada: public Cliente
{
    private:
    public:  
        Ilimitada(int _id_cliente, std::string _palabra_busqueda, std::queue<PeticionBusqueda>& colaPetBusqueda)
        : Cliente(_id_cliente, _palabra_busqueda, colaPetBusqueda) {} 
};

#endif