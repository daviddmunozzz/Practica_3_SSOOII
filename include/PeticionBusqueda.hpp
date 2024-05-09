/*********************************************************************
* Class Name: PeticionBusqueda.hpp
* Author/s name: David Muñoz y Daniel Aguado.
* Release/Creation date: 25/4/2024
* Class version: 1.0
* Class description: 
*
**********************************************************************
*/

#ifndef PETICION_BUSQUEDA_H
#define PETICION_BUSQUEDA_H

#include <string>
#include <atomic>
#include <queue>
#include <string>
#include <mutex>
#include "ResultadoBusqueda.hpp"


class PeticionBusqueda
{
    private:
        int id_cliente;                 //Cliente que realiza la peticion
        std::string palabra_busqueda;   //Palabra a buscar en la peticion
        int creditos;                   //Creditos restantes del cliente
        int tipo_cliente;               // 0 == Gratuito, 1 == Saldo, 2 == Ilimitado.
        std::mutex *mtx;                //Semaforo asociado al cliente
        std::queue<ResultadoBusqueda>* q_resultadoBusqueda;  

    public:
        PeticionBusqueda(int _id_cliente, std::string palabra_busqueda, int _creditos, int _tipo_cliente, std::mutex* _mtx, std::queue<ResultadoBusqueda>* _q_resultadoBusqueda) 
        : id_cliente(_id_cliente), palabra_busqueda(palabra_busqueda), creditos(_creditos), tipo_cliente(_tipo_cliente), mtx(_mtx), q_resultadoBusqueda(_q_resultadoBusqueda) {}
        int getIdCliente() const { return id_cliente; }
        std::string getPalabraBusqueda() const { return palabra_busqueda; }
        int getCreditos() const { return creditos; }
        void restarCreditos() { creditos--; }
        std::mutex* getMtx() const { return mtx; }
        std::queue<ResultadoBusqueda>* getQResultadoBusqueda() const { return q_resultadoBusqueda; }
};

#endif 