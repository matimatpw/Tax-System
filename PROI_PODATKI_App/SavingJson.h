#pragma once
#include "../PROI_PODATKI_Lib/TaxSystemLib.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using ordered_json = nlohmann::ordered_json;

void saveToJson(std::string filename, std::vector<Klient>& client_base) {
    ordered_json data_to_save;

    for (auto const& client : client_base) {
        std::vector<Income> client_incomes = client.getWplywy();

        ordered_json client_info;

		client_info["info"]["Client_Name"] = client.getNazwa();

		for (int i = 0; i <= client_incomes.size() - 1; ++i)
		{
			Income current_income = client_incomes[i];
			client_info["info"]["Client_Incomes"][std::to_string(current_income.id)] = current_income.amount;
		}

		data_to_save["Client_ID"][std::to_string(client.getID())] = client_info;
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