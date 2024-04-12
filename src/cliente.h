/*********************************************************************
* Class Name: cliente.h
* Author/s name: Daviz Muñoz y Daniel Aguado.
* Release/Creation date: 10/4/2024
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

class Cliente
{
    private:
        int id_cliente;                 //Identificador único del cliente.
        std::string palabra_busqueda;   //Palabra que se desea buscar.

    public:
        Cliente(int _id_cliente, std::string _palabra_busqueda);
        void operator ()() const;
};

class Gratuida: public Cliente
{
    private:
        std::atomic <int> busquedas_restantes;                                              //Busquedas por gastar al usuario gratuido
    public:
        Gratuida(int _id_cliente, std::string _palabra_busqueda, int _busquedas_restantes); //Constructor cliente gratuida
};

class Saldo: public Cliente
{
    private:
       std::atomic <int> creditos;                                            //Creditos que dispone el cliente para gastar
    public: 
        Saldo(int _id_cliente, std::string _palabra_busqueda, int _creditos); //Constructor cliente gratuida
};

class Ilimitada: public Cliente
{
    private:
    public:  
        Ilimitada(int _id_cliente, std::string _palabra_busqueda); //Constructor cliente gratuida
};

#endif