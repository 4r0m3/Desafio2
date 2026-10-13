#ifndef MENSAJE_H
#define MENSAJE_H
#include <string>
using namespace std;
const unsigned short Max_caracter = 512;

class Mensaje {
private:
    unsigned short emisor;
    unsigned short receptor;
    unsigned int fecha;
    bool leido;
    string contenido;

public:

    Mensaje();
    Mensaje(unsigned short emi, unsigned short rec, const string& cont, unsigned int fec);
    Mensaje(const Mensaje& otro);
    Mensaje& operator=(const Mensaje& otro);
    ~Mensaje();

    unsigned short getEmisor() const;
    unsigned short getReceptor() const;
    const string& getContenido() const;
    unsigned int getFecha() const;
    bool getLeido() const;

    void setContenido(const string& cont);
    void setFecha(unsigned int fec);
    void setLeido(bool valor);
    void marcarLeido();

    bool esValido() const;
    bool estaEnRango(unsigned int inicio, unsigned int fin) const;
    bool operator<(const Mensaje& otro) const;

    void mostrarMensaje() const;
};

#endif
