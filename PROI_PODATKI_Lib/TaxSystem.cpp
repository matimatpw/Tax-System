#include "TaxSystemLib.h"	
#include <stdexcept>


 
TaxSystem::TaxSystem()
{
}

 
TaxSystem::~TaxSystem()
{
}

 
TaxSystem::TaxSystem(std::string path_to_file)
{
}


void TaxSystem::addIncome(size_t clientID, double amount, Tax* tax)
{
	Klient client = searchByClientID(clientID);
	Income newIncome = Income(amount, tax, currentIncomeID);
	client.dodajWplyw(newIncome);
	currentIncomeID++;
}
 
Klient& TaxSystem::searchByIncome(size_t searchID)
{
	if (searchID > currentIncomeID)
		throw std::runtime_error("No income of given ID");
	for (Klient client : clients)
		if (client.hasIncome(searchID))
			return client;
}

void TaxSystem::markPaid(size_t searchID)
{
	Klient toMark = searchByIncome(searchID);
	toMark.markPaid(searchID);
}

 
Klient& TaxSystem::searchByClientID(size_t searchID)
{
	auto place = std::find_if(clients.begin(), clients.end(), [searchID](Klient& client) {
		return searchID == client.getID();
		});
	if (place == clients.end())
		throw std::runtime_error("No client of given ID");
}

 
void TaxSystem::deleteClientByID(size_t searchID)
{
	auto place = std::find_if(clients.begin(), clients.end(), [searchID](Klient& client) {
		return searchID == client.getID();
		});
	if (place != clients.end())
		clients.erase(place);
	else
		throw std::runtime_error("Client of given ID doesnt exist");
}

 
void TaxSystem::addClient(const Klient& newClient)
{
	clients.push_back(newClient);
}

void TaxSystem::writeToFile(std::string path_to_file) const noexcept
{
}

 
double TaxSystem::calculateAllTaxes()
{
	double sum = 0;
	for (Klient client : clients)
		sum += client.wyliczKwotePodatku();
	return sum;
}

