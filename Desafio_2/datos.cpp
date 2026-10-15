#include "Datos.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

Datos::Datos() {
    usuarios    = "Usuarios.txt";
    amistades   = "Amigos.txt";
    solicitudes = "Solicitudes.txt";
    mensajes    = "Mensajes.txt";
    albumes     = "Albums.txt";
    fotos       = "Fotos.txt";
}

string Datos::getUsuarios() const { return usuarios; }
string Datos::getAmistades() const { return amistades; }
string Datos::getSolicitudes() const { return solicitudes; }
string Datos::getMensajes() const { return mensajes; }
string Datos::getAlbumes() const { return albumes; }
string Datos::getFotos() const { return fotos; }

bool Datos::generarArchivos(int n) {
    if (n < 2) return false;
    srand(time(0));

    ofstream fu(usuarios), fa(amistades), fs(solicitudes), fm(mensajes), fal(albumes), ff(fotos);
    if (!fu.is_open() || !fa.is_open() || !fs.is_open() ||
        !fm.is_open() || !fal.is_open() || !ff.is_open()) return false;

    unsigned char* ady = new unsigned char[n * n]();


    // Cada ciudad esta en la misma posicion que su pais (arreglos paralelos).
    const char* ciudades[] = {
        "Medellin", "Bogota", "Cali", "Cartagena", "Barranquilla", "Bucaramanga",
        "Pereira", "Manizales", "Cucuta", "Santa Marta",
        "Lima", "Quito", "Caracas", "Buenos Aires", "Santiago",
        "Ciudad de Mexico", "Sao Paulo", "Montevideo", "Panama", "San Jose",
        "Madrid", "Barcelona", "Miami", "Toronto"
    };
    const char* paises[] = {
        "Colombia", "Colombia", "Colombia", "Colombia", "Colombia", "Colombia",
        "Colombia", "Colombia", "Colombia", "Colombia",
        "Peru", "Ecuador", "Venezuela", "Argentina", "Chile",
        "Mexico", "Brasil", "Uruguay", "Panama", "Costa Rica",
        "Espana", "Espana", "Estados Unidos", "Canada"
    };
    const int totalCiudades = 24;

    // ---- usuarios: id|nombre|fechaNac|correo|fotoPerfil|clave|ciudad|pais|fechaInscripcion
    for (int i = 0; i < n; i++) {
        string nom = "user" + to_string(i);

        // Nacimiento: 1970..2006, mes 1-12, dia 1-28
        int fechaNac = (1970 + rand() % 37) * 10000 + (1 + rand() % 12) * 100 + (1 + rand() % 28);

        // Inscripcion: 2015..2026 (sin pasar de septiembre de 2026)
        int anio = 2015 + rand() % 12;
        int mes = 1 + rand() % 12;
        if (anio == 2026 && mes > 9) mes = 1 + rand() % 9;
        int fechaInsc = anio * 10000 + mes * 100 + (1 + rand() % 28);

        int c = rand() % totalCiudades;

        fu << i << '|' << nom << '|' << fechaNac << '|'
           << nom << "@udea.edu.co|"
           << "/users/udeabook/" << nom << "/albums/profile.png|"
           << "clave" << i << '|' << ciudades[c] << '|' << paises[c] << '|'
           << fechaInsc << '\n';
    }

    for (int i = 0; i < n; i++) {
        for (int d = 1; d <= 20; d++) {
            int j = (i + d) % n;
            if (j != i && rand() % 100 < 70 && ady[i * n + j] == 0) {
                ady[i * n + j] = 1;
                ady[j * n + i] = 1;
                fa << i << '|' << j << '\n';
            }
        }
    }


    for (int i = 0; i < n; i += 2) {
        int j = (i + 100 + rand() % 50) % n;
        if (j != i && ady[i * n + j] == 0) {
            fs << i << '|' << j << "|0\n";
        }
    }


    for (int i = 0; i < n; i++) {
        for (int d = 1; d <= 20; d++) {
            int j = (i + d) % n;
            if (ady[i * n + j] == 1 && rand() % 100 < 20) {
                fm << i << '|' << j << '|'
                   << 20260000 + (1 + rand() % 12) * 100 + (1 + rand() % 28) << '|'
                   << rand() % 2 << "|Hola, como vas?\n";
            }
        }
    }


    const char* nombres[] = {"Viajes", "Familia"};
    const char* privac[]  = {"publico", "amigos"};
    for (int i = 0; i < n; i++) {
        for (int a = 0; a < 2; a++) {
            string ruta = "/users/udeabook/user" + to_string(i) + "/albums/" + nombres[a];
            fal << i << '|' << nombres[a] << '|' << ruta << '|' << privac[a] << '\n';
            for (int f = 1; f <= 5; f++) {
                ff << i << '|' << nombres[a] << '|'
                   << 20200000 + (1 + rand() % 12) * 100 + (1 + rand() % 28) << '|'
                   << 100 + rand() % 400 << '|'
                   << ruta << '/' << nombres[a] << f << ".png|"
                   << rand() % 100 << '\n';
            }
        }
    }

    delete[] ady;
    return true;
}