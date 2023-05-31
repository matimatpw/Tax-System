#include "Klient.h"

unsigned int Klient::getID() const noexcept
{
	return ID;
}

const std::vector<Wplyw>& Klient::getWplywy() const
{
	return wplywy;
}

void Klient::setID(unsigned int new_id)
{
	// TODO zaimplementowac opcje ktora sprawdza czy dane id nie znajduje sie juz w bazie
	this->ID = new_id;
}

void Klient::dodajWplyw(Wplyw const& nowy_wplyw)
{
	wplywy.push_back(nowy_wplyw);
}


double Klient::wyliczKwotePodatku() const
{
	double lacznaKwota = 0;
	for (auto wplyw : wplywy)
	{
		lacznaKwota += wplyw.ileDoZaplaty(); // TODO  zmienic to pozniej gdy zaimplementowany bedzie wplyw
	}
	return lacznaKwota;
}

Osoba::Osoba(unsigned int id, std::vector<Wplyw> wplywy_osoby)
{
	this->ID = id;
	this->wplywy = wplywy_osoby;
}

const std::vector<Podatek>& Osoba::getPodatkiOsoba() const
{
	return podatki_osoby;
}

Firma::Firma(unsigned int id, std::vector<Wplyw> wplywy_firmy)
{
	this->ID = id;
	this->wplywy = wplywy_firmy;
}

const std::vector<Podatek>& Firma::getPodatkiFirma() const
{
	return podatki_firmy;
}
