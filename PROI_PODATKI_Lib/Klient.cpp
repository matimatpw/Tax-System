#include "Klient.h"
#include <iostream>
#include <exception>

size_t Client::getID() const noexcept
{
	return ID;
}

std::string Client::getName() const noexcept
{
	return name;
}

std::vector<Income> Client::getIncomes() const
{
	return Incomes;
}

void Client::addIncome(const Income& new_income)
{
	Incomes.push_back(new_income);
}


double Client::calculateTaxAmount() const
{
	double sum = 0;
	for (auto& wplyw : Incomes)
	{
		sum += wplyw.toPay;
	}
	return sum;
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

Person::Person(size_t id, std::string name, std::vector<Income> wplywy_osoby)
{
	if (name.empty())
		throw std::runtime_error("Name cannot be empty");
	if (name.find_first_of("0123456789") != std::string::npos)
		throw std::runtime_error("There can't be any numbers in Person's name");
	this->name = name;
	this->ID = id;
	this->Incomes = wplywy_osoby;
}

std::vector<Tax*> Person::getPersonTaxes() const
{
	return person_taxes;
}

Company::Company(size_t id, std::string nazwa, std::vector<Income> wplywy_firmy)
{
	this->name = nazwa;
	this->ID = id;
	this->Incomes = wplywy_firmy;
}

std::vector<Tax*> Company::getCompanyTaxes() const
{
	return company_taxes;
}

std::vector<Tax*> Company::company_taxes = { new Vat, new Cit, new Zus};
std::vector<Tax*> Person::person_taxes = { new Pit, new Pon, new Zus };