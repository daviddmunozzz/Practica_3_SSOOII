#include <string>
#include "PeticionBusqueda.hpp"

class PeticionPago
{
    private:
        PeticionBusqueda* peticion;
        std::atomic<int>* creditos;

    public:
        PeticionPago(PeticionBusqueda* _peticion, std::atomic<int>* _creditos): peticion(_peticion), creditos(_creditos) {}
        int getIdCliente() { return peticion->getIdCliente(); }
        void recargaCreditos() { creditos->store(10); }
};