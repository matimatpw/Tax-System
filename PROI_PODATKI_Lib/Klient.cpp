#include "Klient.h"
std::vector<Tax*> Firma::podatki_firmy = { new Vat, new Cit, new Zus };
std::vector<Tax*> Osoba::podatki_osoby = { new Pit, new Pon, new Zus };


Klient::~Klient()
{
}

size_t Klient::getID() const noexcept
{
	return ID;
}

std::string Klient::getNazwa() const noexcept
{
	return nazwa;
}

const std::vector<Income>& Klient::getWplywy() const
{
	return wplywy;
}

void Klient::dodajWplyw(const Income& nowy_wplyw)
{
	wplywy.push_back(nowy_wplyw);
}


double Klient::wyliczKwotePodatku() const
{
	double lacznaKwota = 0;
	for (auto& wplyw : wplywy)
	{
		lacznaKwota += wplyw.toPay;
	}
	return lacznaKwota;
}

void Klient::markPaid(size_t searchID)
{
	for (Income& income : wplywy)
	{
		if (income.id == searchID)
		{
			income.paid = true;
			break;
		}
	}
}


bool Klient::hasIncome(size_t searchID)
{
	for (Income& income : wplywy)
	{
		if (income.id == searchID)
		{
			return true;
		}
	}
	return false;
}

Osoba::Osoba(size_t id, std::string nazwa, std::vector<Income> wplywy_osoby)
{
	this->nazwa = nazwa;
	this->ID = id;
	this->wplywy = wplywy_osoby;
}

const std::vector<Tax*>& Osoba::getPodatkiOsoba() const
{
	return podatki_osoby;
}

Firma::Firma(size_t id, std::string nazwa, std::vector<Income> wplywy_firmy)
{
	this->nazwa = nazwa;
	this->ID = id;
	this->wplywy = wplywy_firmy;
}

const std::vector<Tax*>& Firma::getPodatkiFirma() const
{
	return podatki_firmy;
}

