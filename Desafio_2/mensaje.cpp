#include "mensaje.h"
#include <iostream>
using namespace std;

Mensaje::Mensaje() {
    emisor = "";
    receptor = "";
    contenido = "";
    fecha = "";
    leido = false;
}

Mensaje::Mensaje(string emi, string rec, string cont, string fec) {
    emisor = emi;
    receptor = rec;
    contenido = cont;
    fecha = fec;
    leido = false;
}

Mensaje::Mensaje(const Mensaje& otro) {
    emisor = otro.emisor;
    receptor = otro.receptor;
    contenido = otro.contenido;
    fecha = otro.fecha;
    leido = otro.leido;
}
Mensaje::~Mensaje() {
}

// Getters
string Mensaje::getEmisor() {
    return emisor;
}

string Mensaje::getReceptor() {
    return receptor;
}

string Mensaje::getContenido() {
    return contenido;
}

string Mensaje::getFecha() {
    return fecha;
}

bool Mensaje::getLeido() {
    return leido;
}

// Setters
void Mensaje::setContenido(string cont) {
    contenido = cont;
}

void Mensaje::setFecha(string fec) {
    fecha = fec;
}

void Mensaje::marcarLeido() {
    leido = true;
}

bool Mensaje::esValido() {
    int largo = contenido.length();
    return largo > 0 && largo <= Max_caracter;
}

bool Mensaje::estaEnRango(string inicio, string fin) {
    return fecha >= inicio && fecha <= fin;
}

void Mensaje::mostrarMensaje() {
    cout << "De: " << emisor << endl;
    cout << "Para: " << receptor << endl;
    cout << "Fecha: " << fecha << endl;
    cout << "Estado: " << (leido ? "leido" : "no leido") << endl;
    cout << "Mensaje: " << contenido << endl;
}
