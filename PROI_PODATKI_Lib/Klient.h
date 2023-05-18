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
	void setID(unsigned int new_id);
	void dodajWplyw(Wplyw const& nowy_wplyw);
	double wyliczKwotePodatku() const;
};

class Osoba : public Klient
{
private:
	std::vector<Podatek> podatki_osoby;

public:
	const std::vector<Podatek>& getPodatkiOsoba() const;
};


class Firma : public Klient
{
private:
	std::vector<Podatek> podatki_firmy;

public:
	const std::vector<Podatek>& getPodatkiFirma() const;
};
