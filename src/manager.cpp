/*********************************************************************
 *
 * Class Name: SSOIIGLE.cpp
 * Author/s name: David Muñoz y Daniel Aguado
 * Release/Creation date: 17/04/2024
 * Class version: 1.0
 * Class description: Clase Manager del proyecto. Funciones:
 *                    - Crea buffers de peticiones y de pagos.
 *                    - Crea los buscadores limitados.
 *                    - Crea el sistema de pago.
 *                    - Crea clientes cada X segundos.
 **********************************************************************
 */

#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "../include/Cliente.hpp"
#include "../include/PeticionBusqueda.hpp"
#include "../include/Buscador.hpp"


#define NUM_CLIENTES 10  // Numero de clientes a crear.
#define NUM_BUSCADORES 5 // Numero de buscadores simultaneos.

/* COLAS GLOBALES */
std::queue<Cliente*> colaPeticionesBusqueda;
std::queue<PeticionPago> colaPetPago;

/* VARIABLES DE CONDICIÓN */
std::condition_variable cv_Busqueda;
std::condition_variable cv_Pago;

/* LIBRERIA */
std::vector<std::string> libreria;

/* DICCIONARIO DE PALABRAS */
std::string diccionario[] = {
    "hola","adios", "gato",
    "casa", "coche", "perro",    
    "mesa", "silla", "libro",
    "telefono", "ordenador", "pelicula",
    "juego", "musica", "playa",
    "montaña", "ciudad", "parque",
    "comida", "bebida"
};

void crearClientes()
{
    std::srand(std::time(nullptr)); // Semilla para seleccionar la palabra aleatoria

    for (int i = 1; i <= NUM_CLIENTES; i++)
    {
        int valor = std::rand() % 3;
        std::mutex mtx;
        if (valor == 0)
        {
            colaPeticionesBusqueda.push(new Gratuita(i, diccionario[rand() % 20], &mtx));
            std::cout << "Cliente con opcion gratuita, procede a buscar una palabra..." << std::endl;   
            cv_Busqueda.notify_one();
            mtx.lock();
            std::this_thread::sleep_for(std::chrono::seconds(1));

        }
        else if (valor == 1)
        {
            colaPeticionesBusqueda.push(new Saldo(i, diccionario[rand() % 20], &mtx));
            std::cout << "Cliente con opcion de saldo, procede a buscar una palabra..." << std::endl;   
            cv_Busqueda.notify_one();
            mtx.lock();
            std::this_thread::sleep_for(std::chrono::seconds(1));

        }
        else
        {
            colaPeticionesBusqueda.push(new Ilimitada(i, diccionario[rand() % 20], &mtx));
            std::cout << "Cliente con opcion ilimitada, procede a buscar una palabra..." << std::endl;   
            cv_Busqueda.notify_one();
            mtx.lock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}




/* void crearSistemaPago()
{
    std::thread hiloPago(sistemaPago, &colaPetPago);
    hiloPago.detach();
};*/

void crearBuscadores()
{
    std::vector<std::thread> vBuscadores;

    for (int i = 0; i < NUM_BUSCADORES; i++)
    {
        vBuscadores.emplace_back(Buscador(i, &colaPeticionesBusqueda, &cv_Busqueda, libreria));
    }

    std::for_each(vBuscadores.begin(), vBuscadores.end(), std::mem_fn(&std::thread::join));
} 

int main()
{
    cargarNombreLibros(&libreria);
    std::thread hiloClientes(crearClientes);
    std::thread hiloBuscadores(crearBuscadores);

    hiloClientes.join();
    hiloBuscadores.join();
    
    return 0;
}