#include <iostream>
#include <fstream>
#include <cstdlib>
#include "datos.h"
using namespace std;

// Devuelve el texto desde 'pos' hasta la siguiente barra '|' (o hasta el final de la linea)
// y deja 'pos' apuntando al inicio del campo siguiente.
string siguienteCampo(const string& linea, unsigned int& pos) {
    string campo = "";
    while (pos < linea.length() && linea[pos] != '|') {
        campo += linea[pos];
        pos++;
    }
    pos++;   // salta la barra
    return campo;
}

int main() {
    Datos datos;
    string linea;

    // ---------- 1) Usuarios: id|nombre|fechaNac|correo|fotoPerfil|clave|ciudad|pais|fechaInscripcion
    ifstream archivo(datos.getUsuarios());
    if (!archivo.is_open()) {
        cout << "No se pudo abrir " << datos.getUsuarios() << " (corre primero generarArchivos)" << endl;
        return 1;
    }

    int leidos = 0;
    while (leidos < 3 && getline(archivo, linea)) {
        unsigned int pos = 0;                          // posicion actual dentro de la linea

        string id        = siguienteCampo(linea, pos);
        string nombre    = siguienteCampo(linea, pos);
        string fechaNac  = siguienteCampo(linea, pos);
        string correo    = siguienteCampo(linea, pos);
        string foto      = siguienteCampo(linea, pos);
        string clave     = siguienteCampo(linea, pos);
        string ciudad    = siguienteCampo(linea, pos);
        string pais      = siguienteCampo(linea, pos);
        string fechaInsc = siguienteCampo(linea, pos);

        unsigned short idNum = atoi(id.c_str());       // texto -> numero
        unsigned int nac = atoi(fechaNac.c_str());
        unsigned int insc = atoi(fechaInsc.c_str());

        cout << "Usuario " << idNum << ": " << nombre << " | " << ciudad << ", " << pais
             << " | nacio " << nac << " | inscrito " << insc << endl;
        leidos++;
    }
    archivo.close();

    // ---------- 2) Mensajes: idEmisor|idReceptor|fecha|leido|contenido
    ifstream archivoMsg(datos.getMensajes());
    if (archivoMsg.is_open() && getline(archivoMsg, linea)) {
        unsigned int pos = 0;

        string emisor    = siguienteCampo(linea, pos);
        string receptor  = siguienteCampo(linea, pos);
        string fecha     = siguienteCampo(linea, pos);
        string leido     = siguienteCampo(linea, pos);
        string contenido = siguienteCampo(linea, pos);   // ultimo campo: llega hasta el final

        cout << "Mensaje de " << emisor << " a " << receptor << " (" << fecha << "): "
             << contenido << endl;
    }
    return 0;
}