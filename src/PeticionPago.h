#include <string>


class PeticionPago
{
    private:
        int id_cliente;                 //Identificador único del cliente.
        std::string palabra_busqueda;   //Palabra que se desea buscar.

    public:
        PeticionPago(int _id_cliente, std::string _palabra_busqueda);
        void operator ()() const;
        void depositarPeticion() const;
};