#include "Album.h"
#include <iostream>

using namespace std;

const int CAPACIDAD_INICIAL = 4;

Album::Album() {
    nombre = "";
    ruta = "";
    privacidad = "privado";
    capacidad = CAPACIDAD_INICIAL;
    cantFotos = 0;
    fotos = new Foto[capacidad];
}

Album::Album(string nom, string rut, string priv, const Foto& primeraFoto) {
    nombre = nom;
    ruta = rut;
    privacidad = priv;
    capacidad = CAPACIDAD_INICIAL;
    fotos = new Foto[capacidad];
    fotos[0] = primeraFoto;
    cantFotos = 1;
}

Album::Album(const Album& otro) {
    nombre = otro.nombre;
    ruta = otro.ruta;
    privacidad = otro.privacidad;
    cantFotos = otro.cantFotos;
    capacidad = otro.capacidad;
    fotos = new Foto[capacidad];
    for (int i = 0; i < cantFotos; i++) {
        fotos[i] = otro.fotos[i];
    }
}

Album::~Album() {
    delete[] fotos;
}

Album& Album::operator=(const Album& otro) {
    if (this != &otro) {            // evita problemas con a = a
        delete[] fotos;             // libera el bloque anterior
        nombre = otro.nombre;
        ruta = otro.ruta;
        privacidad = otro.privacidad;
        cantFotos = otro.cantFotos;
        capacidad = otro.capacidad;
        fotos = new Foto[capacidad];
        for (int i = 0; i < cantFotos; i++) {
            fotos[i] = otro.fotos[i];
        }
    }
    return *this;
}

void Album::crecer() {
    capacidad = capacidad * 2;
    Foto* nuevo = new Foto[capacidad];
    for (int i = 0; i < cantFotos; i++) {
        nuevo[i] = fotos[i];
    }
    delete[] fotos;
    fotos = nuevo;
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

int Album::getCapacidad() {
    return capacidad;
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

void Album::agregarFoto(const Foto& foto) {
    if (cantFotos < 0) {
        return;
    }
    if (cantFotos >= capacidad) {
        crecer();
    }
    fotos[cantFotos] = foto;
    cantFotos++;
}

Foto& Album::getFoto(int indice) {
    if (indice < 0 || indice >= cantFotos) {
        return fotos[0];
    }
    return fotos[indice];
}

// Mostrar informacion del album
void Album::mostrarAlbum() {
    cout << "Album: " << nombre << endl;
    cout << "Ruta: " << ruta << endl;
    cout << "Privacidad: " << privacidad << endl;
    cout << "Fotos: " << cantFotos << " (capacidad " << capacidad << ")" << endl;
}


void Album::carrusel() {
    if (cantFotos <= 0) {
        cout << "El album esta vacio" << endl;
        return;
    }

    int actual = 0;
    char opcion = ' ';

    while (opcion != 's' && opcion != 'S') {
        cout << endl << "Foto " << actual + 1 << " de " << cantFotos << endl;
        fotos[actual].mostrarFoto();

        if (cantFotos == 1) {
            cout << "Este album solo tiene una foto, se repetira" << endl;
        }

        cout << "[o] anterior  [p] siguiente  [l] like  [k] quitar like  [s] salir: ";
        if (!(cin >> opcion)) {
            return;
        }

        if (opcion == 'p' || opcion == 'P') {
            actual = (actual + 1) % cantFotos;
        } else if (opcion == 'o' || opcion == 'O') {
            actual = (actual - 1 + cantFotos) % cantFotos;
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
