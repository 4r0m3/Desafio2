#ifndef LISTA_H
#define LISTA_H

template <typename T>
class Lista {
private:
    T* datos;
    int cantidad;
    int capacidad;

    void crecer() {
        capacidad = capacidad * 2;
        T* nuevo = new T[capacidad];
        for (int i = 0; i < cantidad; i++) {
            nuevo[i] = datos[i];
        }
        delete[] datos;
        datos = nuevo;
    }

public:
    Lista() {
        capacidad = 4;
        cantidad = 0;
        datos = new T[capacidad];
    }

    Lista(const Lista& otra) {
        cantidad = otra.cantidad;
        capacidad = otra.capacidad;
        datos = new T[capacidad];
        for (int i = 0; i < cantidad; i++) {
            datos[i] = otra.datos[i];
        }
    }

    ~Lista() {
        delete[] datos;
    }

    Lista& operator=(const Lista& otra) {
        if (this != &otra) {
            delete[] datos;
            cantidad = otra.cantidad;
            capacidad = otra.capacidad;
            datos = new T[capacidad];
            for (int i = 0; i < cantidad; i++) {
                datos[i] = otra.datos[i];
            }
        }
        return *this;
    }

    void agregar(const T& elemento) {
        if (cantidad >= capacidad) {
            crecer();
        }
        datos[cantidad] = elemento;
        cantidad++;
    }

    T& operator[](int i) {
        return datos[i];
    }

    const T& operator[](int i) const {
        return datos[i];
    }

    int getCantidad() const {
        return cantidad;
    }

    int getCapacidad() const {
        return capacidad;
    }
};

#endif