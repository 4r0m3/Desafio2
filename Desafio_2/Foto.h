
#ifndef FOTO_H
#define FOTO_H

#include <string>
using namespace std;

class Foto {
private:
    string fechaCaptura;
    double tamano;
    string ruta;
    int likes;

public:
    Foto();
    // Constructor
    Foto(string fecha, double tam, string ubicacion, int cantidadLikes);

    // Constructor de copia
    Foto(const Foto& otra);

    // Destructor
    ~Foto();

    // Getters
    string getFechaCaptura();
    double getTamano();
    string getRuta();
    int getLikes();

    // Setters
    void setFechaCaptura(string fecha);
    void setTamano(double tam);
    void setRuta(string ubicacion);

    // Operaciones
    void darLike();
    void quitarLike();
    void mostrarFoto();
};

#endif
