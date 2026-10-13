#ifndef FOTO_H
#define FOTO_H

#include <string>
using namespace std;

class Foto {
private:
    unsigned int fechaCaptura;
    double tamano;
    string ruta;
    unsigned int likes;

public:
    Foto();
    Foto(unsigned int fecha, double tam, const string& ubicacion, unsigned int cantidadLikes);
    Foto(const Foto& otra);
    Foto& operator=(const Foto& otra);
    ~Foto();

    unsigned int getFechaCaptura() const;
    double getTamano() const;
    const string& getRuta() const;
    unsigned int getLikes() const;

    void setFechaCaptura(unsigned int fecha);
    void setTamano(double tam);
    void setRuta(const string& ubicacion);

    void darLike();
    void quitarLike();
    void mostrarFoto() const;
};

#endif