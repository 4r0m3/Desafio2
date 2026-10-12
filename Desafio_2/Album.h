#ifndef ALBUM_H
#define ALBUM_H
#include <string>
#include "Foto.h"
using namespace std;

const int MAX_FOTOS = 50;

class Album {
private:
    string nombre;
    string ruta;
    string privacidad;
    Foto fotos[MAX_FOTOS];
    int cantFotos;

public:
    Album();
    Album(string nom, string rut, string priv, const Foto& primeraFoto);
    Album(const Album& otro);
    ~Album();

    // Getters
    string getNombre();
    string getRuta();
    string getPrivacidad();
    int getCantFotos();

    // Setters
    void setNombre(string nom);
    void setRuta(string rut);
    void setPrivacidad(string priv);

    // Operaciones
    bool agregarFoto(const Foto& foto);
    Foto& getFoto(int indice);
    void mostrarAlbum();
};

#endif
