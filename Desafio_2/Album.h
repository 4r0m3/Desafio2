#ifndef ALBUM_H
#define ALBUM_H
#include <string>
#include "Foto.h"
using namespace std;

class Album {
private:
    string nombre;
    string ruta;
    string privacidad;      // "publico", "privado" o "amigos"
    Foto* fotos;            // arreglo dinamico de fotos
    int cantFotos;          // fotos realmente guardadas
    int capacidad;          // fotos que caben en el bloque actual

    void crecer();          // duplica la capacidad cuando el arreglo se llena

public:
    // Constructor por defecto (album vacio)
    Album();

    // Constructor: un album nace con al menos una foto
    Album(string nom, string rut, string priv, const Foto& primeraFoto);

    // Constructor de copia (copia profunda)
    Album(const Album& otro);

    // Destructor (libera el arreglo dinamico)
    ~Album();

    // Operador de asignacion (copia profunda)
    Album& operator=(const Album& otro);

    // Getters
    string getNombre();
    string getRuta();
    string getPrivacidad();
    int getCantFotos();
    int getCapacidad();

    // Setters
    void setNombre(string nom);
    void setRuta(string rut);
    void setPrivacidad(string priv);

    // Operaciones
    void agregarFoto(const Foto& foto);
    Foto& getFoto(int indice);            // indice entre 0 y cantFotos-1
    void mostrarAlbum();
    void carrusel();
};

#endif
