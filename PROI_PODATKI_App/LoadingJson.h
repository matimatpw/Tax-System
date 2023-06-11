#pragma once
#include "../single_include/nlohmann/json.hpp"
#include "../PROI_PODATKI_Lib/TaxSystemLib.h"
#include <fstream>
#include <iostream>


using ordered_json = nlohmann::ordered_json;
using namespace nlohmann;

std::map<std::string, personTaxes> osobyMap = {
    {"pit", personTaxes::pit},
    {"pon", personTaxes::pon},
    {"zusOsoba", personTaxes::zusOsoba}
};

std::map<std::string, companyTaxes> firmaMap = {
    {"vat", companyTaxes::vat},
    {"cit", companyTaxes::cit},
    {"zusFirma", companyTaxes::zusFirma}
};

void loadFromJson(std::string filename, std::vector<Client*>& client_base) {
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
            Person newClient(clientID, clientName, {});
            const auto& clientIncomes = clientInfo["info"]["Client_Incomes"];
            for (const auto& incomeEntry : clientIncomes.items()) {

                size_t incomeId = std::stoull(incomeEntry.key());
                const auto& incomeInfo = incomeEntry.value();

                double amount = incomeInfo["amount"];
                std::string taxType = incomeInfo["tax"];
                personTaxes taxEnum = osobyMap[taxType];

                Income newIncome(amount, newClient.getPersonTaxes()[taxEnum], incomeId);
                newClient.addIncome(newIncome);

            }
            client_base.push_back(&newClient);
        }
        else if (clientType == "firma") {
            Company newClient(clientID, clientName, {});
            const auto& clientIncomes = clientInfo["info"]["Client_Incomes"];
            for (const auto& incomeEntry : clientIncomes.items()) {

                size_t incomeId = std::stoull(incomeEntry.key());
                const auto& incomeInfo = incomeEntry.value();

                double amount = incomeInfo["amount"];
                std::string taxType = incomeInfo["tax"];
                companyTaxes taxEnum = firmaMap[taxType];

                Income newIncome(amount, newClient.getCompanyTaxes()[taxEnum], incomeId);
                newClient.addIncome(newIncome);

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
