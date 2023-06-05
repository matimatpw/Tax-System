#pragma once
#include "../single_include/nlohmann/json.hpp"
#include "../PROI_PODATKI_Lib/TaxSystemLib.h"
#include <fstream>
#include <iostream>


using ordered_json = nlohmann::ordered_json;
using namespace nlohmann;

std::map<std::string, podatkiOsoby> osobyMap = {
    {"pit", podatkiOsoby::pit},
    {"pon", podatkiOsoby::pon},
    {"zusOsoba", podatkiOsoby::zusOsoba}
};

std::map<std::string, podatkiFirma> firmaMap = {
    {"vat", podatkiFirma::vat},
    {"cit", podatkiFirma::cit},
    {"zusFirma", podatkiFirma::zusFirma}
};

void loadFromJson(std::string filename, std::vector<Klient*>& client_base) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Can't open json source file");
    json source = json::parse(file);

    size_t counter = 0;
    for (const auto& clientEntry : source["Client_ID"].items())
    {
        counter++;
        size_t clientID = std::stoull(clientEntry.key());
        const auto& clientInfo = clientEntry.value();

        std::string clientType = clientInfo["info"]["client_type"];
        std::string clientName = clientInfo["info"]["Client_Name"];

        if (clientType == "osoba") {
            Osoba newClient(clientID, clientName, {});
            const auto& clientIncomes = clientInfo["info"]["Client_Incomes"];
            for (const auto& incomeEntry : clientIncomes.items()) {

                size_t incomeId = std::stoull(incomeEntry.key());
                const auto& incomeInfo = incomeEntry.value();

                double amount = incomeInfo["amount"];
                std::string taxType = incomeInfo["tax"];
                podatkiOsoby taxEnum = osobyMap[taxType];

                Income newIncome(amount, newClient.getPodatkiOsoba()[taxEnum], incomeId);
                newClient.dodajWplyw(newIncome);

            }
            client_base.push_back(&newClient);
        }
        else if (clientType == "firma") {
            Firma newClient(clientID, clientName, {});
            const auto& clientIncomes = clientInfo["info"]["Client_Incomes"];
            for (const auto& incomeEntry : clientIncomes.items()) {

                size_t incomeId = std::stoull(incomeEntry.key());
                const auto& incomeInfo = incomeEntry.value();

                double amount = incomeInfo["amount"];
                std::string taxType = incomeInfo["tax"];
                podatkiFirma taxEnum = firmaMap[taxType];

                Income newIncome(amount, newClient.getPodatkiFirma()[taxEnum], incomeId);
                newClient.dodajWplyw(newIncome);

            }
            client_base.push_back(&newClient);
        }
        else
            throw std::runtime_error("Error reading from file: wrong client type");

    }

    if (counter == client_base.size())
    {
        std::cout << "Loaded from json file succesfully" << std::endl;
    }
    else
    {
        throw std::runtime_error("Error reading from json file: unknown error");
    }
}
