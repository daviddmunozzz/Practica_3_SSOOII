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

class PeticionBusqueda
{
    private:
        int id_cliente;                 //Cliente que realiza la peticion
        std::string palabra_busqueda;   //Palabra a buscar en la peticion
        int creditos;                   //Creditos restantes del cliente
        std::mutex *mtx;

    public:
        PeticionBusqueda(int _id_cliente, const std::string& palabra_busqueda, int _creditos, std::mutex* _mtx) 
        : id_cliente(_id_cliente), palabra_busqueda(palabra_busqueda), creditos(_creditos), mtx(_mtx) {}
        int getIdCliente() const { return id_cliente; }
        std::string getPalabraBusqueda() const { return palabra_busqueda; }
        int getCreditos() const { return creditos; }
        std::mutex* getMtx() const { return mtx; }
};

#endif 