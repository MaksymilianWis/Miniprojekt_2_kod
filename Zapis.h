#ifndef KOLEJKA_PRIORYTETOWA_ZAPIS_H
#define KOLEJKA_PRIORYTETOWA_ZAPIS_H

#include <string>

class Zapis {
public:
    // Konstruktor przyjmujący nazwę pliku
    Zapis(const std::string& filename);

    // Metoda do zapisu danych do pliku CSV
    void shot(int iteration, unsigned duration, int size);

private:
    std::string filename; // Nazwa pliku
};


#endif //KOLEJKA_PRIORYTETOWA_ZAPIS_H
