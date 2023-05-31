#pragma once
#include <vector>
// #include <Wplyw.h>

class Podatek;
class Wplyw;

class Klient
{
protected:
	unsigned int ID;
	std::vector<Wplyw> wplywy;
public:
	unsigned int getID() const noexcept;
	const std::vector<Wplyw>& getWplywy() const;
	void setID(unsigned int new_id);
	void dodajWplyw(Wplyw const& nowy_wplyw);
	double wyliczKwotePodatku() const;
};

class Osoba : public Klient
{
private:
	std::vector<Podatek> podatki_osoby; // Beda odgornie ustalane

public:
	Osoba(unsigned int id, std::vector<Wplyw> wplywy_osoby);
	const std::vector<Podatek>& getPodatkiOsoba() const;
};


class Firma : public Klient
{
private:
	std::vector<Podatek> podatki_firmy;

public:
	Firma(unsigned int id, std::vector<Wplyw> wplywy_firmy);
	const std::vector<Podatek>& getPodatkiFirma() const;
};
