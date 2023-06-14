#pragma once
#include <string>
#include "Klient.h"

class TaxSystem
{
private:
	std::vector<Client*> clients;
	size_t current_income_ID = 0;
public:
	TaxSystem();
	~TaxSystem();

	void addIncome(size_t clientID, double amount, Tax* tax);
	Client& searchByIncome(size_t searchID);
	void markPaid(size_t searchID);
	
	std::vector<Client*> get_clients_base() const noexcept;

	Client& searchByClientID(size_t searchID);
	void deleteClientByID(size_t searchID);
	void addClient(Client* newClient);

	void writeToFile(std::string path_to_file) const noexcept;

	double calculateAllTaxes();
};


