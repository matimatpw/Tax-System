#pragma once
#include <string>

class Tax
{
public:
    virtual double operator()(double inc) const noexcept = 0;
    virtual std::string getName() const noexcept = 0;
};

// FIRMA-----
class Vat : public Tax {
public:
    double operator()(double inc) const noexcept;
    std::string getName() const noexcept;
    // double inComeWithVat =  Vat(income)
    /*double calculate_tax(double inc);*/
};

class Cit : public Tax {
public:
    double operator()(double inc) const noexcept;
    std::string getName() const noexcept ;
};


// Osoba FIzyczna-----
class Pit : public Tax {
public:
    double operator()(double inc) const noexcept;
    std::string getName() const noexcept;
};

class Pon : public Tax {
public:
    double operator()(double inc) const noexcept;
    std::string getName() const noexcept;
};


//FIrma i Osoba Fizyczna
class Zus : public Tax {
public:
    double operator()(double inc) const noexcept;
    std::string getName() const noexcept;
};