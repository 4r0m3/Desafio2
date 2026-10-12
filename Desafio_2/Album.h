#ifndef ALBUM_H
#define ALBUM_H
#include <string>
#include "Foto.h"
using namespace std;

const int MAX_FOTOS = 50;   // capacidad fija (sin memoria dinamica por ahora)

class Album {
private:
    string nombre;
    string ruta;
    string privacidad;      // "publico", "privado" o "amigos"
    Foto fotos[MAX_FOTOS];
    int cantFotos;

public:
    // Constructor por defecto (album vacio, util para arreglos de albumes)
    Album();

    // Constructor: un album nace con al menos una foto
    Album(string nom, string rut, string priv, const Foto& primeraFoto);

    // Constructor de copia
    Album(const Album& otro);

    // Destructor
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
    bool agregarFoto(const Foto& foto);   // false si el album esta lleno
    Foto& getFoto(int indice);            // indice entre 0 y cantFotos-1
    void mostrarAlbum();
};

#endif
