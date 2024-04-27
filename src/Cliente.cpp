#include "../include/Cliente.hpp"
#include "../include/PeticionBusqueda.hpp"
#include <iostream>
#include <typeinfo>
#include <thread>
#include <algorithm>
#include <mutex>
#include <condition_variable>


void Gratuita::operator()()
{
   crearPeticion(getIdCliente(), getPalabraBusqueda(), getCreditos(), getCvBusqueda(), getColaPetBusqueda());
};


void Saldo::operator()()    
{
   crearPeticion(getIdCliente(), getPalabraBusqueda(), getCreditos(), getCvBusqueda(), getColaPetBusqueda());
};


void Ilimitada::operator()()
{
   crearPeticion(getIdCliente(), getPalabraBusqueda(), getCreditos(), getCvBusqueda(), getColaPetBusqueda());
};


std::condition_variable cv;
std::mutex lock;

void crearPeticion(int id_cliente, std::string palabra, int creditos, std::condition_variable* cv, std::queue<PeticionBusqueda>* q)
{   
    std::unique_lock ulock(lock);
    std::mutex mtx;
    PeticionBusqueda p (id_cliente, palabra, creditos, &mtx);
    //Frase
    q->push(p);

    cv->notify_one();
    mtx.lock();
}


/*int main()
{
    std::queue<PeticionBusqueda> colaPetBusqueda;
    std::vector<std::thread> hilos;
    std::string palabra = "hola";
    
    //PeticionBusqueda peticion(&il, i, palabra);

    for (int i = 0; i < 5; i++)
    {
        //Ilimitada il(i, palabra, &colaPetBusqueda);
        hilos.emplace_back(Saldo(i, palabra, &colaPetBusqueda));
    }

    std::for_each(hilos.begin(), hilos.end(), std::mem_fn(&std::thread::join));
    
    return 0;
}*/