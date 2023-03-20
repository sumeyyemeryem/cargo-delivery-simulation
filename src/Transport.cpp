#include <vector>
#include "Transport.h"
#include <sstream>
#include <fstream>
extern ofstream output;

void Transport::addStation(const string name) {

    Station *temp = new Station();
    temp->name = name;
    temp->next = NULL;

    if(head1 == NULL){
        head1 = temp;
    }
    else{
        Station* last = head1;
        while (last->next != NULL) last = last->next;
        last->next = temp;
    }
}

void Transport::addPackage(string station, string package) {

    Station* temp = head1;
    Package* p = new Package();
    p->name = package;
    while (temp != NULL){
        if(temp->name == station){
            temp->packages->push(*p);
            return;
        }
        temp = temp->next;
    }

}

void Transport::addTruck(string station, string truck, string power) {


    Station* temp = head1;
    Truck* t = new Truck();
    t->name = truck;
    t->power = power;
    while (temp != NULL){
        if(temp->name == station){
            temp->trucks->enqueue(*t);
            return;
        }
        temp = temp->next;
    }

}


void Transport::performMission(string start, string midway, string target, string x, string y,string z) {

    //taking packages from starting point
    Station* s = head1;
    while (s != NULL){
        if(s->name == start){ //find the starting station
            break;
        }
        s = s->next;
    }

    Truck* head2 = new Truck(); //head of the cargo
    s->trucks->getFront(*head2); //cargo truck as head of the cargo
    s->trucks->dequeue();

    int n = stoi(x);
    for(int i = 0; i < n; i ++){
        //allocate memory for node
        Package* newNode = new Package();

        s->packages->getTop(*newNode);
        s->packages->pop();

        Package* last = head2; //set last node value to head

        //new node is the last node , so set next of new node to null
        newNode->next = NULL;

        while (last->next != NULL) last = last->next;

        last->next = newNode;
        newNode->prev = last;

    }

    Station* m = head1;
    while (m != NULL){
        if(m->name == midway){ //find the midway station
            break;
        }
        m = m->next;
    }

    //taking the packages from midway
    int j = stoi(y);
    for(int i = 0; i < j; i ++){
        //allocate memory for node
        Package* newNode = new Package();

        m->packages->getTop(*newNode);
        m->packages->pop();

        //set last node value to head
        Package* last = head2;
        //new node is the last node , so set next of new node to null
        newNode->next = NULL;

        while (last->next != NULL) last = last->next;

        last->next = newNode;
        newNode->prev = last;

    }

    vector<string> deleted;
    //leaving packages at midway
    int length = z.size();
    for(int i = 0; i < length; i = i+2){
        unsigned char uc = z.at(i);
        int index = uc - 48;
        int k = 0;
        Package* temp = head2->next;
        while (temp != NULL){
            if(k == index){ //find the package to be left
                break;
            }
            temp = temp->next;
            k++;
        }
        deleted.push_back(temp->name);
    }

    for(const auto& name : deleted){
        Package* temp1 = head2->next;
        while (temp1 != NULL){
            if(temp1->name == name){ //find the package to be left
                break;
            }
            temp1 = temp1->next;
        }
        if (temp1->next != NULL) {
            temp1->next->prev = temp1->prev;
            temp1->prev->next = temp1->next;
        }
        else{//deleting the last node
            temp1->prev->next = NULL;
        }

        m->packages->push(*temp1);//push the package to the midway stack
        free(temp1);
    }


    //leaving all the packages at the target station
    Station* t = head1;
    while (t != NULL){
        if(t->name == target){ //find the target station
            break;
        }
        t = t->next;
    }

    Package* temp = head2->next;
    while (temp != NULL){
        t->packages->push(*temp);//push the package to the target stack
        temp = temp->next;
    }

    Package* head = head2->next;
    Package* tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }

    t->trucks->enqueue(*head2); //leave the truck at the target station
    //at last get rid of the cargo list
    free(head2);

}

void Transport::print() {

    Station* temp = head1;
    while (temp != NULL){

        output << temp->name << endl;
        output << "Packages:" << endl;
        Package* top = new Package();
        while (!temp->packages->isEmpty()){
            temp->packages->getTop(*top);
            output << top->name << endl;
            temp->packages->pop();
        }

        output << "Trucks:" << endl;
        Truck* front = new Truck();
        while (!temp->trucks->isEmpty()){
            temp->trucks->getFront(*front);
            output << front->name << endl;
            temp->trucks->dequeue();
        }

        output << "-------------" << endl;
        temp = temp->next;
    }

}
