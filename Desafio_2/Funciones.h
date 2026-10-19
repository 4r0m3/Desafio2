#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Datos.h"
#include "Lista.h"
#include "Usuario.h"
#include "Mensaje.h"
#include "solicitudamistad.h"
#include "Album.h"
#include "Foto.h"
#include <stdexcept>

using namespace std;

// --- PROTOTIPOS DE FUNCIONES ---
string leer(string texto);
string campo(const string& linea, int numero);
bool esFechaValida(const string& fecha);
void cargarUsuarios(Datos& datos, Lista<Usuario>& usuarios);
void cargarAmistades(Datos& datos, Lista<int>& amigosA, Lista<int>& amigosB);
void cargarSolicitudes(Datos& datos, Lista<SolicitudAmistad>& solicitudes);
void cargarMensajes(Datos& datos, Lista<Mensaje>& mensajes);
void cargarAlbumes(Datos& datos, Lista<Album>& albumes, Lista<int>& duenos);
void cargarFotos(Datos& datos, Lista<Album>& albumes, Lista<int>& duenos);
void guardarFotos(Datos& datos, Lista<Album>& albumes, Lista<int>& duenos);
int buscarUsuario(Lista<Usuario>& usuarios, int id);
bool sonAmigos(Lista<int>& amigosA, Lista<int>& amigosB, int a, int b);
void verAmigos(Lista<Usuario>& usuarios, Lista<int>& amigosA, Lista<int>& amigosB, int id);
void verSolicitudes(Lista<SolicitudAmistad>& solicitudes, Lista<int>& amigosA, Lista<int>& amigosB, int id);
void enviarSolicitud(Lista<Usuario>& usuarios, Lista<SolicitudAmistad>& solicitudes, Lista<int>& amigosA, Lista<int>& amigosB, int id);
void verMensajes(Lista<Mensaje>& mensajes, int id);
void enviarMensaje(Lista<Usuario>& usuarios, Lista<Mensaje>& mensajes, Lista<int>& amigosA, Lista<int>& amigosB, int id);
void verAlbumes(Lista<Album>& albumes, Lista<int>& duenos, int dueno, int actual, bool amigos);
void usuarioConMasAmigos(Datos& datos, Lista<Usuario>& usuarios);
void gestionarPerfil(Usuario& usuario);
void guardarDatos(Datos& datos, Lista<Usuario>& usuarios, Lista<int>& amigosA, Lista<int>& amigosB, Lista<SolicitudAmistad>& solicitudes, Lista<Mensaje>& mensajes);
int buscarUsuarioPorNombre(Lista<Usuario>& usuarios, const string& nombre);
int iniciarSesion(Lista<Usuario>& usuarios, int id);
int iniciarSesion(Lista<Usuario>& usuarios, const string& nombre);
int iniciarSesion(Lista<Usuario>& usuarios);
void mostrarMemoria(Lista<Usuario>& usuarios,
                    Lista<int>& amigosA, Lista<int>& amigosB,
                    Lista<SolicitudAmistad>& solicitudes,
                    Lista<Mensaje>& mensajes,
                    Lista<Album>& albumes, Lista<int>& duenos);
void visitarPerfil(Lista<Usuario>& usuarios, Lista<int>& amigosA, Lista<int>& amigosB,
                   Lista<Album>& albumes, Lista<int>& duenos, int id);
// --- IMPLEMENTACIÓN DE LAS FUNCIONES ---

inline string leer(string texto) {
    string respuesta;
    cout << texto;
    getline(cin, respuesta);
    return respuesta;
}

inline string campo(const string& linea, int numero) {
    int actual = 0;
    string resultado = "";
    for (unsigned int i = 0; i < linea.length(); i++) {
        if (linea[i] == '|') actual++;
        else if (actual == numero) resultado += linea[i];
    }
    return resultado;
}

inline void cargarUsuarios(Datos& datos, Lista<Usuario>& usuarios) {
    ifstream archivo(datos.getUsuarios());
    if (!archivo.is_open()) return;
    string linea;
    while (getline(archivo, linea)) {
        Usuario u;
        if (u.cargarDesdeLinea(linea)) usuarios.agregar(u);
    }
}

inline void cargarAmistades(Datos& datos, Lista<int>& amigosA, Lista<int>& amigosB) {
    ifstream archivo(datos.getAmistades());
    if (!archivo.is_open()) return;
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        amigosA.agregar(std::stoi(campo(linea, 0)));
        amigosB.agregar(std::stoi(campo(linea, 1)));
    }
}

inline void cargarSolicitudes(Datos& datos, Lista<SolicitudAmistad>& solicitudes) {
    ifstream archivo(datos.getSolicitudes());
    if (!archivo.is_open()) return;
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        int emisor = std::stoi(campo(linea, 0));
        int receptor = std::stoi(campo(linea, 1));
        int estado = std::stoi(campo(linea, 2));
        SolicitudAmistad s(emisor, receptor);
        if (estado == 1) s.aceptar();
        else if (estado == 2) s.rechazar();
        solicitudes.agregar(s);
    }
}

inline void cargarMensajes(Datos& datos, Lista<Mensaje>& mensajes) {
    ifstream archivo(datos.getMensajes());
    if (!archivo.is_open()) return;
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        Mensaje m(std::stoi(campo(linea, 0)), std::stoi(campo(linea, 1)), campo(linea, 4), std::stoi(campo(linea, 2)));
        if (campo(linea, 3) == "1") m.marcarLeido();
        mensajes.agregar(m);
    }
}

inline void cargarAlbumes(Datos& datos, Lista<Album>& albumes, Lista<int>& duenos) {
    ifstream archivo(datos.getAlbumes());
    if (!archivo.is_open()) return;
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        duenos.agregar(std::stoi(campo(linea, 0)));
        albumes.agregar(Album(campo(linea, 1), campo(linea, 2), campo(linea, 3)));
    }
}

inline void cargarFotos(Datos& datos, Lista<Album>& albumes, Lista<int>& duenos) {
    ifstream archivo(datos.getFotos());
    if (!archivo.is_open()) return;
    string linea;
    int inicio = 0;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        int dueno = std::stoi(campo(linea, 0));
        string nombre = campo(linea, 1);

        int k = inicio;
        while (k < albumes.getCantidad() && !(duenos[k] == dueno && albumes[k].getNombre() == nombre)) k++;
        if (k < albumes.getCantidad()) {
            albumes[k].agregarFoto(Foto(std::stoi(campo(linea, 2)), std::stod(campo(linea, 3)), campo(linea, 4), std::stoi(campo(linea, 5))));
            inicio = k;
        }
    }
}

inline int buscarUsuario(Lista<Usuario>& usuarios, int id) {
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        if (usuarios[i].getId() == id) return i;
    }
    return -1;
}

inline bool sonAmigos(Lista<int>& amigosA, Lista<int>& amigosB, int a, int b) {
    for (int i = 0; i < amigosA.getCantidad(); i++) {
        if ((amigosA[i] == a && amigosB[i] == b) || (amigosA[i] == b && amigosB[i] == a)) return true;
    }
    return false;
}

inline void verAmigos(Lista<Usuario>& usuarios, Lista<int>& amigosA, Lista<int>& amigosB, int id) {
    int total = 0;
    for (int i = 0; i < amigosA.getCantidad(); i++) {
        int otro = (amigosA[i] == id) ? amigosB[i] : (amigosB[i] == id ? amigosA[i] : -1);
        if (otro != -1) {
            int pos = buscarUsuario(usuarios, otro);
            if (pos != -1) {
                cout << otro << " - " << usuarios[pos].getNombre() << endl;
                total++;
            }
        }
    }
    cout << "Total de amigos: " << total << endl;
}

inline void verSolicitudes(Lista<SolicitudAmistad>& solicitudes, Lista<int>& amigosA, Lista<int>& amigosB, int id) {
    int pendientes = 0;
    for (int i = 0; i < solicitudes.getCantidad(); i++) {
        if (solicitudes[i].getReceptor() == id && solicitudes[i].estaPendiente()) {
            pendientes++;
            cout << endl;
            solicitudes[i].mostrarSolicitud();
            string op = leer("1 aceptar, 2 rechazar, otra tecla dejar pendiente: ");
            if (op == "1") {
                solicitudes[i].aceptar();
                int emisor = solicitudes[i].getEmisor();
                if (!sonAmigos(amigosA, amigosB, emisor, id)) {
                    amigosA.agregar(emisor);
                    amigosB.agregar(id);
                }
                cout << "Solicitud aceptada" << endl;
            } else if (op == "2") {
                solicitudes[i].rechazar();
                cout << "Solicitud rechazada" << endl;
            }
        }
    }
    if (pendientes == 0) cout << "No tienes solicitudes pendientes" << endl;
}

inline void enviarSolicitud(Lista<Usuario>& usuarios, Lista<SolicitudAmistad>& solicitudes, Lista<int>& amigosA, Lista<int>& amigosB, int id) {
    int destino = std::stoi(leer("Id del usuario al que quieres enviar la solicitud: "));
    if (destino == id || buscarUsuario(usuarios, destino) == -1 || sonAmigos(amigosA, amigosB, id, destino)) {
        cout << "Accion invalida (usuario invalido, eres tu mismo, o ya son amigos)" << endl;
        return;
    }
    SolicitudAmistad nueva(id, destino), inversa(destino, id);
    for (int i = 0; i < solicitudes.getCantidad(); i++) {
        if (solicitudes[i].estaPendiente()) {
            if (solicitudes[i] == nueva) { cout << "Ya enviaste una solicitud" << endl; return; }
            if (solicitudes[i] == inversa) { cout << "Ese usuario ya te envio una solicitud" << endl; return; }
        }
    }
    solicitudes.agregar(nueva);
    cout << "Solicitud enviada" << endl;
}

inline void verMensajes(Lista<Mensaje>& mensajes, int id) {
    int total = 0;
    for (int i = 0; i < mensajes.getCantidad(); i++) {
        if (mensajes[i].getReceptor() == id) {
            cout << endl;
            mensajes[i].mostrarMensaje();
            mensajes[i].marcarLeido();
            total++;
        }
    }
    if (total == 0) cout << "No tienes mensajes" << endl;
}

inline void enviarMensaje(Lista<Usuario>& usuarios, Lista<Mensaje>& mensajes, Lista<int>& amigosA, Lista<int>& amigosB, int id) {
    int destino = std::stoi(leer("Id del amigo: "));
    if (buscarUsuario(usuarios, destino) == -1 || !sonAmigos(amigosA, amigosB, id, destino)) {
        cout << "No puedes enviar mensaje (usuario no existe o no son amigos)" << endl;
        return;
    }

    string texto = leer("Mensaje: ");
    string strFecha = "";

    // Bucle que valida estrictamente los 8 dígitos y el calendario mediante el try-catch
    do {
        strFecha = leer("Fecha (aaaammdd - exactamente 8 digitos): ");
        if (!esFechaValida(strFecha)) {
            cout << "Fecha invalida. Asegurese de ingresar exactamente 8 numeros en formato aaaammdd validos. Intente de nuevo." << endl;
        }
    } while (!esFechaValida(strFecha));

    int fechaNumerica = std::stoi(strFecha);
    Mensaje m(id, destino, texto, fechaNumerica);

    if (!m.esValido()) {
        cout << "Mensaje invalido" << endl;
        return;
    }

    mensajes.agregar(m);
    cout << "Mensaje enviado exitosamente" << endl;
}

inline void verAlbumes(Lista<Album>& albumes, Lista<int>& duenos, int dueno, int actual, bool amigos) {
    Lista<int> visibles;
    for (int k = 0; k < albumes.getCantidad(); k++) {
        if (duenos[k] == dueno) {
            string priv = albumes[k].getPrivacidad();
            if (dueno == actual || priv == "publico" || (priv == "amigos" && amigos)) {
                visibles.agregar(k);
            }
        }
    }
    if (visibles.getCantidad() == 0) { cout << "No hay albumes disponibles" << endl; return; }

    for (int i = 0; i < visibles.getCantidad(); i++) {
        cout << endl << i + 1 << ". ";
        albumes[visibles[i]].mostrarAlbum();
    }
    int op = std::stoi(leer("Numero de album para abrir (0 para volver): "));
    if (op >= 1 && op <= visibles.getCantidad()) {
        albumes[visibles[op - 1]].carrusel();
        cin.ignore(1000, '\n');
    }
}

inline void usuarioConMasAmigos(Datos& datos, Lista<Usuario>& usuarios) {
    Lista<int> cantidades;
    if (!datos.contarAmigos(usuarios.getCantidad(), cantidades)) { cout << "Error leyendo amistades" << endl; return; }
    int mayor = 0;
    for (int i = 1; i < cantidades.getCantidad(); i++) {
        if (cantidades[i] > cantidades[mayor]) mayor = i;
    }
    cout << "Usuario con mas amigos: " << usuarios[mayor].getNombre() << " (" << cantidades[mayor] << " amigos)" << endl;
}

inline void gestionarPerfil(Usuario& usuario) {
    int opcion;
    do {
        cout << "\n===============================\n";
        cout << "         MI PERFIL            \n";
        cout << "===============================\n";
        usuario.mostrarUsuario();
        cout << "-------------------------------\n";
        cout << "1. Modificar nombre\n";
        cout << "2. Modificar clave\n";
        cout << "3. Modificar correo\n";
        cout << "4. Modificar foto de perfil\n";
        cout << "5. Modificar ciudad y pais\n";
        cout << "6. Modificar fecha de nacimiento\n";
        cout << "0. Volver al menu principal\n";

        string entradaOpcion = leer("Selecciona una opcion para modificar: ");
        try {
            opcion = std::stoi(entradaOpcion);
        } catch (const std::exception& e) {
            opcion = -1; // Fuerza una opción inválida si ingresan letras
        }

        switch (opcion) {
        case 1: {
            string nuevoNombre;
            bool contieneBarra;
            do {
                contieneBarra = false;
                nuevoNombre = leer("Ingresa el nuevo nombre (No puede contener '|'): ");

                for (char c : nuevoNombre) {
                    if (c == '|') {
                        contieneBarra = true;
                        break;
                    }
                }

                if (contieneBarra) {
                    cout << "[Error]: El nombre no puede contener el caracter '|'. Intenta de nuevo.\n";
                } else if (nuevoNombre.empty()) {
                    cout << "[Error]: El nombre no puede estar vacio.\n";
                    contieneBarra = true;
                }
            } while (contieneBarra);

            usuario.setNombre(nuevoNombre);
            cout << "¡Nombre actualizado con exito!\n";
            break;
        }
        case 2: {
            string nuevaClave;
            bool contieneBarra;
            do {
                contieneBarra = false;
                nuevaClave = leer("Ingresa la nueva clave (No puede contener '|'): ");

                for (char c : nuevaClave) {
                    if (c == '|') {
                        contieneBarra = true;
                        break;
                    }
                }

                if (contieneBarra) {
                    cout << "[Error]: La clave no puede contener el caracter '|'. Intenta de nuevo.\n";
                } else if (nuevaClave.empty()) {
                    cout << "[Error]: La clave no puede estar vacia.\n";
                    contieneBarra = true;
                }
            } while (contieneBarra);

            usuario.setClave(nuevaClave);
            cout << "¡Clave actualizada con exito!\n";
            break;
        }
        case 3: {
            string nuevoCorreo;
            bool contieneBarra;
            do {
                contieneBarra = false;
                nuevoCorreo = leer("Ingresa el nuevo correo (No puede contener '|'): ");

                for (char c : nuevoCorreo) {
                    if (c == '|') {
                        contieneBarra = true;
                        break;
                    }
                }

                if (contieneBarra) {
                    cout << "[Error]: El correo no puede contener el caracter '|'. Intenta de nuevo.\n";
                } else if (nuevoCorreo.empty()) {
                    cout << "[Error]: El correo no puede estar vacio.\n";
                    contieneBarra = true;
                }
            } while (contieneBarra);

            usuario.setCorreo(nuevoCorreo);
            cout << "¡Correo actualizado con exito!\n";
            break;
        }
        case 4: {
            string nuevaFoto;
            bool contieneBarra;
            do {
                contieneBarra = false;
                nuevaFoto = leer("Ingresa la nueva ruta de la foto de perfil (No puede contener '|'): ");

                for (char c : nuevaFoto) {
                    if (c == '|') {
                        contieneBarra = true;
                        break;
                    }
                }

                if (contieneBarra) {
                    cout << "[Error]: La ruta no puede contener el caracter '|'. Intenta de nuevo.\n";
                } else if (nuevaFoto.empty()) {
                    cout << "[Error]: La ruta no puede estar vacia.\n";
                    contieneBarra = true;
                }
            } while (contieneBarra);

            usuario.setFotoPerfil(nuevaFoto);
            cout << "¡Foto de perfil actualizada con exito!\n";
            break;
        }
        case 5: {
            string nuevaCiudad, nuevoPais;
            bool contieneBarra;
            do {
                contieneBarra = false;
                nuevaCiudad = leer("Ingresa la nueva ciudad (No puede contener '|'): ");
                nuevoPais = leer("Ingresa el nuevo pais (No puede contener '|'): ");

                for (char c : nuevaCiudad) {
                    if (c == '|') { contieneBarra = true; break; }
                }
                for (char c : nuevoPais) {
                    if (c == '|') { contieneBarra = true; break; }
                }

                if (contieneBarra) {
                    cout << "[Error]: Ciudad o pais no pueden contener el caracter '|'. Intenta de nuevo.\n";
                } else if (nuevaCiudad.empty() || nuevoPais.empty()) {
                    cout << "[Error]: Los campos de ubicacion no pueden estar vacios.\n";
                    contieneBarra = true;
                }
            } while (contieneBarra);

            usuario.setCiudad(nuevaCiudad);
            usuario.setPais(nuevoPais);
            cout << "¡Ubicacion actualizada con exito!\n";
            break;
        }
        case 6: {
            string strFecha;
            do {
                strFecha = leer("Ingresa la nueva fecha de nacimiento (aaaammdd - exactamente 8 digitos): ");
                if (!esFechaValida(strFecha)) {
                    cout << "[Error]: Fecha invalida o formato incorrecto. Asegurese de ingresar 8 numeros validos.\n";
                }
            } while (!esFechaValida(strFecha));

            int nuevaFecha = std::stoi(strFecha);
            usuario.setFechaNac(nuevaFecha);
            cout << "¡Fecha de nacimiento actualizada con exito!\n";
            break;
        }
        case 0:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "Opcion invalida, intenta de nuevo.\n";
            break;
        }
    } while (opcion != 0);
}

inline void guardarDatos(Datos& datos, Lista<Usuario>& usuarios, Lista<int>& amigosA, Lista<int>& amigosB, Lista<SolicitudAmistad>& solicitudes, Lista<Mensaje>& mensajes) {
    ofstream archivoU(datos.getUsuarios());
    if (archivoU.is_open()) {
        for (int i = 0; i < usuarios.getCantidad(); i++) {
            Usuario u = usuarios[i];
            archivoU << u.getId() << '|' << u.getNombre() << '|' << u.getFechaNac() << '|'
                     << u.getCorreo() << '|' << u.getFotoPerfil() << '|' << u.getClave() << '|'
                     << u.getCiudad() << '|' << u.getPais() << '|' << u.getFechaInscripcion() << '\n';
        }
        archivoU.close();
    }

    ofstream archivoA(datos.getAmistades());
    if (archivoA.is_open()) {
        for (int i = 0; i < amigosA.getCantidad(); i++) {
            archivoA << amigosA[i] << '|' << amigosB[i] << '\n';
        }
        archivoA.close();
    }

    ofstream archivoS(datos.getSolicitudes());
    if (archivoS.is_open()) {
        for (int i = 0; i < solicitudes.getCantidad(); i++) {
            int estadoNum = 0;
            archivoS << solicitudes[i].getEmisor() << '|' << solicitudes[i].getReceptor() << '|' << estadoNum << '\n';
        }
        archivoS.close();
    }

    ofstream archivoM(datos.getMensajes());
    if (archivoM.is_open()) {
        for (int i = 0; i < mensajes.getCantidad(); i++) {
            Mensaje m = mensajes[i];
            int leidoNum = 0;
            archivoM << m.getEmisor() << '|'
                     << m.getReceptor() << '|'
                     << m.getFecha() << '|'
                     << leidoNum << '|'
                     << m.getContenido() << '\n';
        }
        archivoM.close();
    }
}

inline int buscarUsuarioPorNombre(Lista<Usuario>& usuarios, const string& nombre) {
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        if (usuarios[i].getNombre() == nombre) return i;
    }
    return -1;
}

inline int iniciarSesion(Lista<Usuario>& usuarios, int id) {
    int pos = buscarUsuario(usuarios, id);
    string clave = leer("Clave: ");
    if (pos != -1 && usuarios[pos].getClave() == clave) return pos;
    cout << "Datos incorrectos" << endl;
    return -1;
}

inline int iniciarSesion(Lista<Usuario>& usuarios, const string& nombre) {
    int pos = buscarUsuarioPorNombre(usuarios, nombre);
    string clave = leer("Clave: ");
    if (pos != -1 && usuarios[pos].getClave() == clave) return pos;
    cout << "Datos incorrectos" << endl;
    return -1;
}

inline int iniciarSesion(Lista<Usuario>& usuarios) {
    int resultado = -1;
    do {
        string opcion = leer("Como deseas iniciar sesion? (1. ID, 2. Nombre, -1 para salir): ");
        if (opcion == "-1") return -1;

        if (opcion == "1") {
            try {
                string entradaId = leer("Id de usuario: ");
                int id = std::stoi(entradaId);
                resultado = iniciarSesion(usuarios, id);
                if (resultado != -1) return resultado;
            } catch (const std::exception& e) {
                cout << "[Error]: Por favor, ingrese un numero de ID valido." << endl;
            }
        }
        else if (opcion == "2") {
            string nombre = leer("Nombre de usuario: ");
            resultado = iniciarSesion(usuarios, nombre);
            if (resultado != -1) return resultado;
        }
        else {
            cout << "Opcion invalida. Intenta de nuevo." << endl;
        }
    } while (true);
}

inline bool esFechaValida(const string& strFecha) {
    try {
        // Validar que la cadena tenga exactamente 8 caracteres (dígitos)
        if (strFecha.length() != 8) {
            throw std::invalid_argument("La fecha debe contener exactamente 8 digitos (aaaammdd).");
        }

        // Verificar que todos los caracteres sean números
        for (char c : strFecha) {
            if (!isdigit(c)) {
                throw std::invalid_argument("La fecha solo debe contener numeros.");
            }
        }

        // Convertir a entero largo para extraer año, mes y día
        unsigned int fecha = std::stoul(strFecha);
        unsigned int anio = fecha / 10000;
        unsigned int mes = (fecha / 100) % 100;
        unsigned int dia = fecha % 100;

        if (anio < 2000 || anio > 2100) return false;
        if (mes < 1 || mes > 12) return false;
        if (dia < 1) return false;

        unsigned int diasMes = 31;
        if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
            diasMes = 30;
        } else if (mes == 2) {
            bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
            diasMes = bisiesto ? 29 : 28;
        }

        return dia <= diasMes;

    } catch (const std::exception& e) {
        return false;
    }
}
inline void guardarFotos(Datos& datos, Lista<Album>& albumes, Lista<int>& duenos) {
    ofstream archivo(datos.getFotos());
    if (!archivo.is_open()) return;

    for (int k = 0; k < albumes.getCantidad(); k++) {
        for (int f = 0; f < albumes[k].getCantFotos(); f++) {
            Foto* foto = albumes[k].getFoto(f);
            archivo << duenos[k] << '|'
                    << albumes[k].getNombre() << '|'
                    << foto->getFechaCaptura() << '|'
                    << foto->getTamano() << '|'
                    << foto->getRuta() << '|'
                    << foto->getLikes() << '\n';
        }
    }
    archivo.close();
}

inline void mostrarMemoria(Lista<Usuario>& usuarios,
                           Lista<int>& amigosA, Lista<int>& amigosB,
                           Lista<SolicitudAmistad>& solicitudes,
                           Lista<Mensaje>& mensajes,
                           Lista<Album>& albumes, Lista<int>& duenos) {
    unsigned int reservada = 0;
    unsigned int usada = 0;

    reservada += usuarios.getCapacidad()    * sizeof(Usuario);
    usada     += usuarios.getCantidad()     * sizeof(Usuario);

    reservada += amigosA.getCapacidad()     * sizeof(int);
    usada     += amigosA.getCantidad()      * sizeof(int);

    reservada += amigosB.getCapacidad()     * sizeof(int);
    usada     += amigosB.getCantidad()      * sizeof(int);

    reservada += solicitudes.getCapacidad() * sizeof(SolicitudAmistad);
    usada     += solicitudes.getCantidad()  * sizeof(SolicitudAmistad);

    reservada += mensajes.getCapacidad()    * sizeof(Mensaje);
    usada     += mensajes.getCantidad()     * sizeof(Mensaje);

    reservada += albumes.getCapacidad()     * sizeof(Album);
    usada     += albumes.getCantidad()      * sizeof(Album);

    reservada += duenos.getCapacidad()      * sizeof(int);
    usada     += duenos.getCantidad()       * sizeof(int);

    for (int k = 0; k < albumes.getCantidad(); k++) {
        reservada += albumes[k].getCapacidad() * sizeof(Foto);
        usada     += albumes[k].getCantFotos() * sizeof(Foto);
    }

    cout << "[Memoria usada:     " << usada << " bytes]\n";
    cout << "[Memoria reservada: " << reservada << " bytes]\n";

}


inline void visitarPerfil(Lista<Usuario>& usuarios, Lista<int>& amigosA, Lista<int>& amigosB,
                          Lista<Album>& albumes, Lista<int>& duenos, int id) {
    int idAmigo;
    try {
        idAmigo = std::stoi(leer("Id del amigo a visitar: "));
    } catch (const std::exception& e) {
        cout << "Id invalido" << endl;
        return;
    }

    int pos = buscarUsuario(usuarios, idAmigo);
    if (pos == -1) {
        cout << "Ese usuario no existe" << endl;
        return;
    }
    if (idAmigo == id || !sonAmigos(amigosA, amigosB, id, idAmigo)) {
        cout << "Solo puedes visitar el perfil de tus amigos" << endl;
        return;
    }

    // El contador empieza aqui, al entrar al perfil del amigo
    unsigned long long iter = 0;
    int opcion;

    do {
        iter++;   // cada vuelta del menu cuenta

        cout << "\n===============================\n";
        cout << "     PERFIL DE AMIGO\n";
        cout << "===============================\n";
        usuarios[pos].mostrarUsuario();   // id, nombre, nacimiento, correo, foto, ciudad, pais, inscripcion
        cout << "Memoria del usuario: sizeof(Usuario) = " << sizeof(Usuario) << " bytes\n";
        cout << "-------------------------------\n";
        cout << "Iteraciones acumuladas: " << iter << endl;
        cout << "1. Ver sus albumes\n0. Volver\n";

        try {
            opcion = std::stoi(leer("Opcion: "));
        } catch (const std::exception& e) {
            opcion = -1;
        }

        if (opcion == 1) {
            unsigned long long iterAntes = iter;
            Lista<int> visibles;
            for (int k = 0; k < albumes.getCantidad(); k++) {
                iter++;
                if (duenos[k] == idAmigo) {
                    string priv = albumes[k].getPrivacidad();
                    if (priv == "publico" || priv == "amigos") visibles.agregar(k);
                }
            }

            if (visibles.getCantidad() == 0) {
                cout << "No hay albumes disponibles" << endl;
                continue;
            }

            unsigned long long memAlbumes = 0;   // acumulado de los albumes listados
            for (int i = 0; i < visibles.getCantidad(); i++) {
                iter++;
                Album& a = albumes[visibles[i]];
                cout << endl << i + 1 << ". ";
                a.mostrarAlbum();

                unsigned long long memObjeto = sizeof(Album);
                unsigned long long memFotosUsada = (unsigned long long)a.getCantFotos() * sizeof(Foto);
                unsigned long long memFotosReservada = (unsigned long long)a.getCapacidad() * sizeof(Foto);

                cout << "Memoria: sizeof(Album) = " << memObjeto << " bytes | "
                     << "fotos usadas = " << memFotosUsada << " bytes | "
                     << "fotos reservadas = " << memFotosReservada << " bytes\n";

                memAlbumes += memObjeto + memFotosReservada;
            }
            cout << "\nMemoria total de los albumes listados: " << memAlbumes << " bytes\n";

            cout << "Iteraciones usadas para entrar a los albumes: "
                 << iter - iterAntes << endl;

            int op;
            try {
                op = std::stoi(leer("Numero de album para abrir (0 para volver): "));
            } catch (const std::exception& e) {
                op = 0;
            }

            if (op >= 1 && op <= visibles.getCantidad()) {
                albumes[visibles[op - 1]].carruselConteo(iter);
                cin.ignore(1000, '\n');
            }
        } else if (opcion != 0) {
            cout << "Opcion invalida" << endl;
        }
    } while (opcion != 0);

    cout << "Total de iteraciones en este perfil: " << iter << endl;
    cout << "Memoria base del perfil visitado: " << sizeof(Usuario) << " bytes" << endl;
}

#endif