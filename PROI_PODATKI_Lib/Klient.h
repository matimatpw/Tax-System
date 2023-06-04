#pragma once
#include <vector>
#include "IncomeLib.h"
#include <string>

enum podatkiOsoby
{
	pit,
	pon,
	zusOsoba,
};

enum podatkiFirma
{
	vat,
	cit,
	zusFirma
};

class Klient
{
protected:
	std::string nazwa;
	size_t ID;
	std::vector<Income> wplywy;
public:
	virtual ~Klient() = 0;
	size_t getID() const noexcept;
	std::string getNazwa() const noexcept;
	const std::vector<Income>& getWplywy() const;
	void dodajWplyw(Income const& nowy_wplyw);
	double wyliczKwotePodatku() const;

	void markPaid(size_t searchID);
	bool hasIncome(size_t searchID);
};

class Osoba : public Klient
{
private:
	static std::vector<Tax*> podatki_osoby;

public:
	Osoba(size_t id,std::string nazwa, std::vector<Income> wplywy_osoby);
	const std::vector<Tax*>& getPodatkiOsoba() const;
};


class Firma : public Klient
{
private:
	 static std::vector<Tax*> podatki_firmy;

public:
	Firma(size_t id, std::string nazwa, std::vector<Income> wplywy_firmy);
	const std::vector<Tax*>& getPodatkiFirma() const;
};

