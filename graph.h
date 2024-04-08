#include <iostream>
#include <string>
#include <unordered_map>
#include <tuple>

class Graph{
    private:

        // Define the pointer to the hashmap 
        // The first hashmap key represents the nodes while the second hashmap represents the neighbors
        // The second hashmap's values are tuples which store the d, s, and A values
        std::unordered_map <unsigned int, std::unordered_map <unsigned int, std::tuple <double, double, double>>> *graph;

    public:

        // Constructor/ destructor
        Graph();
        ~Graph();
        
        // Member functions
        void insert(unsigned int& a, unsigned int& b, double& d, double& s, double& A);
        bool traffic(unsigned int& a, unsigned int& b, double& A);
        bool print(unsigned int& a);
        bool remove(unsigned int& a);
        std::string path(unsigned int& a, unsigned int&b);
        double lowest(unsigned int& a, unsigned int&b);



};

