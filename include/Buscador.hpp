#include <queue>
#include "../include/PeticionBusqueda.hpp"
#include "../include/Utilidades.hpp"
#include "../include/Cliente.hpp"
#include <condition_variable>

#define LIBRERIA "../library"

int contarLibros();
void recibirPeticion();
void iniciarBusqueda(Cliente* p);
void buscar(Cliente* p, std::string libro);
bool comprobarCreditos(Cliente* c);

class Buscador
{
    private:
        int id_buscador;
        std::queue<Cliente*>* colaPeticiones;
        std::condition_variable* cvBusqueda;
        std::vector<std::string> v_libros;

    public:
        Buscador(int _id_buscador, std::queue<Cliente*>* _colaPeticiones, std::condition_variable* _cvBusqueda, std::vector<std::string> _v_libros)
        : id_buscador(_id_buscador), colaPeticiones(_colaPeticiones), cvBusqueda(_cvBusqueda), v_libros(_v_libros) {}
        void operator()();
        int getIdBuscador() const { return id_buscador; }
        std::queue<Cliente*>* getColaPeticiones() const { return colaPeticiones; }
        std::condition_variable* getCvBusqueda() const { return cvBusqueda; }
        std::vector<std::string> getVLibros() const { return v_libros; }
};