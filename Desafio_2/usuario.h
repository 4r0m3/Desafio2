#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

class Usuario {
private:
    unsigned short id;
    string nombre;
    unsigned int fechaNac;
    string correo;
    string fotoPerfil;
    string clave;
    string ciudad;
    string pais;
    unsigned int fechaInscripcion;

    // Devuelve el texto desde 'pos' hasta la siguiente '|' y avanza 'pos'.
    static string siguienteCampo(const string& linea, unsigned int& pos);

public:
    Usuario();
    Usuario(unsigned short i, const string& nom, unsigned int fnac, const string& cor,
            const string& foto, const string& cla, const string& ciu,
            const string& pai, unsigned int finsc);
    Usuario(const Usuario& otro);
    ~Usuario();
    Usuario& operator=(const Usuario& otro);

    unsigned short getId() const;
    string getNombre() const;
    unsigned int getFechaNac() const;
    string getCorreo() const;
    string getFotoPerfil() const;
    string getClave() const;
    string getCiudad() const;
    string getPais() const;
    unsigned int getFechaInscripcion() const;

    void setId(unsigned short i);
    void setNombre(const string& nom);
    void setFechaNac(unsigned int fnac);
    void setCorreo(const string& cor);
    void setFotoPerfil(const string& foto);
    void setClave(const string& cla);
    void setCiudad(const string& ciu);
    void setPais(const string& pai);
    void setFechaInscripcion(unsigned int finsc);

    bool cargarDesdeLinea(const string& linea);
    void mostrarUsuario() const;
};

#endif