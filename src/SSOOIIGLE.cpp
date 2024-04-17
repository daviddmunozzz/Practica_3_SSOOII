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
#include "Cliente.h"

#define NUM_CLIENTES 10  // Numero de clientes a crear.
#define NUM_BUSCADORES 5 // Numero de buscadores simultaneos.

/* COLAS GLOBALES */
std::queue<PeticionBusqueda> colaPetBusqueda;
std::condition_variable condicionBusqueda;
std::queue<PeticionPago> colaPetPago;
std::condition_variable condicionPago;

std::string diccionario[] = {
    "hola",
    "adios",
    "casa"
};

void crearClientes()
{
    std::vector<std::thread> vClientes;
    std::srand(std::time(nullptr)); // Semilla para seleccionar la palabra aleatoria

    for (int i = 0; i < NUM_CLIENTES; i++)
    {
        int valor = std::rand() % 3;
        if (valor == 0)
        {
            Cliente cli = Gratuita(i, diccionario[rand() % 26], colaPetBusqueda);

            vClientes.push_back(std::thread(std::ref(cli)));
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        else if (valor == 1)
        {
            Cliente cli = Saldo(i, diccionario[rand() % 26], colaPetBusqueda);

            vClientes.push_back(std::thread(std::ref(cli)));
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        else
        {
            Cliente cli = Ilimitada(i, diccionario[rand() % 26], colaPetBusqueda);

            vClientes.push_back(std::thread(std::ref(cli)));
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }

    std::for_each(vClientes.begin(), vClientes.end(), std::mem_fn(&std::thread::join));
};

void crearSistemaPago()
{
    std::thread hiloPago(sistemaPago, &colaPetPago);
    hiloPago.detach();
};

void crearBuscadores()
{
    std::vector<std::thread> vBuscadores;

    for (int i = 0; i < NUM_BUSCADORES; i++)
    {
        vBuscadores.push_back(std::thread(buscador, i, &colaPetBusqueda));
    }

    std::for_each(vBuscadores.begin(), vBuscadores.end(), std::mem_fn(&std::thread::join));
};