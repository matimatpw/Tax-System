#pragma once
#include <string>
#include "Klient.h"

class TaxSystem
{
private:
	size_t currentIncomeID = 0;
	std::vector<Client> clients;
public:
	TaxSystem();
	~TaxSystem();
	TaxSystem(std::string path_to_file);

	void addIncome(size_t clientID, double amount, Tax* tax);
	Client& searchByIncome(size_t searchID);
	void markPaid(size_t searchID);
	
	Client& searchByClientID(size_t searchID);
	void deleteClientByID(size_t searchID);
	void addClient(const Client& newClient);

	void writeToFile(std::string path_to_file) const noexcept;

	double calculateAllTaxes();
};


