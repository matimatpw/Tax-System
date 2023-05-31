#pragma once
class Tax
{
    float income;
public:
    virtual float calculate_tax(float inc) = 0;
};

// FIRMA-----
class Vat : public Tax {

public:
    float calculate_tax(float inc);
};

class Cit : public Tax {
    float calculate_tax(float inc);
};


// Osoba FIzyczna-----
class Pit : public Tax {
    float calculate_tax(float inc);
};

class Pon : public Tax { //Podatek Od Nieruchomosci
    float calculate_tax(float inc);
};


//FIrma i Osoba Fizyczna
class Zus : public Tax {
    float calculate_tax(float inc);
};