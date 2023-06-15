#include "Klient.h"
#include <iostream>
#include <exception>


std::vector<size_t> Client::ID_base = {};

std::vector<Tax*> Company::company_taxes = {};
std::vector<Tax*> Person::person_taxes = {};

size_t Company::companyCounter = 0;
size_t Person::personCounter = 0;

size_t Client::getID() const noexcept
{
	return ID;
}

std::string Client::getName() const noexcept
{
	return name;
}

bool Client::isInIDBase(size_t id) const noexcept
{
	for (auto& base_id : ID_base)
	{
		if (base_id == id)
			return true;
	}
	return false;
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
	for (auto& income : Incomes)
	{
		if (!(income.paid))
			sum += income.toPay;
	}
	return sum;
}

void Client::markPaid(size_t searchID)
{
	for (Income& income : Incomes)
	{
		if (income.id == searchID)
		{
			if (!income.paid)
			{
				income.paid = true;
				break;
			}
			else
				throw std::runtime_error("Tax already paid");
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
	return false;
}

//void Client::displayInfo(std::ostream& os) const
//{
//	
//}

//std::ostream& Client::readIncome(std::ostream& os)
//{
//	return os;
//}

Person::Person(size_t id, std::string name, std::vector<Income> wplywy_osoby)
{
	if (name.empty())
		throw std::runtime_error("Name cannot be empty");
	if (name.find_first_of("0123456789") != std::string::npos)
		throw std::runtime_error("There can't be any numbers in Person's name");
	this->name = name;
	this->ID = id;
	this->Incomes = wplywy_osoby;

	if (!(personCounter++))
	{
		Person::initTaxes();
	}
}

std::vector<Tax*> Person::getTaxes()
{
	return person_taxes;
}

void Person::initTaxes()
{
	person_taxes = { new Pit, new Pon, new Zus };
}

void Person::destroyTaxes()
{
	for (Tax* tax : person_taxes)
		delete tax;
	person_taxes.clear();
}

void Person::displayInfo(std::ostream& os) const
{
	os << "Imie i Nazwisko >" << this->getName() << "\n";
	os << "ID >" << this->getID() << "\n";
	os << "Income info :" << "\n";
}

Client::~Client() = default;

Person::~Person()
{
	if (!(--personCounter))
	{
		Person::destroyTaxes();
	}
}

Company::Company(size_t id, std::string name, std::vector<Income> wplywy_firmy)
{
	if (name.empty())
		throw std::runtime_error("Name cannot be empty");
	this->name = name;
	this->ID = id;
	/*ID_base.push_back(id);*/
	this->Incomes = wplywy_firmy;

	if (!(companyCounter++))
	{
		Company::initTaxes();
	}
}

std::vector<Tax*> Company::getTaxes()
{
	return company_taxes;
}

void Company::initTaxes()
{
	company_taxes = { new Vat, new Cit, new Zus };
}

void Company::destroyTaxes()
{
	for (Tax* tax : company_taxes)
		delete tax;
	company_taxes.clear();
}

Company::~Company()
{
	if (!(--companyCounter))
	{
		Company::destroyTaxes();
	}
}

void Company::displayInfo(std::ostream& os) const
{
	os << "Nazwa Firmy >" << this->getName() << "\n";
	os << "ID >" << this->getID() << "\n";
	os << "Income info :" << "\n";
}


//std::ostream& operator<<(std::ostream& os, const Client& my_client)
//{
//	my_client.displayInfo(os);
//	return os;
//}
