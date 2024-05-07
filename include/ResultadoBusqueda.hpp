#include <string>

#ifndef RESULTADOBUSQUEDA_HPP
#define RESULTADOBUSQUEDA_HPP

class ResultadoBusqueda {
    private:
        int linea;
        std::string palabra_anterior;
        std::string palabra;
        std::string palabra_posterior;
        std::string libro;
    public:
        ResultadoBusqueda(int _linea, std::string _palabra_anterior, std::string _palabra_posterior, std::string _libro)
        : linea(_linea), palabra_anterior(_palabra_anterior), palabra_posterior(_palabra_posterior), libro(_libro) {}
        int getLinea() { return linea; }
        std::string getPalabraAnterior() { return palabra_anterior; }
        std::string getPalabraPosterior() { return palabra_posterior; }
        std::string getLibro() { return libro; }
};

#endif // RESULTADOBUSQUEDA_HPP