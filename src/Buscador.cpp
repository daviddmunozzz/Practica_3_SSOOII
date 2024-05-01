#include "../include/Buscador.hpp"
#include "../include/Utilidades.hpp"
#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <algorithm>

std::queue<PeticionBusqueda>* g_colaPeticiones;
std::condition_variable* g_cvBusqueda;
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

        PeticionBusqueda p = g_colaPeticiones->front();
        g_colaPeticiones->pop();
        // Mensaje
        std::cout << "Buscador de cliente: " << p.getIdCliente() << " ha solicitado buscar la palabra " << p.getPalabraBusqueda() << std::endl;

        iniciarBusqueda(p);
    }
}

void iniciarBusqueda(PeticionBusqueda p)
{
    std::vector<std::thread> v_hilos;
    for(int i = 0; i<g_vLibros.size(); i++)
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

    for(int i = 0; i<lectura.size(); i++)
    {
        std::string linea = lectura[i]; 
        std::vector<std::string> lineaSeparada = split(linea, " ");

        for(int j = 0; j<lineaSeparada.size(); j++)
        {
            if(toLower(lineaSeparada[j]) == toLower(palabra))
            {
                if(j == 0 &&  lineaSeparada.size() > 1)
                {
                    palabra_anterior= "";
                    palabra_posterior = "";
                }else if(j == 0)
                {
                    palabra_anterior = "";
                    palabra_posterior = lineaSeparada[i+1];
                }else if(j == lineaSeparada.size() - 1)
                {
                    palabra_anterior = lineaSeparada[i-1];
                    palabra_posterior = "";
                }else{
                    palabra_anterior = lineaSeparada[i-1];
                    palabra_posterior = lineaSeparada[i+1];
                }
            }
        }
    }       
}



/*int main()
{
    
    return 0;
}*/