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

//class IOClient {
//public:
//	virtual void displayInfo(std::ostream& os)const =0;
//};

class Client /*: public IOClient*/
{
protected:
	std::string name;
	size_t ID;
	static std::vector<size_t> ID_base;
	std::vector<Income> Incomes{};
public:
	size_t getID() const noexcept;
	std::string getName() const noexcept;
	std::vector<Income> getIncomes() const;
	bool isInIDBase(size_t id) const noexcept;
	void addIncome(Income const& nowy_wplyw);
	double calculateTaxAmount() const;

	void markPaid(size_t searchID);
	bool hasIncome(size_t searchID);

	/*void displayInfo(std::ostream& os) const;*/
	
	//friend std::ostream& operator<<(std::ostream& os, const Client& my_client);

	//std::ostream& readIncome(std::ostream& os);
};

class Person : public Client
{
private:
	static std::vector<Tax*> person_taxes; // Beda odgornie ustalane

public:
	Person(size_t id, std::string name, std::vector<Income> person_incomes = {});
	std::vector<Tax*> getPersonTaxes() const;
	//~Person();
	void displayInfo(std::ostream& os) const;
	
};


class Company : public Client
{
private:
	 static std::vector<Tax*> company_taxes;

public:
	Company(size_t id, std::string name, std::vector<Income> company_incomes = {});
	std::vector<Tax*> getCompanyTaxes() const;
	//~Company();
	void displayInfo(std::ostream& os) const;
};

