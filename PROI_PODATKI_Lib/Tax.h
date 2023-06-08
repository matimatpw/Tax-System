#pragma once
class Tax
{
    double income;
public:
    virtual double operator()(double inc) = 0;
};

// FIRMA-----
class Vat : public Tax {
public:
    double operator()(double inc);
    // double inComeWithVat =  Vat(income)
    /*double calculate_tax(double inc);*/
};

class Cit : public Tax {
public:
    double operator()(double inc);
};


// Osoba FIzyczna-----
class Pit : public Tax {
public:
    double operator()(double inc);
};

class Pon : public Tax {
public:
    double operator()(double inc);
};


//FIrma i Osoba Fizyczna
class Zus : public Tax {
public:
    double operator()(double inc);
};