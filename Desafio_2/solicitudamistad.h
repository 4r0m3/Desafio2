#ifndef SOLICITUDAMISTAD_H
#define SOLICITUDAMISTAD_H

enum EstadoSolicitud {
    PENDIENTE,
    ACEPTADA,
    RECHAZADA
};

class SolicitudAmistad {
private:
    unsigned short emisor;
    unsigned short receptor;
    EstadoSolicitud estado;

public:
    SolicitudAmistad();
    SolicitudAmistad(unsigned short emi, unsigned short rec);
    SolicitudAmistad(const SolicitudAmistad& otra);
    ~SolicitudAmistad();

    SolicitudAmistad& operator=(const SolicitudAmistad& otra);
    bool operator==(const SolicitudAmistad& otra) const;

    unsigned short getEmisor() const;
    unsigned short getReceptor() const;
    int getEstado() const;

    bool estaPendiente() const;
    bool aceptar();
    bool rechazar();

    void mostrarSolicitud() const;
};

#endif