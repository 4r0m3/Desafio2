#ifndef DATOS_H
#define DATOS_H

#include <string>
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
};

#endif // DATOS_H