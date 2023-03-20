#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Transport.h"
using namespace std;
ofstream output;

int main(int argc, char *argv[]) {

    ifstream destination(argv[1]);
    ifstream package(argv[2]);
    ifstream truck(argv[3]);
    ifstream missions(argv[4]);
    output.open(argv[5]);

    //initial status of the stations
    Transport transport;
    if(!destination.fail()) {
        string line;
        while(getline(destination, line)){
            if(line != "\n"){
                transport.addStation(line);
            }
        }
    }

    vector<string> tokens;
    if(!package.fail()) {
        string line;
        while(getline(package, line)){
            if(line != "\n"){
                istringstream iss(line);
                string token;
                while(getline(iss, token, ' ')){
                    tokens.push_back(token);
                }
                transport.addPackage(tokens.at(1), tokens.at(0));
                tokens.clear();
            }
        }
    }
    if(!truck.fail()) {
        string line;
        while(getline(truck, line)){
            if(line != "\n"){
                istringstream iss(line);
                string token;
                while(getline(iss, token, ' ')){
                    tokens.push_back(token);
                }
                transport.addTruck(tokens.at(1), tokens.at(0), tokens.at(2));
                tokens.clear();
            }
        }
    }

    //missions
    if(!missions.fail()) {
        string line;
        while(getline(missions, line)){
            if(line != "\n"){
                istringstream iss(line);
                string token;
                while(getline(iss, token, '-')){
                    tokens.push_back(token);
                }
                transport.performMission(tokens.at(0), tokens.at(1), tokens.at(2), tokens.at(3), tokens.at(4), tokens.at(5));
                tokens.clear();
            }
        }
    }

    transport.print();

}
