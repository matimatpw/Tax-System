#include "Klient.h"

unsigned int Klient::getID() const noexcept
{
	return ID;
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

const std::vector<Podatek>& Osoba::getPodatkiOsoba() const
{
	return podatki_osoby;
}

const std::vector<Podatek>& Firma::getPodatkiFirma() const
{
	return podatki_firmy;
}
