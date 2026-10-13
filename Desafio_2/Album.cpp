#include "Album.h"
#include <iostream>
using namespace std;

Album::Album() {
    nombre = "";
    ruta = "";
    privacidad = "privado";
}

Album::Album(const string& nom, const string& rut, const string& priv) {
    nombre = nom;
    ruta = rut;
    privacidad = priv;
}

Album::Album(const Album& otro) {
    nombre = otro.nombre;
    ruta = otro.ruta;
    privacidad = otro.privacidad;
    fotos = otro.fotos;
}

Album::~Album() {

}

Album& Album::operator=(const Album& otro) {
    if (this != &otro) {
        nombre = otro.nombre;
        ruta = otro.ruta;
        privacidad = otro.privacidad;
        fotos = otro.fotos;
    }
    return *this;
}

// Getters
const string& Album::getNombre() const {
    return nombre;
}

const string& Album::getRuta() const {
    return ruta;
}

const string& Album::getPrivacidad() const {
    return privacidad;
}

int Album::getCantFotos() const {
    return fotos.getCantidad();
}

int Album::getCapacidad() const {
    return fotos.getCapacidad();
}

Foto* Album::getFoto(int indice) {
    if (indice < 0 || indice >= fotos.getCantidad()) {
        return nullptr;
    }
    return &fotos[indice];
}

// Setters
void Album::setNombre(const string& nom) {
    nombre = nom;
}

void Album::setRuta(const string& rut) {
    ruta = rut;
}

void Album::setPrivacidad(const string& priv) {
    privacidad = priv;
}

void Album::agregarFoto(const Foto& foto) {
    fotos.agregar(foto);
}

void Album::mostrarAlbum() const {
    cout << "Album: " << nombre << endl;
    cout << "Ruta: " << ruta << endl;
    cout << "Privacidad: " << privacidad << endl;
    cout << "Fotos: " << fotos.getCantidad()
         << " (capacidad " << fotos.getCapacidad() << ")" << endl;
}

void Album::carrusel() {
    int total = fotos.getCantidad();
    if (total <= 0) {
        cout << "El album esta vacio" << endl;
        return;
    }

    int actual = 0;
    char opcion = ' ';

    while (opcion != 's' && opcion != 'S') {
        cout << endl << "Foto " << actual + 1 << " de " << total << endl;
        fotos[actual].mostrarFoto();

        if (total == 1) {
            cout << "Este album solo tiene una foto, se repetira" << endl;
        }

        cout << "[o] anterior  [p] siguiente  [l] like  [k] quitar like  [s] salir: ";
        if (!(cin >> opcion)) {
            return;
        }

        if (opcion == 'p' || opcion == 'P') {
            actual = (actual + 1) % total;
        } else if (opcion == 'o' || opcion == 'O') {
            actual = (actual - 1 + total) % total;
        } else if (opcion == 'l' || opcion == 'L') {
            fotos[actual].darLike();
            cout << "Like registrado" << endl;
        } else if (opcion == 'k' || opcion == 'K') {
            if (fotos[actual].getLikes() > 0) {
                fotos[actual].quitarLike();
                cout << "Like quitado" << endl;
            } else {
                cout << "La foto no tiene likes para quitar" << endl;
            }
        } else if (opcion != 's' && opcion != 'S') {
            cout << "Opcion invalida" << endl;
        }
    }
}
