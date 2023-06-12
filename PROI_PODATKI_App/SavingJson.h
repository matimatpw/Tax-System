#pragma once
#include "../PROI_PODATKI_Lib/TaxSystemLib.h"
#include <fstream>
#include <iostream>
#include "../single_include/nlohmann/json.hpp"


using ordered_json = nlohmann::ordered_json;

std::string getTaxName(Income income) {
	Tax* tax = income.tax;
	
	Pit* pit = dynamic_cast<Pit*>(tax);
	Vat* vat = dynamic_cast<Vat*>(tax);
	Pon* pon = dynamic_cast<Pon*>(tax);
	Cit* cit = dynamic_cast<Cit*>(tax);
	Zus* zus = dynamic_cast<Zus*>(tax);

	return pit ? "pit" : vat ? "vat" : pon ? "pon" : cit ? "cit" : zus ? "zus" : "unknown";
}

void saveToJson(std::string filename, std::vector<Client*> client_base) {
    ordered_json data_to_save;

    for (Client* client : client_base) {
        std::vector<Income> client_incomes = client->getIncomes();

        ordered_json client_info;

		client_info["info"]["client_type"] = dynamic_cast<Person*>(client) ? "osoba" : "firma";
		client_info["info"]["Client_Name"] = client->getName();

		if (client->getIncomes().size() == 0)
			continue;

		for (Income current_income : client_incomes)
		{
			client_info["info"]["Client_Incomes"][std::to_string(current_income.id)]["amount"] = current_income.amount;
			client_info["info"]["Client_Incomes"][std::to_string(current_income.id)]["tax"] = getTaxName(current_income);
			client_info["info"]["Client_Incomes"][std::to_string(current_income.id)]["paid"] = current_income.paid;
		}

		data_to_save["Client_ID"][std::to_string(client->getID())] = client_info;
    }

	std::ofstream file(filename);

	if (file.is_open())
	{
		file << std::setw(4) << data_to_save << std::endl;
		std::cout << "Data saved to file: " + filename << std::endl;
	}
	else 
	{
		std::cout << "Can't open file." << std::endl;
	}


}