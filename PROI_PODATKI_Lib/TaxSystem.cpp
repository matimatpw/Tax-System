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
	Client& client = searchByClientID(clientID);
	Income newIncome = Income(amount, tax, currentIncomeID);
	client.addIncome(newIncome);
	currentIncomeID++;
}
 
Client& TaxSystem::searchByIncome(size_t searchID)
{
	if (searchID >= currentIncomeID)
		throw std::runtime_error("No income of given ID");
	for (Client& client : clients)
		if (client.hasIncome(searchID))
			return client;
}

void TaxSystem::markPaid(size_t searchID)
{
	Client& toMark = searchByIncome(searchID);
	toMark.markPaid(searchID);
}

 
Client& TaxSystem::searchByClientID(size_t searchID)
{
	auto place = std::find_if(clients.begin(), clients.end(), [searchID](Client& client) {
		return searchID == client.getID();
		});
	if (place == clients.end())
		throw std::runtime_error("No client of given ID");
	return (*place);
}

 
void TaxSystem::deleteClientByID(size_t searchID)
{
	auto place = std::find_if(clients.begin(), clients.end(), [searchID](Client& client) {
		return searchID == client.getID();
		});
	if (place != clients.end()) {
		
		clients.erase(place);
	}
	else
		throw std::runtime_error("Client of given ID doesnt exist");
}

 
void TaxSystem::addClient(const Client& newClient) noexcept
{
	clients.push_back(newClient);
}

void TaxSystem::writeToFile(std::string path_to_file) const noexcept
{
}

 
double TaxSystem::calculateAllTaxes()
{
	double sum = 0;
	for (Client& client : clients)
		sum += client.calculateTaxAmount();
	return sum;
}

