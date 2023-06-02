#include "../PROI_PODATKI_Lib/TaxSystemLib.h"
#include "SavingJson.h"
#include <iostream>


int main()
{
	return 0;
}

 // u¿ywane wczeœniej do testowania zapisu do pliku JSON
/*
Tax* taxes_ptr = nullptr;
Vat vat;
taxes_ptr = &vat;
Income wplyw1(1500, taxes_ptr, 5000);
Pit pit;
taxes_ptr = &pit;
//Income wplyw2(5500, taxes_ptr, 5001);

std::vector<Income> wplywy_Marka = { wplyw1, wplyw2 };
std::vector<Income> wplywy_Darka = { wplyw1 };
std::vector<Income> wplywy_Eugeniusza = { wplyw2 };

Osoba Marek(10001, "Marek Brzozowski", wplywy_Marka);
Osoba Darek(5001, "Darek Nowak", wplywy_Darka);
Osoba Eugeniusz(6005, "Eugeniusz Dabrowski", wplywy_Eugeniusza);

std::vector<Klient> clients;
clients.push_back(Marek);
clients.push_back(Darek);
clients.push_back(Eugeniusz);

saveToJson("results.txt", clients); */