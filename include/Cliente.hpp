/*********************************************************************
* Class Name: cliente.h
* Author/s name: David Muñoz y Daniel Aguado.
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
#include <iostream>
#include <condition_variable>
#include "PeticionPago.hpp"
#include "PeticionBusqueda.hpp"
#include "ResultadoBusqueda.hpp"

void realizarPeticion(PeticionBusqueda p);

class Cliente
{
    private:
        int id_cliente;                                                   
        std::string palabra_busqueda;                     
        int creditos;
        int tipo_cliente;                                   // 0 == Gratuito, 1 == Saldo, 2 == Ilimitado.
        std::mutex *mtx;                                    //Semaforo para bloquearse tras depositar la peticion
        std::queue<PeticionBusqueda*>* q_peticiones;         //Cola de peticiones donde se dejan las peticiones de busqueda
        std::condition_variable* cv_busqueda;               //Variable de condicion para avisar al cliente de los resultados
        std::queue<ResultadoBusqueda>* q_resultadoBusqueda;  //Cola de soluciones. Se le proporciona al buscador.
    public:
        Cliente(int _id_cliente, std::string _palabra_busqueda, int _creditos, int _tipo_cliente, std::queue<PeticionBusqueda*>* _q_peticiones, std::condition_variable* _cv_busqueda)
        : id_cliente(_id_cliente), palabra_busqueda(_palabra_busqueda), creditos(_creditos), tipo_cliente(_tipo_cliente), q_peticiones(_q_peticiones), cv_busqueda(_cv_busqueda) {}
        
        void operator ()();     
        int getIdCliente() const { return id_cliente; }
        std::string getPalabraBusqueda() const { return palabra_busqueda; }
        virtual int getCreditos() const { return creditos; }
        void setCreditos(int _creditos) { creditos = _creditos; }
        std::mutex* getMtx() const { return mtx; }
        int getTipoCliente() const { return tipo_cliente; }
        std::queue<PeticionBusqueda*>* getQPeticiones() const { return q_peticiones; }
        std::condition_variable* getCvBusqueda() const { return cv_busqueda; }
        std::queue<ResultadoBusqueda>* getQResultadoBusqueda() const { return q_resultadoBusqueda; }
        void setQResultadoBusqueda(std::queue<ResultadoBusqueda>* _q_resultadoBusqueda) { q_resultadoBusqueda = _q_resultadoBusqueda; }
        void toString();
};

#endif
