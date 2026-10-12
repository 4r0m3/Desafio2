#ifndef MENSAJE_H
#define MENSAJE_H
#include <string>
using namespace std;
const int Max_caracter = 512;

class Mensaje{
private:
    string emisor;
    string receptor;
    string contenido;
    string fecha;
    bool leido;

public:
    Mensaje();
    Mensaje(string emi, string rec, string mens, string fech);
    Mensaje(const Mensaje& otro);
    ~Mensaje();

//Getters
    string getEmisor();
    string getReceptor();
    string getContenido();
    string getFecha();
    bool getLeido();
//Setters
    void setContenido(string cont);
    void setFecha(string fec);
//acciones
    void marcarLeido();
    bool esValido();
    bool estaEnRango(string inicio, string fin);
    void mostrarMensaje();

};

#endif // MENSAJE_H
