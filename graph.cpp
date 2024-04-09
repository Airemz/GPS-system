#include "graph.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <tuple>
#include <queue>
#include <set>
#include <utility>
#include <stack>
#include <limits>

// Constructor
Graph::Graph(){
    graph = new std::unordered_map <unsigned int, std::unordered_map <unsigned int, std::tuple <double, double, double>>>;
}

// Destructor
Graph::~Graph(){
    delete graph;
}

void Graph::insert(unsigned int& a, unsigned int& b, double& d, double& s, double& A){

    // Check if vertex b is a neighbour of vertex a, if so update d and s values, but leave A
    if ((*graph).find(a) != (*graph).end() && (*graph).find(b) != (*graph).end()){
        if ((*graph)[a].find(b) != (*graph)[a].end()){
            std::get<0> ((*graph)[a][b]) = std::get<0> ((*graph)[b][a]) = d;
            std::get<1> ((*graph)[a][b]) = std::get<1> ((*graph)[b][a]) = s;
        }

        else{ (*graph)[a][b] = (*graph)[b][a] = std::make_tuple(d,s,A);}
    }

    // If the edge doesn't exist, create it
    else{ (*graph)[a][b] = (*graph)[b][a] = std::make_tuple(d,s,A);}
}

bool Graph::traffic(unsigned int& a, unsigned int& b, double& A){

    // Chcek if vertex b is a neighbour of vertex a, if so update the A value and return true
    if ((*graph).find(a) != (*graph).end() && (*graph).find(b) != (*graph).end()){
        if ((*graph)[a].find(b) != (*graph)[a].end()){
            std::get<2>((*graph)[a][b]) = std::get<2> ((*graph)[b][a]) = A;
            return true;
        }

        else {return false;}
    }
    
    // Return false since the verticies are not neighbours
    else {return false;}
}

bool Graph::print(unsigned int& a){

    bool flag;

    // Check if vertex a is in our graph and update our flag / return false
    if ((*graph).find(a) != (*graph).end()){

        flag = true;

        // Itterate through all of vertex a's neighbours and output them with spaces in between
        for (auto& vertex : (*graph)[a]){
        std::cout << std::to_string(vertex.first) + " ";
        }

        return flag;
    }

    else {return false;}

    
}

bool Graph::remove(unsigned int& a){

    // Check if vertex a is in our graph, if not return false
    if ((*graph).find(a) != (*graph).end()){

        // First, itterate through all verticies and delete vertex a from their neighbours
        for (auto& neighbours : (*graph)){
            neighbours.second.erase(a);
        }

        // Finally, delete vertex a from our graph and return true;
        (*graph).erase(a);

        return true;
    }

    return false;
}

std::string Graph::path(unsigned int& a, unsigned int&b){

    std::string empty;
    std::string &output = empty;

    // Check if either of the nodes do not exist, return empty string
    if ((*graph).find(a) == (*graph).end() || (*graph).find(b) == (*graph).end()) {return output;}

    // Create a min heap sorted by the distance(T value) and their corresponding vertex
    std::priority_queue <std::pair <double, unsigned int>, std::vector <std::pair <double, unsigned int>>,std::greater <std::pair <double, unsigned int>>> Priority_Queue;
    
    // Define 2 hashmaps of the best distance between a vertex and all its neighbours, and the closest neighbour of every vertex, as well as a set of ints following djikstras algorithm
    std::unordered_map <unsigned int, double> best_distance;
    std::unordered_map<unsigned int, unsigned int> predecessor;
    std::set<unsigned int> completed;

    // Initialize the best distance table with all entries have ∞
    for(auto& pair : (*graph)){
        best_distance[pair.first] = std::numeric_limits<double>::infinity();
    }

    // Initialize the starting vertex to have a distance of 0, and push this onto the PQ
    best_distance[a] = 0.0;
    Priority_Queue.push(std::make_pair(0.0, a));

    // Itterate through all elements in our PQ/keep adding until we reach vertex b
    while (!Priority_Queue.empty()){

        // Pop and read the distance and vertex of our min element in our PQ
        std::pair <double, unsigned int> popped = Priority_Queue.top();
        Priority_Queue.pop();

        double current_distance = popped.first;
        unsigned int current_vertex = popped.second;

        // if a vertex is already completed, continue to the next element in the PQ
        if (completed.find(current_vertex) != completed.end()) {
            continue; 
        } 

        // Insert the vertex into the completed set so that we don't overwrite the best distance
        completed.insert(current_vertex);

        // Check if we reached our destinate node
        if (current_vertex == b) {
            unsigned int &vertex = b;
            std::stack<unsigned int> best_path;

            // Itterate thourgh the predecessors hashmap until we reach the source vertex, pushing to the stack each time
            while (vertex != a) {
                best_path.push(vertex);
                vertex = predecessor[vertex];
            }
            
            // Push the source vertex
            best_path.push(a); 

            // Itterate through the stack, adding to the output and popping each time
            while (!best_path.empty()) {
                output += std::to_string(best_path.top()) + " ";
                best_path.pop();
            }

            return output;
        }

        // Itterate through all of the current vertex's neighbours 
        for(auto& adjacencies : (*graph)[current_vertex]){
            
            unsigned int adjacent_vertex = adjacencies.first;
            auto& weights = adjacencies.second;
            
            double T = std::get<0>(weights)/(std::get<1>(weights)*std::get<2>(weights));
            
            // Check if the vertex is already completed and that the distance is the shortest among the neighbours of the current vertex
            if (!completed.count(adjacent_vertex) && current_distance + T < best_distance[adjacent_vertex]){

                // Update the hashmaps and push the new element into the PQ
                best_distance[adjacent_vertex] = current_distance + T;
                predecessor[adjacent_vertex] = current_vertex;
                Priority_Queue.push(std::make_pair(current_distance + T, adjacent_vertex));
            }
        }
    }
    
    return output;
}

double Graph::lowest(unsigned int& a, unsigned int&b){


    double output = 0.0;

    // Check if either of the nodes do not exist, return 0
    if ((*graph).find(a) == (*graph).end() || (*graph).find(b) == (*graph).end()) {return output;}
    
    // Create a min heap sorted by the distance(T value) and their corresponding vertex
    std::priority_queue <std::pair <double, unsigned int>, std::vector <std::pair <double, unsigned int>>,std::greater <std::pair <double, unsigned int>>> Priority_Queue;
    
    // Define 2 hashmaps of the best distance between a vertex and all its neighbours, and the closest neighbour of every vertex, as well as a set of ints following djikstras algorithm
    std::unordered_map <unsigned int, double> best_distance;
    std::unordered_map<unsigned int, unsigned int> predecessor;
    std::set<unsigned int> completed;

    // Initialize the best distance table with all entries have ∞
    for(auto& pair : (*graph)){
        best_distance[pair.first] = std::numeric_limits<double>::infinity();
    }

    // Initialize the starting vertex to have a distance of 0, and push this onto the PQ
    best_distance[a] = 0.0;
    Priority_Queue.push(std::make_pair(0.0, a));

    // Itterate through all elements in our PQ/keep adding until we reach vertex b
    while (!Priority_Queue.empty()){

        // Pop and read the distance and vertex of our min element in our PQ
        std::pair <double, unsigned int> popped = Priority_Queue.top();
        Priority_Queue.pop();

        double current_distance = popped.first;
        unsigned int current_vertex = popped.second;

         // if a vertex is already completed, continue to the next element in the PQ
        if (completed.find(current_vertex) != completed.end()) {
            continue; 
        } 

        // Insert the vertex into the completed set so that we don't overwrite the best distance
        completed.insert(current_vertex);

        // Check if we reached our destination node
        if (current_vertex == b) {
            output = best_distance[b];
            return output;
        }
        
        // Itterate through all of the current vertex's neighbours 
        for(auto& adjacencies : (*graph)[current_vertex]){
            
            unsigned int adjacent_vertex = adjacencies.first;
            auto& weights = adjacencies.second;
            
            double T = std::get<0>(weights)/(std::get<1>(weights)*std::get<2>(weights));
            
            // Check if the vertex is already completed and that the distance is the shortest among the neighbours of the current vertex
            if (!completed.count(adjacent_vertex) && current_distance + T < best_distance[adjacent_vertex]){

                // Update the hashmaps and push the new element into the PQ
                best_distance[adjacent_vertex] = current_distance + T;
                predecessor[adjacent_vertex] = current_vertex;
                Priority_Queue.push(std::make_pair(current_distance + T, adjacent_vertex));
            }
        }
    }

    return output;
}