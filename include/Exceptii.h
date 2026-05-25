#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <stdexcept>
#include <string>

class EroareJoc : public std::runtime_error {
public:
    explicit EroareJoc(const std::string& mesaj);
};

class EroareInitializare : public EroareJoc {
public:
    explicit EroareInitializare(const std::string& mesaj);
};

class EroareFisierLipsa : public EroareInitializare {
public:
    explicit EroareFisierLipsa(const std::string& mesaj);
};

class EroareFormatFisier : public EroareInitializare {
public:
    explicit EroareFormatFisier(const std::string& mesaj);
};

class EroareLogica : public EroareJoc {
public:
    explicit EroareLogica(const std::string& mesaj);
};

class EroareActiuneInvalida : public EroareLogica {
public:
    explicit EroareActiuneInvalida(const std::string& mesaj);
};

#endif
