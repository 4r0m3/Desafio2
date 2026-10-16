#include "Datos.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
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

    // Lista variada de nombres para los usuarios
    const char* nombresUsuarios[] = {
        "Andres", "Sofia", "Carlos", "Valentina", "Mateo", "Camila",
        "Alejandro", "Lucia", "Juan", "Mariana", "Daniel", "Valeria",
        "Santiago", "Isabella", "Sebastian", "Gabriela", "David", "Martina",
        "Nicolas", "Catalina", "Felipe", "Sara", "Manuel", "Elena",
        "Esteban", "Paula", "Julian", "Jimena", "Tomas", "Daniela"
    };
    const int totalNombresUsuarios = 30;

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

    // ---- Usuarios con nombres variados
    for (int i = 0; i < n; i++) {
        string nom = nombresUsuarios[i % totalNombresUsuarios];
        if (i >= totalNombresUsuarios) {
            nom += to_string(i); // Evita duplicados si n > 30
        }

        int fechaNac = (1970 + rand() % 37) * 10000 + (1 + rand() % 12) * 100 + (1 + rand() % 28);

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

    // ---- Amistades aleatorias
    for (int i = 0; i < n; i++) {
        int conexiones = 1 + rand() % (n > 10 ? 10 : (n > 1 ? n - 1 : 1));
        for (int k = 0; k < conexiones; k++) {
            int j = rand() % n;
            if (j != i && ady[i * n + j] == 0) {
                ady[i * n + j] = 1;
                ady[j * n + i] = 1;
                fa << i << '|' << j << '\n';
            }
        }
    }

    // ---- Solicitudes de amistad pendientes (estado 0)
    for (int i = 0; i < n; i++) {
        int enviadas = 0;
        int intentos = 0;
        while (enviadas < 3 && intentos < 20) {
            int j = rand() % n;
            if (j != i && ady[i * n + j] == 0) {
                fs << i << '|' << j << "|0\n";
                enviadas++;
            }
            intentos++;
        }
    }

    // ---- Mensajes variados y garantizados entre amigos
    const char* mensajesPosibles[] = {
        "Hola, como vas?",
        "Feliz cumpleanos! Que la pases excelente hoy.",
        "Nos vemos este fin de semana para jugar un partido?",
        "Oye, muy buenas las fotos que subiste al album.",
        "Hola! Que tal va todo por alla?",
        "Mucho exito con tus proyectos y clases de esta semana.",
        "Me avisas cuando te conectes para charlar un rato.",
        "Gracias por la ayuda con la tarea el otro dia!"
    };
    const int totalMensajes = 8;

    for (int i = 0; i < n; i++) {
        int mensajesGenerados = 0;
        for (int d = 1; d < n && mensajesGenerados < 3; d++) {
            int j = (i + d) % n;
            // Si son amigos, les creamos mensajes obligatoriamente para que aparezcan al iniciar sesión
            if (ady[i * n + j] == 1) {
                string textoElegido = mensajesPosibles[rand() % totalMensajes];
                // Formato: emisor | receptor | fecha | leido (0 = no leído) | texto
                fm << i << '|' << j << '|'
                   << 20260000 + (1 + rand() % 12) * 100 + (1 + rand() % 28) << '|'
                   << 0 << '|' << textoElegido << '\n';
                mensajesGenerados++;
            }
        }
    }
    // ---- Álbumes y Fotos
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
bool Datos::contarAmigos(int n, Lista<int>& cantidades) const {
    ifstream archivo(amistades);
    if (!archivo.is_open()) {
        return false;
    }

    cantidades = Lista<int>();
    for (int i = 0; i < n; i++) {
        cantidades.agregar(0);
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t barra = linea.find('|');
        if (barra == string::npos) {
            continue;
        }
        int a = std::stoi(linea.substr(0, barra));
        int b = std::stoi(linea.substr(barra + 1));

        if (a < 0 || a >= n || b < 0 || b >= n || a == b) {
            continue;
        }
        cantidades[a]++;
        cantidades[b]++;
    }
    archivo.close();
    return true;
}