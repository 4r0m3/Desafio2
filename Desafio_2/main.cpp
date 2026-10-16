#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Funciones.h"

using namespace std;

int main() {
    Datos datos;

    // Verificamos si el archivo de usuarios ya existe
    ifstream archivoVerificacion(datos.getUsuarios());

    if (!archivoVerificacion.is_open()) {
        archivoVerificacion.close();
        int n = std::stoi(leer("Archivos no encontrados. Cantidad de usuarios a generar: "));
        if (!datos.generarArchivos(n)) {
            cout << "Error generando archivos" << endl;
            return 1;
        }
        cout << "¡Archivos generados exitosamente!" << endl;
    } else {
        archivoVerificacion.close();
        cout << "Cargando datos existentes desde los archivos..." << endl;
    }

    Lista<Usuario> usuarios;
    Lista<int> amigosA, amigosB, duenos;
    Lista<SolicitudAmistad> solicitudes;
    Lista<Mensaje> mensajes;
    Lista<Album> albumes;

    cargarUsuarios(datos, usuarios);
    cargarAmistades(datos, amigosA, amigosB);
    cargarSolicitudes(datos, solicitudes);
    cargarMensajes(datos, mensajes);
    cargarAlbumes(datos, albumes, duenos);
    cargarFotos(datos, albumes, duenos);

    int pos = iniciarSesion(usuarios);
    if (pos == -1) return 0;
    int id = usuarios[pos].getId();
    cout << "Bienvenido " << usuarios[pos].getNombre() << endl;

    int opcion;
    do {
        cout << "\n1. Ver mi perfil\n2. Ver mis amigos\n3. Ver solicitudes recibidas\n4. Enviar solicitud\n5. Ver mensajes\n6. Enviar mensaje\n7. Ver mis albumes\n8. Ver albumes de otro\n9. Usuario con mas amigos\n0. Salir\n";
        opcion = std::stoi(leer("Opcion: "));

        switch (opcion) {
        case 1: gestionarPerfil(usuarios[pos]); break;
        case 2: verAmigos(usuarios, amigosA, amigosB, id); break;
        case 3: verSolicitudes(solicitudes, amigosA, amigosB, id); break;
        case 4: enviarSolicitud(usuarios, solicitudes, amigosA, amigosB, id); break;
        case 5: verMensajes(mensajes, id); break;
        case 6: enviarMensaje(usuarios, mensajes, amigosA, amigosB, id); break;
        case 7: verAlbumes(albumes, duenos, id, id, true); break;
        case 8: {
            int otro = std::stoi(leer("Id del usuario: "));
            if (buscarUsuario(usuarios, otro) == -1) cout << "Ese usuario no existe" << endl;
            else verAlbumes(albumes, duenos, otro, id, sonAmigos(amigosA, amigosB, id, otro));
            break;
        }
        case 9: usuarioConMasAmigos(datos, usuarios); break;
        case 0:
            guardarDatos(datos, usuarios, amigosA, amigosB, solicitudes, mensajes);
            guardarFotos(datos, albumes, duenos);
            cout << "Datos guardados exitosamente. Hasta luego" << endl;
            break;
        default: cout << "Opcion invalida" << endl; break;
        }
    } while (opcion != 0);

    return 0;
}