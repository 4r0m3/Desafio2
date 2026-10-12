#include "solicitudamistad.h"
#include <iostream>
using namespace std;

SolicitudAmistad::SolicitudAmistad() {
    emisor = "";
    receptor = "";
    estado = PENDIENTE;
}

SolicitudAmistad::SolicitudAmistad(string emi, string rec){
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

string SolicitudAmistad::getEmisor(){
    return emisor;
}

string SolicitudAmistad::getReceptor(){
    return receptor;
}

int SolicitudAmistad::getEstado(){
    return estado;
}

bool SolicitudAmistad::estaPendiente() {
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

void SolicitudAmistad::mostrarSolicitud() {
    cout << "De: " << emisor << endl;
    cout << "Para: " << receptor << endl;
    cout << "Estado: ";
    if (estado == PENDIENTE) {
        cout << "pendiente" << endl;
    } else if (estado == ACEPTADA) {
        cout << "aceptada" << endl;
    } else {
        cout << "rechazada" << endl;
    }
}
