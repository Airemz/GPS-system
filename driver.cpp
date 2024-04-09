// include libraries here
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "graph.h"



// For testing:
//./graph.out < inputs/test06.in > my_outputs/mtest06.out
// ./graph.out < inputs/test02.in > my_outputs/mtest02.out
// Add -g to cxxflags in make file
//valgrind --leak-check=full --show-leak-kinds=all ./tokenize.out <inputs/test03.in 
//valgrind --leak-check=full --show-leak-kinds=all ./graph.out

int main(){

    // Initialize the graph class
    Graph *Googoo_maps = new Graph;

    // infinite loop until exit function call
    while (true){

        // Receive User input and seperate into command and parameters
        std::string user_input, command, parameter;
        std::getline(std::cin, user_input);
        std::istringstream iss(user_input);
        iss >> command >> parameter;

        // Insert: Parse paramaters and call insert function, always output success
        if (command == "insert") {

            // Extract data and convert to appropriate data types
            unsigned int a = std::stoi(parameter);

            iss >> parameter;
            unsigned int b = std::stoi(parameter);

            iss >> parameter;
            double d = std::stod(parameter);

            iss >> parameter;
            double s = std::stod(parameter);

            // Initialize A to be 1 and call member function
            double A = 1;
            Googoo_maps->insert(a,b,d,s,A);
            std::cout << "success" << std::endl;
        }

        // Load: Open given file and extract words; always cout success 
        else if (command == "load") {

            // Initialize variables for parsing through file and a flag which will check if a word was inserted into the graph
            std::ifstream file(parameter);

            unsigned int a, b;
            double d, s;

            while (file >> a >> b >> d >> s) {
                // Insert data directly without using stringstream
                double A = 1;
                Googoo_maps->insert(a, b, d, s, A);
            }

            // Close the file so other files can be read
            file.close();
            std::cout << "success" << std::endl;
        }

        // Traffic: Open given file and parse paramaters and call traffic function, check if a node was updated/exists if so output success, else failure
        else if (command == "traffic") {
            
            // Extract data and convert to appropriate data types
            unsigned int a = std::stoi(parameter);

            iss >> parameter;
            unsigned int b = std::stoi(parameter);

            iss >> parameter;
            double A = std::stod(parameter);

            //Check if a node was updated/exists if so output success, else failure
            if (Googoo_maps->traffic(a,b,A)){std::cout << "success" << std::endl;}
            else{std::cout << "failure" << std::endl;}
        }

        // Traffic: Open given file and parse paramaters and call update function, check if a node was updated/exists if so output success, else failure
        else if (command == "update") {

            // Initialize variables for parsing through file and a flag which will check if a word was inserted into the hashmap
            std::ifstream file(parameter);
            bool flag;

            // Read the file line by line
            unsigned int a, b;
            double A;

            while (file >> a >> b >> A) {
                // Insert data directly without using stringstream
                if (Googoo_maps->traffic(a,b,A)){flag = true;} 
            }

            // Close the file so other files can be read
            file.close();

            if (flag){std::cout << "success" << std::endl;}
            else{std::cout << "failure" << std::endl;}
        }

        // Print: Check if a node exists if so print its neighbors and end the line, if it doesn't exist output failure
        else if (command == "print") {
            
            unsigned int a = std::stoi(parameter);

            // If a node exists but has no neighbours an empty line will be printed
            if (Googoo_maps->print(a)){std::cout << std::endl;}
            else{std::cout << "failure"  << std::endl;}
        }

        // Delete: remove a node if it exists and output success, else failure
        else if (command == "delete") {
            unsigned int a = std::stoi(parameter);

            if (Googoo_maps->remove(a)){std::cout << "success" << std::endl;}
            else{std::cout << "failure" << std::endl;}
            
        }

        // Path: call djikstras algorithm to find shortest path, if the output is empty meaning there is no path, output failure
        else if (command == "path") {

            // Extract data and convert to appropriate data types
            unsigned int a = std::stoi(parameter);

            iss >> parameter;
            unsigned int b = std::stoi(parameter);

            std::string output = Googoo_maps->path(a,b);

            if (output.empty()){std::cout << "failure" << std::endl;}
            else{std::cout << output << std::endl;}

            
        }

        // Path: call djikstras algorithm to find the weight of shortest path, if the output is 0 meaning there is no path, output failure, else output according to piazza post
        else if (command == "lowest") {

            // Extract data and convert to appropriate data types
            unsigned int a = std::stoi(parameter);

            iss >> parameter;
            unsigned int b = std::stoi(parameter);

            double output = Googoo_maps->lowest(a,b);

            if (output == 0){std::cout << "failure" << std::endl;}
            else{

                // As directed on piazza
                std::cout << std::fixed << std::showpoint;
                std::cout << std::setprecision(3);
                std::cout << output << std::endl;
            }
        }

        // Exit: call the graph destructor and return 0
        else if (command == "exit") {
            delete Googoo_maps;
            Googoo_maps = nullptr;
            return 0;
        }
    }
}