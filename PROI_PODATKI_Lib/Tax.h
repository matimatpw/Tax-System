#pragma once
#include <string>

class Tax
{
public:
    virtual double calculate_tax(double inc) = 0;
};

// FIRMA-----
class Vat : public Tax {
public:
    //double operator()(double inc);
    // double inComeWithVat =  Vat(income)
    double calculate_tax(double inc);
};

class Cit : public Tax {
    double calculate_tax(double inc);
};


// Osoba FIzyczna-----
class Pit : public Tax {
    double calculate_tax(double inc);
};

class Pon : public Tax { //Podatek Od Nieruchomosci
    double calculate_tax(double inc);
};


//FIrma i Osoba Fizyczna
class Zus : public Tax {
    double calculate_tax(double inc);
};