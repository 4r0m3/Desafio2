#include "Usuario.h"
#include <iostream>
using namespace std;

Usuario::Usuario() {
    id = 0;
    nombre = "";
    fechaNac = 0;
    correo = "";
    fotoPerfil = "";
    clave = "";
    ciudad = "";
    pais = "";
    fechaInscripcion = 0;
}

Usuario::Usuario(unsigned short i, const string& nom, unsigned int fnac, const string& cor,
                 const string& foto, const string& cla, const string& ciu,
                 const string& pai, unsigned int finsc) {
    id = i;
    nombre = nom;
    fechaNac = fnac;
    correo = cor;
    fotoPerfil = foto;
    clave = cla;
    ciudad = ciu;
    pais = pai;
    fechaInscripcion = finsc;
}

Usuario::Usuario(const Usuario& otro) {
    id = otro.id;
    nombre = otro.nombre;
    fechaNac = otro.fechaNac;
    correo = otro.correo;
    fotoPerfil = otro.fotoPerfil;
    clave = otro.clave;
    ciudad = otro.ciudad;
    pais = otro.pais;
    fechaInscripcion = otro.fechaInscripcion;
}

Usuario::~Usuario() {
}

Usuario& Usuario::operator=(const Usuario& otro) {
    if (this != &otro) {
        id = otro.id;
        nombre = otro.nombre;
        fechaNac = otro.fechaNac;
        correo = otro.correo;
        fotoPerfil = otro.fotoPerfil;
        clave = otro.clave;
        ciudad = otro.ciudad;
        pais = otro.pais;
        fechaInscripcion = otro.fechaInscripcion;
    }
    return *this;
}

unsigned short Usuario::getId() const { return id; }
string Usuario::getNombre() const { return nombre; }
unsigned int Usuario::getFechaNac() const { return fechaNac; }
string Usuario::getCorreo() const { return correo; }
string Usuario::getFotoPerfil() const { return fotoPerfil; }
string Usuario::getClave() const { return clave; }
string Usuario::getCiudad() const { return ciudad; }
string Usuario::getPais() const { return pais; }
unsigned int Usuario::getFechaInscripcion() const { return fechaInscripcion; }

string Usuario::siguienteCampo(const string& linea, unsigned int& pos) {
    string campo = "";
    while (pos < linea.length() && linea[pos] != '|') {
        campo += linea[pos];
        pos++;
    }
    pos++;   // salta la barra
    return campo;
}

bool Usuario::cargarDesdeLinea(const string& linea) {
    int barras = 0;
    for (unsigned int i = 0; i < linea.length(); i++) {
        if (linea[i] == '|') barras++;
    }
    if (barras != 8) {
        return false;
    }

    unsigned int pos = 0;
    id               = std::stoi(siguienteCampo(linea, pos));
    nombre           = siguienteCampo(linea, pos);
    fechaNac         = std::stoi(siguienteCampo(linea, pos));
    correo           = siguienteCampo(linea, pos);
    fotoPerfil       = siguienteCampo(linea, pos);
    clave            = siguienteCampo(linea, pos);
    ciudad           = siguienteCampo(linea, pos);
    pais             = siguienteCampo(linea, pos);
    fechaInscripcion = std::stoi(siguienteCampo(linea, pos));

    return true;
}

static void mostrarFecha(unsigned int fecha) {
    unsigned int anio = fecha / 10000;
    unsigned int mes = (fecha / 100) % 100;
    unsigned int dia = fecha % 100;
    cout << anio << "-";
    if (mes < 10) cout << "0";
    cout << mes << "-";
    if (dia < 10) cout << "0";
    cout << dia;
}

void Usuario::mostrarUsuario() const {
    cout << "Id: " << id << endl;
    cout << "Usuario: " << nombre << endl;
    cout << "Nacimiento: ";
    mostrarFecha(fechaNac);
    cout << endl;
    cout << "Correo: " << correo << endl;
    cout << "Foto de perfil: " << fotoPerfil << endl;
    cout << "Ciudad: " << ciudad << ", " << pais << endl;
    cout << "Inscripcion: ";
    mostrarFecha(fechaInscripcion);
    cout << endl;


}

// --- Implementación de los setters para modificar los datos del usuario ---
void Usuario::setId(unsigned short i) { id = i; }
void Usuario::setNombre(const string& nom) { nombre = nom; }
void Usuario::setFechaNac(unsigned int fnac) { fechaNac = fnac; }
void Usuario::setCorreo(const string& cor) { correo = cor; }
void Usuario::setFotoPerfil(const string& foto) { fotoPerfil = foto; }
void Usuario::setClave(const string& cla) { clave = cla; }
void Usuario::setCiudad(const string& ciu) { ciudad = ciu; }
void Usuario::setPais(const string& pai) { pais = pai; }
void Usuario::setFechaInscripcion(unsigned int finsc) { fechaInscripcion = finsc; }