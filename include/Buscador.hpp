#include <queue>
#include "../include/PeticionBusqueda.hpp"
#include <condition_variable>

class Buscador
{
    private:
        int id_buscador;
        std::queue<PeticionBusqueda>* colaPeticiones;
        std::condition_variable* cvBusqueda;

    public:
        Buscador(int _id_buscador, std::queue<PeticionBusqueda>* _colaPeticiones, std::condition_variable* _cvBusqueda)
        : id_buscador(_id_buscador), colaPeticiones(_colaPeticiones), cvBusqueda(_cvBusqueda) {}
};