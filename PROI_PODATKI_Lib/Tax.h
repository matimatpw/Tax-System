#pragma once
#include <string>
#include <iostream>
class Tax
{
public:
    virtual double operator()(double inc) = 0;
    virtual std::string getName() = 0;
};

// FIRMA-----
class Vat : public Tax {
public:
    double operator()(double inc);
    std::string getName();
    // double inComeWithVat =  Vat(income)
    /*double calculate_tax(double inc);*/
};

class Cit : public Tax {
public:
    double operator()(double inc);
    std::string getName();
};


// Osoba FIzyczna-----
class Pit : public Tax {
public:
    double operator()(double inc);
    std::string getName();
};

class Pon : public Tax {
public:
    double operator()(double inc);
    std::string getName();
};


//FIrma i Osoba Fizyczna
class Zus : public Tax {
public:
    double operator()(double inc);
    std::string getName();
};