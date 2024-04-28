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
    crearPeticion(getIdCliente(), getPalabraBusqueda(), creditos, getCvBusqueda(), getColaPetBusqueda(), "[GRATUITA]");
};


void Saldo::operator()()    
{
    crearPeticion(getIdCliente(), getPalabraBusqueda(), creditos, getCvBusqueda(), getColaPetBusqueda(), "[PREMIUM]");    
};


void Ilimitada::operator()()
{  

    crearPeticion(getIdCliente(), getPalabraBusqueda(), creditos, getCvBusqueda(), getColaPetBusqueda(), "[PREMIUM +]");
};


std::mutex lock;

void crearPeticion(int id_cliente, std::string palabra, int creditos, std::condition_variable* cv, std::queue<PeticionBusqueda>* q, std::string tipo)
{   
    std::unique_lock<std::mutex> ulock(lock);
    std::mutex mtx;
    PeticionBusqueda p (id_cliente, palabra, creditos, &mtx);
    mostrarMensaje(id_cliente, palabra, creditos, tipo);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    q->push(p);

    cv->notify_one();
    mtx.lock();   
}


void mostrarMensaje(int id_cliente, std::string palabra, int creditos, std::string tipo)
{   
    if(creditos != -1)
    {
        creditos--;
        std::cout << tipo << " El cliente " << id_cliente << " procede a buscar la palabra " << palabra << ", le quedan " << creditos << " creditos." << std::endl;
    }else
    {
        std::cout << tipo << " El cliente " << id_cliente << " procede a buscar la palabra " << palabra << std::endl;
    }
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