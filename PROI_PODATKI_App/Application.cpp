#include "../PROI_PODATKI_Lib/TaxSystemLib.h"
#include "SavingJson.h"
#include <iostream>
#include <sstream>
#include <string>
std::ostream& displayClientInfo(std::ostream& os, Client& my_client) {
	os << "Nazwa >" << my_client.getName() << "\n";
	os << "ID >" << my_client.getID() << "\n";
	os << "Income info :" << "\n";
	
	int i = 0;
	int MAX_ITER = 3;
	for (auto& income : my_client.getIncomes()){
		os << ">ID - " << income.id << "\n";
		os << ">Amount - " << income.amount << "\n";
		os << ">Tax - " << income.toPay <<"\n";
		os << ">Is tax paid - ";
		os << ((income.paid) ? "Yes\n" : "No\n");
		os << std::endl;
	}
	os << "Full Tax> " << my_client.calculateTaxAmount() << "\n";

	return os;
}

Client createClient(int my_choice, size_t& index_XD) {
	std::string name;
	if (my_choice == 1) {
		std::cout << "Wprowadz Imie i Nazwisko\n> ";
		std::getline(std::cin, name);
		Person client(size_t(index_XD),name, {});
		//test---
		
		//---
		index_XD++;
		return client;
	}
	else if (my_choice == 2) {
		std::cout << "Wprowadz nazwe Firmy\n> ";
		std::getline(std::cin, name);
		Company client(size_t(index_XD),name, {});
		index_XD++;
		return client;
	}
	else {
		throw std::invalid_argument("Wrong number\n");
	}

}

Client findClient(int my_choice, size_t id, TaxSystem& my_system) {
	if (my_choice == 1) {
		return my_system.searchByIncome(id);
	}
	else if (my_choice == 2) {
		return my_system.searchByClientID(id);
	}
	else {
		throw std::invalid_argument("Wrong number\n");
	}
}
//TODO ID klienta trzeba automatycznie jakos ustawiac np. incermentacja

void print_output() {
	std::cout << "Done :)\n";
	//for (int i = 0; i < 100; i++)
	//	std::cout << "-";
	std::cout << std::endl;
}

int main()
{
	size_t my_idx = 0;
	TaxSystem system;
	bool is_valid;

	//here for tersting
	Person a(69, "xd", {});
	//Income new_inc(500, a.getPersonTaxes()[cit], 20);
	//a.addIncome(new_inc);
	system.addClient(a);

	Company b(70, "company", {});
	Income new_inc2(600, b.getCompanyTaxes()[cit], 30);
	Income new_inc3(600, b.getCompanyTaxes()[cit], 31);
	//system.addIncome(new_inc3);
	system.addClient(b);

	system.addIncome(69, 101, a.getPersonTaxes()[pit]);

	system.addIncome(70, 202, b.getCompanyTaxes()[cit]);
	system.addIncome(70, 303, b.getCompanyTaxes()[cit]);
	//-----



	do {
		is_valid = false;
		size_t my_id;
		int choice = 0;
		//TODO ------------------------------------------------------------------------------
		std::cout << "Hi, what would you like to do today? Choose one of the options below: \n";
		std::cout << "1 -> Add Client \n";
		std::cout << "2 -> Remove Client \n";//by ID
		std::cout << "3 -> Add Income \n";
		std::cout << "4 -> Search Client \n";//by (income or client) ID
		std::cout << "> ";
		std::cin >> choice;
		//TODO ------------------------------------------------------------------------------
		switch (choice)
		{
		case 1:
		{
			while(!is_valid)
			{

				std::cout << "Firma czy Osoba?: \n";
				std::cout << "1-> Osoba\n";
				std::cout << "2-> Firma\n> ";
				std::cin >> choice;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore newline

				
				try {
					Client client = createClient(choice, my_idx);
					system.addClient(client);
					is_valid = true;

				}
				catch (std::invalid_argument e) {
					std::cout << e.what() << std::endl;
				}
			}
			print_output();
			break;
		}
		case 2:
		{
			while (!is_valid) {
				std::cout << "Wprowadz ID Klienta:\n> ";
				std::cin >> choice;
				try {
					system.deleteClientByID(size_t(choice));
					is_valid = true;
				}
				catch (std::runtime_error e) {
					std::cout << e.what() << std::endl;
				}
			}
			print_output();
			break;
		}
		case 3:
		{
			while (!is_valid) {
				
				std::cout << "Wprowadz ID klienta: \n> ";//TODO  funkcja addIncome , nwm jak podawac tax.?
				std::cin >> my_id;
				is_valid = true;
			}
			print_output();
			break;
		}
		case 4: 
		{
			while (!is_valid) {
				std::cout << "Po czym chcesz wyszukac klienta?:\n";
				std::cout << "1-> ID wplywu\n";
				std::cout << "2-> ID klienta\n";
				std::cout << "Wybierz opcje:\n> ";
				std::cin >> choice;
				std::cout << "Wprowadz ID:\n> ";
				std::cin >> my_id;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore newline
				try {
					Client client = findClient(choice, my_id, system);//tutaj
					is_valid = true;
					displayClientInfo(std::cout, client);
				}
				catch (std::runtime_error r) {
					std::cout << r.what() << std::endl;
				}
				catch (std::invalid_argument e) {
					std::cout << e.what() << std::endl;
				}
			}
			print_output();
			break;
		}

		
		default:
			std::cout << "> Niepoprawna opcja! <\n";
		}
		// Taxsystem X
		// 
		// 
		// 
		// 
		// 
		// 
		// 
		//addclimt
		//taxsyte
	} while (true);
	return 0;
};