#include "solicitudamistad.h"
#include <iostream>
using namespace std;

SolicitudAmistad::SolicitudAmistad() {
    emisor = 0;
    receptor = 0;
    estado = PENDIENTE;
}

SolicitudAmistad::SolicitudAmistad(unsigned short emi, unsigned short rec) {
    emisor = emi;
    receptor = rec;
    estado = PENDIENTE;
}

SolicitudAmistad::SolicitudAmistad(const SolicitudAmistad& otra) {
    emisor = otra.emisor;
    receptor = otra.receptor;
    estado = otra.estado;
}

SolicitudAmistad::~SolicitudAmistad() {
}

SolicitudAmistad& SolicitudAmistad::operator=(const SolicitudAmistad& otra) {
    if (this != &otra) {
        emisor = otra.emisor;
        receptor = otra.receptor;
        estado = otra.estado;
    }
    return *this;
}

// Dos solicitudes son iguales si tienen el mismo emisor y receptor.
// Sirve para detectar solicitudes duplicadas.
bool SolicitudAmistad::operator==(const SolicitudAmistad& otra) const {
    return emisor == otra.emisor && receptor == otra.receptor;
}

unsigned short SolicitudAmistad::getEmisor() const {
    return emisor;
}

unsigned short SolicitudAmistad::getReceptor() const {
    return receptor;
}

int SolicitudAmistad::getEstado() const {
    return estado;
}

bool SolicitudAmistad::estaPendiente() const {
    return estado == PENDIENTE;
}

bool SolicitudAmistad::aceptar() {
    if (estado != PENDIENTE) {
        return false;
    }
    estado = ACEPTADA;
    return true;
}

bool SolicitudAmistad::rechazar() {
    if (estado != PENDIENTE) {
        return false;
    }
    estado = RECHAZADA;
    return true;
}

void SolicitudAmistad::mostrarSolicitud() const {
    cout << "De (id): " << emisor << endl;
    cout << "Para (id): " << receptor << endl;
    cout << "Estado: ";
    if (estado == PENDIENTE) {
        cout << "pendiente" << endl;
    } else if (estado == ACEPTADA) {
        cout << "aceptada" << endl;
    } else {
        cout << "rechazada" << endl;
    }
}