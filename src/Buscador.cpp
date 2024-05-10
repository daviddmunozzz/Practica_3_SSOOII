#include "../include/Buscador.hpp"
#include "../include/Utilidades.hpp"
#include "../include/ResultadoBusqueda.hpp"
#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <atomic>
#include <algorithm>

std::queue<PeticionBusqueda*> *g_colaPeticiones;
std::condition_variable *g_cvBusqueda;

std::queue<PeticionPago> *g_colaPeticionPago;
std::condition_variable *g_cvPago;

std::vector<std::string> g_vLibros;

std::atomic<int> va_creditos;


void Buscador::operator()()
{
    g_colaPeticiones = getColaPeticiones();
    g_cvBusqueda = getCvBusqueda();

    g_vLibros = getVLibros();

    g_colaPeticionPago = getQpeticionPago();
    g_cvPago = getCvPago();

    recibirPeticion();
}

std::mutex lck;
void recibirPeticion()
{
    while (true)
    {
        std::unique_lock<std::mutex> ulck(lck);
        std::cout << "Buscador esperando peticion..." << std::endl;
        g_cvBusqueda->wait(ulck, [] { return !g_colaPeticiones->empty(); });
        PeticionBusqueda* p = g_colaPeticiones->front();
        va_creditos.store(p->getCreditos());
        g_colaPeticiones->pop();
        std::cout << "Buscador de cliente: " << p->getIdCliente() << " ha solicitado buscar la palabra " << p->getPalabraBusqueda() << std::endl;

        iniciarBusqueda(*p);  // Dereferenciamos el puntero para pasarle el objeto a iniciarBusqueda()
    }
}

void iniciarBusqueda(PeticionBusqueda p)
{
    std::vector<std::thread> v_hilos;
    for (int i = 0; i < g_vLibros.size(); i++)
    {
        v_hilos.push_back(std::thread(buscar, p, g_vLibros[i]));
    }

    std::for_each(v_hilos.begin(), v_hilos.end(), std::mem_fn(&std::thread::join));

    std::cout << "Busqueda finalizada para el cliente: " << p.getIdCliente() << std::endl;
    p.getMtx()->unlock();
}

std::mutex mut;
void buscar(PeticionBusqueda p, std::string libro)
{
    std::vector<std::string> lectura = LeerFichero(libro);
    std::string palabra = p.getPalabraBusqueda();
    std::string palabra_anterior, palabra_posterior;

    for (int i = 0; i < lectura.size(); i++)
    {
        std::string linea = lectura[i];
        std::vector<std::string> lineaSeparada = split(linea, " ");

        for (int j = 0; j < lineaSeparada.size(); j++)
        {
            // Solo va a aplicar cuando tipo cliente == 1 (Saldo)
            std::unique_lock<std::mutex> unique(mut);
            g_cvPago->wait(unique, [] { return g_colaPeticionPago->empty(); });

            if ((toLower(lineaSeparada[j]) == toLower(palabra)) && comprobarCreditos(p))
            {
                if (j == 0 && lineaSeparada.size() == 1)
                {
                    palabra_anterior = "";
                    palabra_posterior = "";
                }
                else if (j == 0)
                {
                    palabra_anterior = "";
                    palabra_posterior = lineaSeparada[j + 1];
                }
                else if (j == lineaSeparada.size() - 1)
                {
                    palabra_anterior = lineaSeparada[j - 1];
                    palabra_posterior = "";
                }
                else
                {
                    palabra_anterior = lineaSeparada[j - 1];
                    palabra_posterior = lineaSeparada[j + 1];
                }

                //std::lock_guard<std::mutex> lck(mut);
                ResultadoBusqueda resultado = ResultadoBusqueda(i, palabra_anterior, palabra_posterior, libro);
                p.getQResultadoBusqueda()->push(resultado);   

            }
        }
    }
}


bool comprobarCreditos(PeticionBusqueda p)
{
    // std::mutex m;
    // std::lock_guard<std::mutex> lck(m);

   // int creditos = p.getCreditos();

    switch (p.getTipoCliente())
    {
    case 0:
        if(va_creditos.load() == 0)
        {
            std::cout << "No hay creditos disponibles para el cliente: " << p.getIdCliente() << std::endl;       
            return false;
        }
        else{
            va_creditos.fetch_sub(1);
            return true;
        }
        break;
    case 1:
        if(va_creditos.load() == 0)
        {
            PeticionPago peticionPago = PeticionPago(&p, &va_creditos);
            std::cout << "No hay creditos disponibles para el cliente: " << p.getIdCliente() << " procede a pagar..." << std::endl;
            g_colaPeticionPago->push(peticionPago);
            g_cvPago->notify_one();
            return false;
        }
        else{
            va_creditos.fetch_sub(1);
            return true;
        }
        break;
    default:
        return true;
        break;
    }
} 
