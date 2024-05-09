/*********************************************************************
* Class Name: cliente.cpp
* Author/s name: David Muñoz y Daniel Aguado.
* Release/Creation date: 08/5/2024
* Class version: 1.0
* Class description: Clase abstracta cliente de la que derivan gratuida,
*                    saldo e ilimitada.
*
**********************************************************************
*/

#include "../include/Cliente.hpp"
#include "../include/PeticionBusqueda.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::queue<PeticionBusqueda>* G_q_peticionesBusqueda;
std::condition_variable* G_cv_busqueda;
std::mutex lock;

void Cliente::operator()()
{
    std::mutex* mtx = getMtx();
    mtx->lock();
    std::queue<ResultadoBusqueda>* q_resultadoBusqueda = &getQResultadoBusqueda();
    G_q_peticionesBusqueda = getQPeticiones();
    G_cv_busqueda = getCvBusqueda();
    PeticionBusqueda peticion = PeticionBusqueda(getIdCliente(), getPalabraBusqueda(), getCreditos(),
                                getTipoCliente(), mtx, q_resultadoBusqueda);    
    realizarPeticion(peticion);         //Realizo la peticion y me bloqueo a la espera de resultados
    toString();                         //Almaceno en un fichero la salida.
}

void realizarPeticion(PeticionBusqueda p)
{
    std::lock_guard<std::mutex> lck(lock);
    G_q_peticionesBusqueda->push(p);
    G_cv_busqueda->notify_one();
    p.getMtx()->lock();   
}

void Cliente::toString()
{
    std::queue<ResultadoBusqueda> q = this->getQResultadoBusqueda();
    while(!q.empty())
    {
        ResultadoBusqueda resultado = q.front();
        q.pop();

        std::cout << "[Cliente " << id_cliente << "] :: línea " << resultado.getLinea() <<
        " :: ... " << resultado.getPalabraAnterior() << " " << palabra_busqueda << "" << resultado.getPalabraPosterior() << 
        " ..." << std::endl;

        //Cambiar salida a fichero de texto
    }   
} 