/*********************************************************************
* Class Name: classBusqueda.h
* Author/s name: Daviz Muñoz y Daniel Aguado.
* Release/Creation date: 6/4/2024
* Class version: 2.0
* Class description: CABECERA de la clase classBusqueda.cpp. Abstraccion del 
*                    elemento que es solución. Nos permite rear una cola 
*                    de tipo busqueda para almacenar todos os datos
*                    requeridos para mostrar la solucion total.
*
**********************************************************************
*/

#include <string>
#include <vector>

#ifndef BUSQUEDA_H
#define BUSQUEDA_H
class Busqueda
{
    public:
        Busqueda(int id, int ini, int fin, int line, 
                 std::string palabra, std::string p_a, std::string p_p);//Constructor de la clase Busqueda
                                                                        /*int id     --> id del hilo que ha encontrado la palabra
                                                                        int ini    --> Linea inicio por la que empezará el hilo
                                                                        int fin    --> Linea fin por la que acabará el hilo
                                                                        int line   --> Linea en la que se ha encontrado la palabra
                                                                        string pal --> Palabra que queremos buscar
                                                                        string p_a --> Palabra en la posición previa a la que se encuentra nuestra palabra
                                                                        string p_p --> Palabra en la posición siguiente a la que se encuentra nuestra palabra*/
                                                                        
        void operator()() const;                                        //Sobrecarga de operator
        void toString() const;                                          //Salida formateada del texto

    private:
        int idHilo;                 //ID del hilo que esta trabajando
        int inicio;                 //Linea de inicio del espacio de trabajo del hilo actual
        int final;                  //Linea final del espacio de trabajo del hilo actual
        std::string libro;          //Libro sobre el que se está leyendo
        int linea;                  //Linea en la que se ha encontrado la palabra buscada
        std::string palabra;        //Palabra encontrada
        std::string palabra_ant;    //Palabra anterior a la posicion de la palabra a buscar
        std::string palabra_post;   //Palabra posterior a la posicion de la palabra a buscar    
};
#endif