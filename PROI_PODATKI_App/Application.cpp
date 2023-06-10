#include "../PROI_PODATKI_Lib/TaxSystemLib.h"
#include "SavingJson.h"
#include <iostream>
#include <sstream>
#include <string>
void displayClientInfo(Client& my_client) {

}
std::unique_ptr<Client> createClient(int my_choice, size_t& index_XD) {
	std::string name;
	if (my_choice == 1) {
		std::cout << "Wprowadz Imie i Nazwisko\n> ";
		std::getline(std::cin, name);
		std::unique_ptr<Client> client = std::make_unique<Person>(index_XD, name);		
		index_XD++;
		return client;
	}
	else if (my_choice == 2) {
		std::cout << "Wprowadz nazwe Firmy\n> ";
		std::getline(std::cin, name);
		std::unique_ptr<Client> client = std::make_unique<Company>(index_XD, name);
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
	system.addClient(a);



	do {
		is_valid = false;
		size_t my_id;
		int choice = 0;
		std::cout << "Hi, what would you like to do today? Choose one of the options below: \n";
		std::cout << "1 -> Add Client \n";
		std::cout << "2 -> Remove Client \n";//by ID
		std::cout << "3 -> Add Income \n";
		std::cout << "4 -> Search Client \n";//by (income or client) ID
		std::cout << "> ";
		std::cin >> choice;

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
				
				std::cout << "Jeszczenie zrobione";//TODO  funkcja addIncome , nwm jak podawac tax.?
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
					Client client = findClient(choice, my_id, system);
					is_valid = true;
					std::cout << client;

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