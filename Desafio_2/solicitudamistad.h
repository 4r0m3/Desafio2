#ifndef SOLICITUDAMISTAD_H
#define SOLICITUDAMISTAD_H
#include <string>
using namespace std;
const int PENDIENTE = 0;
const int ACEPTADA = 1;
const int RECHAZADA = 2;


class SolicitudAmistad
{
private:
    string emisor;
    string receptor;
    int estado;
public:
    SolicitudAmistad();
    SolicitudAmistad(string emi, string rec);
    SolicitudAmistad(const SolicitudAmistad& otra);
    ~SolicitudAmistad();

    //getter
    string getEmisor();
    string getReceptor();
    int getEstado();

    //acciones
    bool estaPendiente();
    bool aceptar();
    bool rechazar();
    void mostrarSolicitud();
};

#endif // SOLICITUDAMISTAD_H
