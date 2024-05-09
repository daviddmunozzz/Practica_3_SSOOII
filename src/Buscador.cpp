#include "../include/Buscador.hpp"
#include "../include/Utilidades.hpp"
#include "../include/ResultadoBusqueda.hpp"
#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <algorithm>

std::queue<PeticionBusqueda*> *g_colaPeticiones;
std::condition_variable *g_cvBusqueda;
std::vector<std::string> g_vLibros;

void Buscador::operator()()
{
    g_colaPeticiones = getColaPeticiones();
    g_cvBusqueda = getCvBusqueda();
    g_vLibros = getVLibros();

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
        g_colaPeticiones->pop();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        // Mensaje
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
}

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
            if (toLower(lineaSeparada[j]) == toLower(palabra))
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

                // if (comprobarCreditos(p))
                // {
                //     std::cout << "Introduciendo resultado de cliente: " << p.getIdCliente() << std::endl;
                //     p.getQResultadoBusqueda()->push(ResultadoBusqueda(i, palabra_anterior, palabra_posterior, libro));
                   
                // } 

                std::cout << "... " << palabra_anterior << " " << palabra << " " << palabra_posterior << " ..." << std::endl;
            }
        }
    }
}


/* bool comprobarCreditos(PeticionBusqueda p)
{
    int creditos = p.getCreditos();
    std::cout << "Cliente: " << p.getIdCliente() << " con creditos: " << creditos << std::endl;

    if (creditos == -1)
    {
        std::cout << " Cliente premium+ " << std::endl;
        return true;
    }
    else if (creditos == 0)
    {
        std::cout << " No hay mas creditos " << std::endl;
        return false;
    }
    else
    {
        // Cliente gratuito = 1
        if (p.tipoCliente() == 1)
        {
            std::cout << " Cliente gratuito" << std::endl;
            
            c->setCreditos(creditos - 1);
            return true;
        }
        // Cliente saldo = 2
        else if (p.tipoCliente() == 2)
        {
            std::cout << " Cliente saldo" << std::endl;
            c->setCreditos(c->getCreditos() - 1);
            return true;
        }
    }
} */
/*int main()
{

    return 0;
}*/