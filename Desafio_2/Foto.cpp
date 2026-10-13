#include "Foto.h"
#include <iostream>
using namespace std;

Foto::Foto() {
    fechaCaptura = 0;
    tamano = 0;
    ruta = "";
    likes = 0;
}

Foto::Foto(unsigned int fecha, double tam, const string& ubicacion, unsigned int cantidadLikes) {
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

unsigned int Foto::getFechaCaptura() const {
    return fechaCaptura;
}

double Foto::getTamano() const {
    return tamano;
}

const string& Foto::getRuta() const {
    return ruta;
}

unsigned int Foto::getLikes() const {
    return likes;
}

void Foto::setFechaCaptura(unsigned int fecha) {
    fechaCaptura = fecha;
}

void Foto::setTamano(double tam) {
    tamano = tam;
}

void Foto::setRuta(const string& ubicacion) {
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

void Foto::mostrarFoto() const {
    unsigned int anio = fechaCaptura / 10000;
    unsigned int mes = (fechaCaptura / 100) % 100;
    unsigned int dia = fechaCaptura % 100;

    cout << "Fecha de captura: " << anio << "-";
    if (mes < 10) cout << "0";
    cout << mes << "-";
    if (dia < 10) cout << "0";
    cout << dia << endl;
    cout << "Tamano: " << tamano << endl;
    cout << "Ruta: " << ruta << endl;
    cout << "Likes: " << likes << endl;
}