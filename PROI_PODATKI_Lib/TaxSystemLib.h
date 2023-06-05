#pragma once
#include <string>
#include "Klient.h"

class TaxSystem
{
private:
	std::vector<Klient*> clients;
public:
	TaxSystem();
	~TaxSystem();
	TaxSystem(std::string path_to_file);

	void addIncome(size_t clientID, double amount, Tax* tax, size_t id);
	Klient* searchByIncome(size_t searchID);
	void markPaid(size_t searchID);
	
	Klient* searchByClientID(size_t searchID);
	void deleteClientByID(size_t searchID);
	void addClient(Klient* newClient);

	void writeToFile(std::string path_to_file) const noexcept;

	double calculateAllTaxes();
};


