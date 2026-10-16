#ifndef DATOS_H
#define DATOS_H

#include <string>
#include "Lista.h"
using namespace std;

class Datos
{
private:
    string usuarios;
    string amistades;
    string solicitudes;
    string mensajes;
    string albumes;
    string fotos;

public:
    Datos();

    string getUsuarios() const;
    string getAmistades() const;
    string getSolicitudes() const;
    string getMensajes() const;
    string getAlbumes() const;
    string getFotos() const;

    bool generarArchivos(int n);
    bool contarAmigos(int n, Lista<int>& cantidades) const;
};

#endif // DATOS_H