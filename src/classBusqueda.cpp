/*********************************************************************
* Class Name: classBusqueda.cpp
* Author/s name: Daviz Muñoz y Daniel Aguado.
* Release/Creation date: 6/4/2024
* Class version: 2.0
* Class description: Abstraccion del elemento que es solución. Nos permite
*                    crear una cola de tipo busqueda para almacenar todos
*                    los datos requeridos para mostrar la solucion total
*
**********************************************************************
*/

#include "classBusqueda.h"
#include "Manejador.h"

/*********************************************************************
*
* Method name: Busqueda
*
* Description of the Method: CONSTRUCTOR de la clase busqueda. 
*
* Calling arguments: int id     --> id del hilo que ha encontrado la palabra
*                    int ini    --> Linea inicio por la que empezará el hilo
*                    int fin    --> Linea fin por la que acabará el hilo
*                    int line   --> Linea en la que se ha encontrado la palabra
*                    string pal --> Palabra que queremos buscar
*                    string p_a --> Palabra en la posición previa a la que se encuentra nuestra palabra
*                    string p_p --> Palabra en la posición siguiente a la que se encuentra nuestra palabra
*
*
* Return value: Crea un objeto de tipo Busqueda cuyos atributos son
*               los mismos que los argumentos de entrada.
*
*********************************************************************/
Busqueda::Busqueda(int id, int ini, int fin, int line, std::string pal, std::string p_a, std::string p_p)
            : idHilo(id), inicio(ini), final(fin), linea(line), palabra(pal), palabra_ant(p_a), palabra_post(p_p){};    //Creacion de objetos Busqueda

/*********************************************************************
* Method name: toString
*
* Description of the Method: Salida formateada de las soluciones 
*                            almacenadas.
*
* Return value: Salida por pantalla.
*
*********************************************************************/
void Busqueda::toString() const
{
    std::cout << "[Hilo " << idHilo+1 << " inicio:" << inicio+1 << " - "    //Mostrar por pantalla
    << "final: " << final+1 << "]"
    << " :: "
    << "línea " << linea+1 << " :: "
    << "... " << palabra_ant << " " << palabra << " "
    << palabra_post << " ..." << std::endl;
} 
