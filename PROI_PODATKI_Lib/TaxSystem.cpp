#include "TaxSystemLib.h"	
#include <stdexcept>


template<typename Tax, typename Client>
TaxSystem<Tax, Client>::TaxSystem()
{
}

template<typename Tax, typename Client>
TaxSystem<Tax, Client>::~TaxSystem()
{
}

template<typename Tax, typename Client>
TaxSystem<Tax, Client>::TaxSystem(std::string path_to_file)
{
}

template<typename Tax, typename Client>
void TaxSystem<Tax, Client>::addIncome(std::string clientID, int amount, Tax tax)
{
	Client client = searchByClientID(clientID);
	client.addIncome(amount, tax, currentIncomeID);
	currentIncomeID++;
}

template<typename Tax, typename Client>
Client& TaxSystem<Tax, Client>::searchByIncome(size_t searchID)
{
	if (searchID > currentIncomeID)
		throw std::runtime_error("No income of given ID");
	for (Client client : clients)
		for (Income income : client.incomes)
			if (income.id == searchID)
				return client;
}

template<typename Tax, typename Client>
Client& TaxSystem<Tax, Client>::searchByClientID(size_t searchID)
{
	auto place = std::find_if(clients.begin(), clients.end(), [searchID](Client& client) {
		return searchID == client.id;
		});
	if (place == clients.end())
		throw std::runtime_error("No client of given ID");
}

template<typename Tax, typename Client>
void TaxSystem<Tax, Client>::deleteClientByID(size_t searchID)
{
	auto place = std::find_if(clients.begin(), clients.end(), [searchID](Client& client) {
		return searchID == client.id;
		});
	if (place != clients.end())
		clients.erase(place);
	else
		throw std::runtime_error("Client of given ID doesnt exist");
}

template<typename Tax, typename Client>
void TaxSystem<Tax, Client>::addClient(const Client& newClient)
{
	clients.push_back(newClient);
}

template<typename Tax, typename Client>
int TaxSystem<Tax, Client>::calculateAllTaxes()
{
	int sum = 0;
	for (Client client : clients)
		sum += client.calculateAllTaxes();
	return sum;
}

