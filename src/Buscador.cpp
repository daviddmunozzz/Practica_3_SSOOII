#include "../include/Buscador.hpp"
#include "../include/Utilidades.hpp"
#include "../include/ResultadoBusqueda.hpp"
#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <algorithm>

std::queue<Cliente*>* g_colaPeticiones;
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

        Cliente* c = g_colaPeticiones->front();
        g_colaPeticiones->pop();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        // Mensaje
        std::cout << "Buscador de cliente: " << c->getIdCliente() << " ha solicitado buscar la palabra " << c->getPalabraBusqueda() << std::endl;

        iniciarBusqueda(c);
    }
}

void iniciarBusqueda(Cliente* c)
{
    std::vector<std::thread> v_hilos;
    for(int i = 0; i<g_vLibros.size(); i++)
    {
        v_hilos.push_back(std::thread(buscar, c, g_vLibros[i]));
    }

    std::for_each(v_hilos.begin(), v_hilos.end(), std::mem_fn(&std::thread::join));
}

void buscar(Cliente* c, std::string libro)
{
    std::vector<std::string> lectura = LeerFichero(libro);  
    std::string palabra = c->getPalabraBusqueda();
    std::string palabra_anterior, palabra_posterior;
    std::mutex mtx;

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

                if(comprobarCreditos(c))
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    c->getQResultadoBusqueda().push(ResultadoBusqueda(i, palabra_anterior, palabra_posterior, libro));
                }              
            }
        }
    }       
} 

bool comprobarCreditos(Cliente* c)
{
    if(typeid(*c) == typeid(Gratuita))
    {
        if(c->getCreditos() > 0)
        {
            c->setCreditos(c->getCreditos() - 1);
            return true;
        }
        else
        {
            std::cout << "Cliente " << c->getIdCliente() << " con cuenta gratuita, ha completado todas sus búsquedas." << std::endl;
            return false;
        }
    }
    else if(typeid(*c) == typeid(Saldo))
    {
        if(c->getCreditos() > 0)
        {
            c->setCreditos(c->getCreditos() - 1);
            return true;
        }
        else
        {
            std::cout << "Cliente necesita cargar créditos" << std::endl; 
            //Recargar saldo
            return true;
        }
    }
    else
    {
        return true;
    }
}

/*int main()
{
    
    return 0;
}*/