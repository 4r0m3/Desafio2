#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "Foto.h"
#include "Lista.h"
using namespace std;

class Album {
private:
    string nombre;
    string ruta;
    string privacidad;
    Lista<Foto> fotos;

public:
    Album();
    Album(const string& nom, const string& rut, const string& priv);
    Album(const Album& otro);
    ~Album();
    Album& operator=(const Album& otro);

    // Getters
    const string& getNombre() const;
    const string& getRuta() const;
    const string& getPrivacidad() const;
    int getCantFotos() const;
    int getCapacidad() const;
    Foto* getFoto(int indice);
    // Setters
    void setNombre(const string& nom);
    void setRuta(const string& rut);
    void setPrivacidad(const string& priv);

    void agregarFoto(const Foto& foto);
    void mostrarAlbum() const;
    void carrusel();
};

#endif
