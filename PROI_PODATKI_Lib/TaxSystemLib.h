#pragma once
#include "IncomeLib.h"

template <typename Tax, typename Client>
class TaxSystem
{
private:
	std::vector<Client> clients;
public:
	TaxSystem();
	TaxSystem(std::string path_to_file);
	TaxSystem(std::vector<Client> existing);
	addIncome(std::string clientID, int amount, Tax tax);
	Client& searchByIncome(std::string incomeID);
	Client& searchByClientID(std::string ClientID);

	void deleteClientByID(std::string clientID);
	void addClient(std::string newClientID);

	int calculateAllTaxes();
};

