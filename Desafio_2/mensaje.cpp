#include "Mensaje.h"
#include <iostream>
using namespace std;

Mensaje::Mensaje() {
    emisor = 0;
    receptor = 0;
    fecha = 0;
    leido = false;
    contenido = "";
}

Mensaje::Mensaje(unsigned short emi, unsigned short rec, const string& cont, unsigned int fec) {
    emisor = emi;
    receptor = rec;
    fecha = fec;
    leido = false;
    contenido = cont;
}

Mensaje::Mensaje(const Mensaje& otro) {
    emisor = otro.emisor;
    receptor = otro.receptor;
    fecha = otro.fecha;
    leido = otro.leido;
    contenido = otro.contenido;
}

Mensaje& Mensaje::operator=(const Mensaje& otro) {
    if (this != &otro) {
        emisor = otro.emisor;
        receptor = otro.receptor;
        fecha = otro.fecha;
        leido = otro.leido;
        contenido = otro.contenido;
    }
    return *this;
}

Mensaje::~Mensaje() {
}

unsigned short Mensaje::getEmisor() const {
    return emisor;
}

unsigned short Mensaje::getReceptor() const {
    return receptor;
}

const string& Mensaje::getContenido() const {
    return contenido;
}

unsigned int Mensaje::getFecha() const {
    return fecha;
}

bool Mensaje::getLeido() const {
    return leido;
}

void Mensaje::setContenido(const string& cont) {
    contenido = cont;
}

void Mensaje::setFecha(unsigned int fec) {
    fecha = fec;
}

void Mensaje::setLeido(bool valor) {
    leido = valor;
}

void Mensaje::marcarLeido() {
    leido = true;
}

bool Mensaje::esValido() const {
    unsigned int largo = contenido.length();
    return largo > 0 && largo <= Max_caracter;
}

bool Mensaje::estaEnRango(unsigned int inicio, unsigned int fin) const {
    return fecha >= inicio && fecha <= fin;
}

bool Mensaje::operator<(const Mensaje& otro) const {
    return fecha < otro.fecha;
}

void Mensaje::mostrarMensaje() const {
    unsigned int anio = fecha / 10000;
    unsigned int mes = (fecha / 100) % 100;
    unsigned int dia = fecha % 100;

    cout << "De (id): " << emisor << endl;
    cout << "Para (id): " << receptor << endl;
    cout << "Fecha: " << anio << "-";
    if (mes < 10) cout << "0";
    cout << mes << "-";
    if (dia < 10) cout << "0";
    cout << dia << endl;
    cout << "Estado: " << (leido ? "leido" : "no leido") << endl;
    cout << "Mensaje: " << contenido << endl;
}
