/*********************************************************************
*
* Class Name: SSOIIGLE.cpp
* Author/s name: David Muñoz y Daniel Aguado
* Release/Creation date: 6/04/2024
* Class version: 2.0
* Class description: Clase principal del proyecto.
*
**********************************************************************
*/

#include <iostream>
#include <thread>
#include <filesystem>
#include <vector>
#include <iostream>
#include <mutex>
#include <queue>
#include "classBusqueda.h"
#include "Manejador.h"


void crearHilos (int numHilos, std::string libro, std::string palabra);
void buscar (int idHilo, int inicio, int fin, std::string libro, std::string palabra);
void imprimir ();

std::vector<std::queue<Busqueda>> vEncontrados;     //Cola global donde los hilos almacenan sus soluciones.
std::mutex mtx;                                     //Mutex para que no haya mas de un hilo escribiendo en la cola de soluciones.

/*********************************************************************
*
* Method name: MAIN
*
* Name of the original author (if the module author is different
* than the author of the file):
*
* Description of the Method:
*                    - Comprobar que se han introducido el nº correcto de parametros
*                    - Divide el libro en tantas partes como hilos haya.
*                    - Crea los hilos necesarios.
*                    - Manda realizar la busqueda e imprime resultados.
*
* Calling arguments: Path completo al fichero txt, palabra a buscar y nº hilos
*
* Required Files: Fichero txt del que leer las palabras.
*
*********************************************************************/
int main(int argc, char *argv[])
{
    if(argc < 4)                                    //Mostramos un mensaje de error si no se han introducido bien los parametros.
    {
        std::cout << "Error: Faltan argumentos. SSOOIIGLE <nombre_fichero> <palabra> <numero_hilos>" << std::endl;
        exit(EXIT_FAILURE);        
    }   

    std::string libro = argv[1];                    //Guardamos los parametros de entrada de Libro, palabra y numero de hilos.
    std::string palabra = argv[2];  
    int numHilos = atoi(argv[3]);

    vEncontrados.resize(numHilos);                  //Reservamos espacio en el vector para los hilos que hemos indicado por parametro.
    crearHilos(numHilos, libro, palabra);           //Creamos los hilos.

    imprimir();                                     //Mostramos los resultados.

    return 0;
}

/*********************************************************************
*
* Method name: crearHilos
*
* Description of the Method: Crea la cola de hilos y los lanza a ejecucion
*
* Calling arguments: int numhilos   --> Numero de hilos a crear
*                    string libro   --> Libro sobre el que operar
*                    string palabra --> Palabra a buscar
*
* Return value: -
*
*********************************************************************/
void crearHilos (int numHilos, std::string libro, std::string palabra)
{
    std::queue<std::thread> colaHilos;                  //Cola para crear los hilos
    
    int inicio = 0;                                     //Posicion de inicio desde la cual el hilo comenzará.
    int fin = 0;                                        //Posicion final de lectura del hilo
    int numLineas = ContarLineas(libro);                //Calculo del fragmento para cada hilo
    int fragmento = numLineas / numHilos;

    for(int idHilo = 0; idHilo < numHilos; idHilo++)    //Mientras haya hilos por crear
    {
        inicio = idHilo * fragmento;                    //Posicion de inicio del fragmento del hilo actual.
        fin = (inicio + fragmento) - 1;                 //Posicion de fin del fragmento del hilo actual.
        if(idHilo == numHilos - 1) fin = numLineas - 1; //Ajustamos las lineas restantes si es el último hilo.
        colaHilos.push(std::thread(buscar, idHilo, inicio, fin, libro, palabra));    //Asignamos espacio para que el hilo guarde sus soluciones
    }

    while(!colaHilos.empty())       //Mientras haya hilos en funcionamiento
    {
        colaHilos.front().join();   //ESperamos a que todos terminen
        colaHilos.pop();
    }
}

/*********************************************************************
*
* Method name: buscar
*
* Description of the Method: Crea la cola de hilos y los lanza a ejecucion.
*                            Comportamiento del hilo.
*
* Calling arguments: int idhilo   --> Hilo que está trabajando.
*                    int inicio   --> Linea desde la que empieza a operar el hilo.
*                    int fin      --> Linea en la que deja de operar el hilo.
*                    string libro   --> Libro sobre el que operar.
*                    string palabra --> Palabra a buscar.
*
* Return value: -
*
*********************************************************************/
void buscar (int idHilo, int inicio, int fin, std::string libro, std::string palabra)
{
    std::vector<std::string> fragmento = LeerFichero(libro);
    std::queue<Busqueda> colaEncontrados;
    std::string palabra_ant, palabra_post;

    std::lock_guard<std::mutex> lock(mtx);
    for(int linea = inicio; linea <= fin; linea++)
    {
        std::string textoLinea = fragmento[linea];
        std::vector<std::string> lineaSeparada = split(textoLinea, " ");

        for(int i=0; i<lineaSeparada.size(); i++)
        {
            if(toLower(lineaSeparada[i]) == toLower(palabra))
            {
                if(i == 0 && lineaSeparada.size() == 1)
                {
                    palabra_ant = "";
                    palabra_post = "";
                }else if(i == 0)
                {
                    palabra_ant = "";
                    palabra_post = lineaSeparada[i+1];                
                }else if(i == lineaSeparada.size() - 1)
                {
                    palabra_ant = lineaSeparada[i-1];
                    palabra_post = "";  
                }else
                {
                    palabra_ant = lineaSeparada[i-1];
                    palabra_post = lineaSeparada[i+1];  
                }       
                Busqueda b = Busqueda(idHilo, inicio, fin, linea, palabra, palabra_ant, palabra_post);
                colaEncontrados.push(b);          
            }   
        }
    }  
    vEncontrados[idHilo] = colaEncontrados;
}

/*********************************************************************
*
* Method name:imprimir
*
* Name of the original author (if the module author is different
* than the author of the file):
*
* Description of the Method: Imprime toda la cola de soluciones en orden.
*                            Muestra primero todas las del hilo 1 hasta hilo N.
*
* Calling arguments: -
*
* Return value: Muestra por pantalla.
*
*********************************************************************/
void imprimir ()
{
    for(int i=0; i<vEncontrados.size(); i++)
    {
        while(!vEncontrados[i].empty())
        {
            vEncontrados[i].front().toString();
            vEncontrados[i].pop();
        }
    }
}