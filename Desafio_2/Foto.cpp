
#include "Foto.h"
#include <iostream>

using namespace std;

// Constructor
Foto::Foto() {
    fechaCaptura = "";
    tamano = 0;
    ruta = "";
    likes = 0;
}

Foto::Foto(string fecha, double tam, string ubicacion, int cantidadLikes) {
    fechaCaptura = fecha;
    tamano = tam;
    ruta = ubicacion;
    likes = cantidadLikes;
}


Foto::Foto(const Foto& otra) {
    fechaCaptura = otra.fechaCaptura;
    tamano = otra.tamano;
    ruta = otra.ruta;
    likes = otra.likes;
}
Foto& Foto::operator=(const Foto& otra) {
    if (this != &otra) {
        fechaCaptura = otra.fechaCaptura;
        tamano = otra.tamano;
        ruta = otra.ruta;
        likes = otra.likes;
    }

    return *this;
}

Foto::~Foto() {
}

// Getters
string Foto::getFechaCaptura() {
    return fechaCaptura;
}

double Foto::getTamano() {
    return tamano;
}

string Foto::getRuta() {
    return ruta;
}

int Foto::getLikes() {
    return likes;
}

// Setters
void Foto::setFechaCaptura(string fecha) {
    fechaCaptura = fecha;
}

void Foto::setTamano(double tam) {
    tamano = tam;
}

void Foto::setRuta(string ubicacion) {
    ruta = ubicacion;
}

void Foto::darLike() {
    likes++;
}

void Foto::quitarLike() {
    if (likes > 0) {
        likes--;
    }
}

// Mostrar información de la foto
void Foto::mostrarFoto() {
    cout << "Fecha de captura: " << fechaCaptura << endl;
    cout << "Tamano: " << tamano << endl;
    cout << "Ruta: " << ruta << endl;
    cout << "Likes: " << likes << endl;
}
