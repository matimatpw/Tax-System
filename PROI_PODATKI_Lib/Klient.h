#pragma once
#include <vector>
#include "IncomeLib.h"

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
	size_t ID;
	std::vector<Income> wplywy;
public:
	size_t getID() const noexcept;
	const std::vector<Income>& getWplywy() const;
	void setID(size_t new_id);
	void dodajWplyw(Income const& nowy_wplyw);
	double wyliczKwotePodatku() const;

	void markPaid(size_t searchID);
	bool hasIncome(size_t searchID);
};

class Osoba : public Klient
{
private:
	static std::vector<Tax*> podatki_osoby; // Beda odgornie ustalane

public:
	Osoba(size_t id, std::vector<Income> wplywy_osoby);
	const std::vector<Tax*>& getPodatkiOsoba() const;
};


class Firma : public Klient
{
private:
	 static std::vector<Tax*> podatki_firmy;

public:
	Firma(size_t id, std::vector<Income> wplywy_firmy);
	const std::vector<Tax*>& getPodatkiFirma() const;
};

