#include "../PROI_PODATKI_Lib/TaxSystemLib.h"
#include "SavingJson.h"
#include <iostream>

Client createClient(int my_choice, size_t& index_XD) {
	
	if (my_choice == 1) {
		Person client(size_t(index_XD), {});
		index_XD++;
		return client;
	}
	else if (my_choice == 2) {
		Company client(size_t(index_XD), {});
		index_XD++;
		return client;
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
	do {
		is_valid = false;

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