#include "Album.h"
#include <iostream>
#include "Foto.h"
using namespace std;

int main() {
    // 1. Crear fotos (constructor con parametros)
    Foto f1("2026-03-15", 2048, "/users/x/juanito76/albums/Cartagena2026/Malecon2612.png", 0);
    Foto f2("2026-03-16", 1500, "/users/x/juanito76/albums/Cartagena2026/Bocagrande1.png", 5);

    // 2. Usar funciones de Foto
    f1.darLike();
    f1.darLike();
    f1.quitarLike();
    f1.setTamano(2100);
    cout << "--- Foto 1 ---" << endl;
    f1.mostrarFoto();
    cout << "Likes (getter): " << f1.getLikes() << endl;

    // 3. Copiar una foto (constructor de copia)
    Foto f3 = f2;
    f3.darLike();
    cout << "\nLikes f2: " << f2.getLikes() << " | likes copia f3: " << f3.getLikes() << endl;

    // 4. Crear un album con su primera foto
    Album album("Cartagena2026", "/users/x/juanito76/albums/Cartagena2026", "amigos", f1);

    // 5. Agregar mas fotos
    album.agregarFoto(f2);
    album.agregarFoto(f3);

    // 6. Mostrar el album y recorrer sus fotos
    cout << "\n--- Album ---" << endl;
    album.mostrarAlbum();
    for (int i = 0; i < album.getCantFotos(); i++) {
        cout << "\nFoto " << i + 1 << ":" << endl;
        album.getFoto(i).mostrarFoto();
    }

    // 7. Dar like a una foto DENTRO del album (getFoto devuelve referencia)
    album.getFoto(0).darLike();
    cout << "\nLikes foto 1 del album: " << album.getFoto(0).getLikes() << endl;

    // 8. Setters del album
    album.setPrivacidad("publico");
    cout << "Nueva privacidad: " << album.getPrivacidad() << endl;

    // 9. Copiar el album (constructor de copia): la copia es independiente
    Album copia = album;
    copia.getFoto(0).darLike();
    cout << "\nLikes foto 1 -> original: " << album.getFoto(0).getLikes()
         << " | copia: " << copia.getFoto(0).getLikes() << endl;

    return 0;
}