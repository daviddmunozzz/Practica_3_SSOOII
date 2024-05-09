#include <queue>
#include "../include/PeticionBusqueda.hpp"
#include "../include/Utilidades.hpp"
#include "../include/Cliente.hpp"
#include <condition_variable>

#define LIBRERIA "../library/"

int contarLibros();
void recibirPeticion();
void iniciarBusqueda(PeticionBusqueda p);
void buscar(PeticionBusqueda p, std::string libro);
bool comprobarCreditos(PeticionBusqueda p);

class Buscador
{
    private:
        int id_buscador;
        std::queue<PeticionBusqueda>* colaPeticiones;
        std::condition_variable* cvBusqueda;
        std::vector<std::string> v_libros;

    public:
        Buscador(int _id_buscador, std::queue<PeticionBusqueda>* _colaPeticiones, std::condition_variable* _cvBusqueda, std::vector<std::string> _v_libros)
        : id_buscador(_id_buscador), colaPeticiones(_colaPeticiones), cvBusqueda(_cvBusqueda), v_libros(_v_libros) {}
        void operator()();
        int getIdBuscador() const { return id_buscador; }
        std::queue<PeticionBusqueda>* getColaPeticiones() const { return colaPeticiones; }
        std::condition_variable* getCvBusqueda() const { return cvBusqueda; }
        std::vector<std::string> getVLibros() const { return v_libros; }
};