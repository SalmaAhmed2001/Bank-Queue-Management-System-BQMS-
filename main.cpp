#include <iostream>
#include "WaitingQueue.h"
#include "Bank.h"
using namespace std;

int main() {

    Bank b1;



    int numOfCustomers;
    cout <<"Welcom to Our Bank System : "<<'\n';
    cout<<'\n';
    cout << "Enter the number of customers: ";
    cin >> numOfCustomers;

    for (int i = 0; i < numOfCustomers; ++i) {
        string name;

        int arrivalTime, serviceTime;

        cout << "Enter Details For Customer Number " << i + 1 << ":" << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Arrival Time: ";
        cin >> arrivalTime;
        cout << "Service Time: ";
        cin >> serviceTime;

        Customer customer = Customer(name, arrivalTime, serviceTime);
        b1.addToPriorityQueue(customer);
    }


    b1.simulateBankOperationWithPriority();

    cout <<'\n';
    cout <<"Thank You For Your Visit , Goodbye! "<<'\n';

    return 0;
}
