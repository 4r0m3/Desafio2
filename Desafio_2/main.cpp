#include "Album.h"
#include "Foto.h"
#include "mensaje.h"
#include "solicitudamistad.h"
#include <iostream>

using namespace std;
int main() {
    Foto f1("2026-03-15", 2048, "/ruta/Malecon2612.png", 0);
    Foto f2("2026-03-16", 1500, "/ruta/Bocagrande1.png", 5);
    Foto f3("2026-03-17", 1800, "/ruta/Castillo.png", 2);

    Album varias("Cartagena2026", "/ruta/Cartagena2026", "amigos", f1);
    varias.agregarFoto(f2);
    varias.agregarFoto(f3);

    Album una("Soledad", "/ruta/Soledad", "privado", f1);
    Album vacio;

    varias.carrusel();
    una.carrusel();
    vacio.carrusel();

    return 0;
}

