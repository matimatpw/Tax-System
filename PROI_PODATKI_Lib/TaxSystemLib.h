#pragma once
#include <string>
#include <vector>
#include "IncomeLib.h"

template <typename Tax, typename Client>
class TaxSystem
{
private:
	size_t currentIncomeID = 0;
	std::vector<Client> clients;
public:
	TaxSystem();
	~TaxSystem();
	TaxSystem(std::string path_to_file);
	void addIncome(std::string clientID, int amount, Tax tax);
	Client& searchByIncome(size_t searchID);
	Client& searchByClientID(size_t searchID);

	void deleteClientByID(size_t searchID);
	void addClient(const Client& newClient);

	int calculateAllTaxes();
};


