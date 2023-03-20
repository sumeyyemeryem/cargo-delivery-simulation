#include "Stack.h"
#include "Queue.h"
#include "iostream"
using namespace std;

class Transport {
public:
    struct Package {
        string name;

        Package* next;
        Package* prev;
    };
    struct Truck : public Package {
        string power;

    };
    struct Station {
        string name;
        Stack<Package> *packages = new Stack<Package>();
        Queue<Truck> *trucks = new Queue<Truck>();

        Station* next;
    };
    Station* head1 = NULL;

    //initial status of the stations
    void addStation(string name);
    void addPackage(string station, string package);
    void addTruck(string station, string truck, string power);

    //to perform the missions
    void performMission(string start, string midway, string target, string x, string y, string z);
    void print();




};


