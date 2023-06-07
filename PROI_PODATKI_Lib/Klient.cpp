#include "Klient.h"

size_t Client::getID() const noexcept
{
	return ID;
}

std::string Client::getName() const noexcept
{
	return name;
}

const std::vector<Income>& Client::getIncomes() const
{
	return Incomes;
}

void Client::addIncome(const Income& nowy_wplyw)
{
	Incomes.push_back(nowy_wplyw);
}


double Client::calculateTaxAmount() const
{
	double lacznaKwota = 0;
	for (auto& wplyw : Incomes)
	{
		lacznaKwota += wplyw.toPay;
	}
	return lacznaKwota;
}

void Client::markPaid(size_t searchID)
{
	for (Income& income : Incomes)
	{
		if (income.id == searchID)
		{
			income.paid = true;
			break;
		}
	}
}

bool Client::hasIncome(size_t searchID)
{
	for (Income& income : Incomes)
	{
		if (income.id == searchID)
		{
			return true;
		}
	}
}

Person::Person(size_t id, std::string nazwa, std::vector<Income> wplywy_osoby)
{
	this->name = nazwa;
	this->ID = id;
	this->Incomes = wplywy_osoby;
}

const std::vector<Tax*>& Person::getPersonTaxes() const
{
	return person_taxes;
}

Company::Company(size_t id, std::string nazwa, std::vector<Income> wplywy_firmy)
{
	this->name = nazwa;
	this->ID = id;
	this->Incomes = wplywy_firmy;
}

const std::vector<Tax*>& Company::getCompanyTaxes() const
{
	return company_taxes;
}

std::vector<Tax*> Company::company_taxes = { new Vat, new Cit, new Zus};
std::vector<Tax*> Person::person_taxes = { new Pit, new Pon, new Zus };