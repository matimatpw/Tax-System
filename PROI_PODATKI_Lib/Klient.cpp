#include "Klient.h"

size_t Klient::getID() const noexcept
{
	return ID;
}

const std::vector<Income>& Klient::getWplywy() const
{
	return wplywy;
}

//void Klient::setID(size_t new_id)
//{
//	// TODO zaimplementowac opcje ktora sprawdza czy dane id nie znajduje sie juz w bazie
//	this->ID = new_id; // TBH, idk czy jest sens zmieniac id klienta
//}

void Klient::dodajWplyw(const Income& nowy_wplyw)
{
	wplywy.push_back(nowy_wplyw);
}


double Klient::wyliczKwotePodatku() const
{
	double lacznaKwota = 0;
	for (Income wplyw : wplywy)
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
}

Osoba::Osoba(size_t id, std::vector<Income> wplywy_osoby)
{
	this->ID = id;
	this->wplywy = wplywy_osoby;
}

const std::vector<Tax*>& Osoba::getPodatkiOsoba() const
{
	return podatki_osoby;
}

Firma::Firma(size_t id, std::vector<Income> wplywy_firmy)
{
	this->ID = id;
	this->wplywy = wplywy_firmy;
}

const std::vector<Tax*>& Firma::getPodatkiFirma() const
{
	return podatki_firmy;
}

std::vector<Tax*> Firma::podatki_firmy = { new Vat, new Cit, new Zus};
std::vector<Tax*> Osoba::podatki_osoby = { new Pit, new Pon, new Zus };