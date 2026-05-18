#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <stdexcept>
#include <string>

// Ierarhie de excepții specifică proiectului — complet independentă de ierarhia VanatorAI

// Baza: erori legate de joc
class EroareJoc : public std::runtime_error {
public:
    explicit EroareJoc(const std::string& mesaj);
};

// Categorie 1: Erori legate de hartă
class EroareHarta : public EroareJoc {
public:
    explicit EroareHarta(const std::string& mesaj);
};

// Categorie 2: Erori legate de jucător
class EroareJucator : public EroareJoc {
public:
    explicit EroareJucator(const std::string& mesaj);
};

// Categorie 3: Erori legate de inventar / obiecte
class EroareInventar : public EroareJoc {
public:
    explicit EroareInventar(const std::string& mesaj);
};

#endif // EXCEPTII_H
