#pragma once
class Tax
{
public:
	virtual float calculate_tax();
};

// FIRMA-----
class Vat : public Tax {
public:
	float calculate_tax();
};

class Cit : public Tax {
	float calculate_tax();
};


// Osoba FIzyczna-----
class Pit : public Tax {
	float calculate_tax();
};

class Pon : public Tax { //Podatek Od Nieruchomosci
	float calculate_tax();
};


//FIrma i Osoba Fizyczna
class Zus : public Tax {
	float calculate_tax();
};

