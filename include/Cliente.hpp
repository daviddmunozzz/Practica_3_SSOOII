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
#include <queue>
#include "PeticionPago.hpp"
#include "PeticionBusqueda.hpp"
#include <iostream>

void crearPeticion();

class Cliente
{
    private:
        int id_cliente;                 
        std::string palabra_busqueda;   
        int creditos;
        std::condition_variable* cv_busqueda;
        std::queue<PeticionBusqueda>* g_colaPetBusqueda; 
        //bool premium;
    public:
        Cliente(int _id_cliente, std::string _palabra_busqueda, std::condition_variable* _cv_busqueda ,std::queue<PeticionBusqueda>* _colaPetBusqueda)
        : id_cliente(_id_cliente), palabra_busqueda(_palabra_busqueda), cv_busqueda(_cv_busqueda), g_colaPetBusqueda(_colaPetBusqueda) {}
        virtual void operator ()() = 0;     
        int getIdCliente() const { return id_cliente; }
        std::string getPalabraBusqueda() const { return palabra_busqueda; }
        int getCreditos() const { return creditos; }
        std::condition_variable* getCvBusqueda() const { return cv_busqueda; }
        std::queue<PeticionBusqueda>* getColaPetBusqueda() const { return g_colaPetBusqueda; }
        //bool esPremium() { return premium; }

};

class Gratuita: public Cliente
{
    private:
        int creditos = 5;              
    public:
        using Cliente::Cliente;
        void operator ()() override; 
        
};


class Saldo: public Cliente
{
    private:
       int creditos = 10;                                       
    public: 
        using Cliente::Cliente;
        void operator ()() override; 
};


class Ilimitada: public Cliente
{
    private:
        int creditos = -1;
    public:  
        using Cliente::Cliente;
        void operator ()() override; 
};


#endif

        /*Gratuita(int _id_cliente, std::string& _palabra_busqueda, std::queue<PeticionBusqueda>* _colaPetBusqueda)
        : Cliente(_id_cliente, _palabra_busqueda, _colaPetBusqueda) {}*/