#include "Album.h"
#include <iostream>
#include "Foto.h"
using namespace std;

// Constructor por defecto
Album::Album(){
    nombre = "";
    ruta = "";
    privacidad = "privado";
    cantFotos = 0;
}

Album::Album(string nom, string rut, string priv, const Foto& primeraFoto) {
    nombre = nom;
    ruta = rut;
    privacidad = priv;
    fotos[0] = primeraFoto;
    cantFotos = 1;
}

Album::Album(const Album& otro) {
    nombre = otro.nombre;
    ruta = otro.ruta;
    privacidad = otro.privacidad;
    cantFotos = otro.cantFotos;
    for (int i = 0; i < cantFotos; i++) {
        fotos[i] = otro.fotos[i];
    }
}

// Destructor
Album::~Album() {
}

// Getters
string Album::getNombre() {
    return nombre;
}

string Album::getRuta() {
    return ruta;
}

string Album::getPrivacidad() {
    return privacidad;
}

int Album::getCantFotos() {
    return cantFotos;
}

// Setters
void Album::setNombre(string nom) {
    nombre = nom;
}

void Album::setRuta(string rut) {
    ruta = rut;
}

void Album::setPrivacidad(string priv) {
    privacidad = priv;
}


bool Album::agregarFoto(const Foto& foto) {
    if (cantFotos >= MAX_FOTOS) {
        return false;
    }
    fotos[cantFotos] = foto;
    cantFotos++;
    return true;
}

Foto& Album::getFoto(int indice) {
    return fotos[indice];
}

// Mostrar informacion del album
void Album::mostrarAlbum() {
    cout << "Album: " << nombre << endl;
    cout << "Ruta: " << ruta << endl;
    cout << "Privacidad: " << privacidad << endl;
    cout << "Fotos: " << cantFotos << endl;
}