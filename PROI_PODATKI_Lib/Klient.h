#pragma once
#include <vector>
#include "IncomeLib.h"
#include <string>

enum personTaxes
{
	pit,
	pon,
	zusOsoba,
};

enum companyTaxes
{
	vat,
	cit,
	zusFirma
};

class Client
{
protected:
	std::string name;
	size_t ID;
	static std::vector<size_t> ID_base;
	std::vector<Income> Incomes{};
public:
	virtual ~Client() = 0;
	virtual std::vector<Tax*> getTaxes() = 0;
	size_t getID() const noexcept;
	std::string getName() const noexcept;
	std::vector<Income> getIncomes() const;
	void addIncome(Income const& nowy_wplyw);
	double calculateTaxAmount() const;

	void markPaid(size_t searchID);
	bool hasIncome(size_t searchID);
};

class Person : public Client
{
private:
	static std::vector<Tax*> person_taxes; // Odgornie ustalane
	static size_t personCounter;

public:
	Person(size_t id, std::string name, std::vector<Income> person_incomes = {});
	std::vector<Tax*> getTaxes();
	static void initTaxes();
	static void destroyTaxes();
	~Person();
	void displayInfo(std::ostream& os) const;
	
};


class Company : public Client
{
private:
	 static std::vector<Tax*> company_taxes;
	 static size_t companyCounter;

public:
	Company(size_t id, std::string name, std::vector<Income> company_incomes = {});
	std::vector<Tax*> getTaxes();
	static void initTaxes();
	static void destroyTaxes();
	~Company();
	void displayInfo(std::ostream& os) const;
};

