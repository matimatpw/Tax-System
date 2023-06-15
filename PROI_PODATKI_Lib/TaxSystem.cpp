#include "TaxSystemLib.h"	
#include <stdexcept>
#include <iostream>


 
TaxSystem::TaxSystem()
{
}

 
TaxSystem::~TaxSystem()
{
	for (Client* client : clients)
		delete client;
}


void TaxSystem::addIncome(size_t clientID, double amount, Tax* tax)
{
	Client* client = searchByClientID(clientID);
	Income newIncome = Income(amount, tax, current_income_ID);
	client->addIncome(newIncome);
	current_income_ID++;
}
 
Client* TaxSystem::searchByIncome(size_t searchID)
{
	for (Client* client : clients)
		if (client->hasIncome(searchID))
			return client;
	throw std::runtime_error("No income of given ID");
}

void TaxSystem::markPaid(size_t searchID)
{
	Client* toMark = searchByIncome(searchID);
	toMark->markPaid(searchID);
}

 
Client* TaxSystem::searchByClientID(size_t searchID)
{
	auto place = std::find_if(clients.begin(), clients.end(), [searchID](Client* client) {return searchID == client->getID();});
	if (place == clients.end())
		throw std::runtime_error("No client of given ID");
	else
		return (*place);
}

 
void TaxSystem::deleteClientByID(size_t searchID)
{
	auto place = std::find_if(clients.begin(), clients.end(), [searchID](Client* client) {return searchID == client->getID();});
	if (place != clients.end()) {
		auto temp = *place;
		clients.erase(place);
		delete temp;
	}
	else
		throw std::runtime_error("Client of given ID doesnt exist");
}

 
void TaxSystem::addClient(Client* newClient)
{
	size_t clientID = newClient->getID();
	std::cout << clientID << std::endl;
	try {
		Client * client = searchByClientID(clientID);
		throw std::invalid_argument("Client of given ID already exists");
	}
	catch (std::runtime_error e) {
		clients.push_back(newClient);
	}
}


std::vector<Client*> TaxSystem::get_clients_base() const noexcept
{
	return clients;
}
 
double TaxSystem::calculateAllTaxes()
{
	double sum = 0;
	for (Client* client : clients)
		sum += (*client).calculateTaxAmount();
	return sum;
}

