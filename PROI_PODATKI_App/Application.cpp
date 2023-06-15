#include "../PROI_PODATKI_Lib/TaxSystemLib.h"
#include "SavingJson.h"
#include "LoadingJson.h"
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

enum Events {
	NullEvent = 0,
	AddClient = 1,
	RemoveClient = 2,
	AddIncome = 3,
	SearchClient = 4,
	SaveToJson = 5,
	LoadFromJson = 6,
	PayTax = 7,
	Quit = 8
};


std::ostream& displayClientInfo(std::ostream& os, Client* my_client) {
	os << "Name - " << my_client->getName() << "\n";
	os << "ID - " << my_client->getID() << "\n";
	os << "Taxes to pay :\n";
	for (Tax* &tax : my_client->getTaxes()) {
		os << "> " << tax->getName() << "\n";
	}
	os << "Income info :" << "\n";
	
	int i = 0;
	int MAX_ITER = 3;
	for (auto& income : my_client->getIncomes()) {
		os << ">ID - " << income.id << "\n";
		os << ">Amount - " << income.amount << "\n";
		os << ">Tax (" << income.tax->getName() << ") - " << income.toPay << "\n";
		
		os << ">Is tax paid - ";
		os << ((income.paid) ? "Yes\n" : "No\n");
		os << std::endl;
		
	}
	os << "Full Tax> " << my_client->calculateTaxAmount() << "\n";

	return os;
}

Client* createClient(int my_choice, size_t& index_XD) {
	std::string name;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (my_choice == 1) {
		std::cout << "Insert Full Name\n> ";
		std::getline(std::cin, name);
		Person* client = new Person(size_t(index_XD),name, {});
		index_XD++;
		return client;
	}
	else if (my_choice == 2) {
		std::cout << "Insert Company Name\n> ";
		std::getline(std::cin, name);
		Company* client = new Company(size_t(index_XD),name, {});
		index_XD++;
		return client;
	}
	else {
		throw std::invalid_argument("Wrong number\n");
	}

}

Client* findClient(int my_choice, size_t id, TaxSystem& my_system) {
	if (my_choice == 1) {
		return (my_system.searchByIncome(id));
	}
	else if (my_choice == 2) {
		return (my_system.searchByClientID(id));
	}
	else {
		throw std::invalid_argument("Wrong number\n");
	}
}


void handleInputError(std::istream& stream) {
	if (stream.fail()) {
		stream.clear();
		stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::invalid_argument("Input Error!");
	}
}
void print_output() {
	std::cout << "\nDone :)\n";
	std::chrono::seconds timer(3);
	std::this_thread::sleep_for(timer);    //  czysczenie konsoli (czyszczenie 3 sekundy przed)
	system("CLS"); // windows
}

int main()
{	
	size_t my_idx = 0; //id of clients (incremented after each AddClient, decrement after each RemoveClient)
	TaxSystem system;
	bool is_valid;

	//here for tersting
	//Person a(69, "xd", {});
	////Income new_inc(500, a.getPersonTaxes()[cit], 20);
	////a.addIncome(new_inc);
	//system.addClient(&a);

	//Company b(70, "company", {});
	//Income new_inc2(600, b.getTaxes()[cit], 30);
	//Income new_inc3(600, b.getTaxes()[cit], 31);
	////system.addIncome(new_inc3);
	//system.addClient(&b);

	//system.addIncome(69, 101, a.getTaxes()[pit]);

	//system.addIncome(70, 202, b.getTaxes()[cit]);
	//system.addIncome(70, 303, b.getTaxes()[cit]);
	//-----

	bool run = true;

	do {
		std::cin.clear();
		is_valid = false;
		size_t my_id;
		int choice = 0;
		std::string input;
		//TODO ------------------------------------------------------------------------------
		std::cout << "Hi, what would you like to do today? Choose one of the options below: \n";
		std::cout << "1 -> Add Client \n";
		std::cout << "2 -> Remove Client \n";//by ID
		std::cout << "3 -> Add Income \n";
		std::cout << "4 -> Search Client \n";//by (income or client) ID
		std::cout << "5 -> Save Clients To Json File \n";
		std::cout << "6 -> Load Clients From Json File \n";
		std::cout << "7 -> Pay Tax From Income Of Given ID \n";
		std::cout << "8 ->Quit \n";
		std::cout << "> ";
		std::cin >> input;

		try {
			choice = std::stoi(input);
		}
		catch (const std::invalid_argument e) {
			std::cout << "Invalid input. Please enter a number." << std::endl;
			continue;
		}

		//TODO ------------------------------------------------------------------------------
		switch (choice)
		{
		case AddClient:
		{
			while (!is_valid)
			{


				try {
					std::cout << "Company or Person?: \n";
					std::cout << "1-> Person\n";
					std::cout << "2-> Company\n> ";
					std::cin >> choice;
					handleInputError(std::cin);
					Client* client = createClient(choice, my_idx);
					system.addClient(client);
					std::cout << "This client ID is: " << my_idx - 1 << "";
					is_valid = true;

				}
				catch (std::invalid_argument e) {
					std::cout << e.what() << " Input 1 or 2 please" << std::endl;
				}
				catch (std::runtime_error r) {
					std::cout << r.what() << std::endl;
				}
			}
			print_output();
			break;
		}
		case RemoveClient:
		{
			while (!is_valid) {
				std::cout << "Insert Client ID:\n> ";
				std::cin >> choice;
				try {
					handleInputError(std::cin);
					system.deleteClientByID(size_t(choice));
					is_valid = true;
				}
				catch (std::runtime_error e) {
					std::cout << e.what() << std::endl;
				}
				catch (std::invalid_argument e) {
					std::cout << e.what() << " ID contains only numbers!" << std::endl;
				}
			}
			print_output();
			break;
		}
		case AddIncome:
		{
			// Wskaznik na podatek przekazywany do konstruktora wplywu, nie tworza sie nowe obietky podatku, wiec nie trzeba ich usuwac
			double my_amount;
			while (!is_valid) {

				try {
					std::cout << "Insert Client ID: \n> ";
					std::cin >> my_id;
					handleInputError(std::cin);
					std::cout << "Insert income amount: \n> ";
					std::cin >> my_amount;
					handleInputError(std::cin);

					Client* my_client = findClient(2, my_id, system);
					std::vector<Tax*> taxes = my_client->getTaxes();
					
					std::cout << "What Tax would you like to include: \n";
					int i = 0;
					for (Tax* tax: taxes) {
						std::cout << ++i <<"-> " << tax->getName() << "\n";
					}
					std::cout << ">";
					std::cin >> choice;
					handleInputError(std::cin);

					system.addIncome(my_id, my_amount, taxes.at(choice - 1));
					
					
					is_valid = true;
				}
				catch (std::out_of_range o)
				{
					std::cout << o.what() << std::endl;
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
		case SearchClient:
		{
			
			std::cin.clear();
			while (!is_valid) {
				try {
					std::cout << "How do you choose a client!:\n";
					std::cout << "1-> Income ID \n";
					std::cout << "2-> Client ID \n";
					std::cout << "Choose option:\n> ";
					std::cin >> choice;
					handleInputError(std::cin);
					if (choice > 2 || choice < 1)
						throw std::invalid_argument("Wrong choice!");
					std::cout << "Insert ID:\n> ";
					std::cin >> my_id;
					handleInputError(std::cin);
					
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore newline
					Client* client = findClient(choice, my_id, system);//tutaj
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
			std::cin.get();
			print_output();
			
			break;
		}
		case SaveToJson:
		{
			while (!is_valid) {
				std::string filename{};
				std::cout << "Enter the name of the file to which you want to save the data:\n";
				std::cin >> filename;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore newline
				try {
					
					saveToJson(filename, system.get_clients_base());
					is_valid = true;
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
		case LoadFromJson:
		{
			// load clients from json file
			while (!is_valid) {
				std::string filename{};
				std::cout << "Enter the name of the file from which you want to load the data:\n>";
				std::cin >> filename;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore newline
				try {

					loadFromJson(filename, system);

					is_valid = true;
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
		case PayTax:
		{
			// pay tax from income of given id
			while (!is_valid) {
				try {
					size_t id;	
					std::cout << "Insert Income ID you want to pay:\n>";
					std::cin >> id;
					handleInputError(std::cin);
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore newline

					system.markPaid(id);
					is_valid = true;
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
		case Quit: 
		{
			run = false;
			break;
		}
		default:
		{
			std::cout << "> Wrong Option! <\n";
		}
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
		//taxsytem
	} while (run);
	return 0;
};