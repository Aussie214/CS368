#include <iostream>
#include <string>
using namespace std;
int main() {
	//Grab user input
	std::cout << "Your name here ";
	std::string user_string;
	getline(cin, user_string);
	std::string edited_String;
	std::cout << "\n";
	//Entered a name
	if (user_string.size() != 0) {
		edited_String = " Welcome " + user_string + "! Enjoy the class! "; 
	}
	//Generic Greeting
	else {
		edited_String = " Welcome CS368 Student! Enjoy the class! ";
	}
	//Create text ouput
	for (int i = 0; i < edited_String.size() + 2; i++) {
		std::cout << "*";
	}
	std::cout << "\n";
	std::cout << "*";
	for (int a = 0; a < edited_String.size(); a++) {
		std::cout << " ";
	}	
	std::cout << "*" << std::endl;
	std::cout << "*";
	std::cout << edited_String;
	std::cout << "*" << std::endl;
	std::cout << "*";
        for (int a = 0; a < edited_String.size(); a++) {
                std::cout << " ";
        }
        std::cout << "*" << std::endl;
	for (int i = 0; i < edited_String.size() + 2; i++) {
                std::cout << "*";
        }
	std::cout << "\n";
	return 0;
}
