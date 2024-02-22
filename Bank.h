#include <string>
#include "Customer.h"
#include <iostream>
#include <queue>
#include <windows.h>
using namespace std;

struct compareEventTime
{
    bool operator()(const Customer& lhs, Customer& rhs) const
    {
        return lhs.ArrivalTime > rhs.ArrivalTime;
    }
};


struct Teller
{
    bool isAvailable;

    int tellerNum;

    int numOfCustomerServed;

    int availableTime;

    int totalTimeServed;

};

class Bank
{
private:
    priority_queue<Customer, vector<Customer>, compareEventTime> customerPriorityQueue;


    int numOfTellers = 3;


    queue<Customer> bankQueue;


    int cur_Time = 0;

    Teller* tellers;

    int totalWaitingTime = 0;

    int totalServiceTime = 0;

public:
    Bank()
    {
        tellers = new Teller[numOfTellers];
        for (int i = 0; i < numOfTellers; ++i)
        {
            tellers[i].isAvailable = true;
            tellers[i].tellerNum = i + 1;
            tellers[i].numOfCustomerServed = 0;
            tellers[i].availableTime = 0;
            tellers[i].totalTimeServed = 0;

        }
    }

    ~Bank()
    {
        delete[] tellers;
    }



    void addToPriorityQueue(Customer c)
    {
        customerPriorityQueue.push(c);
    }


    void addToBankQueue(Customer c2)
    {
        bankQueue.push(c2);
    }



    void simulateBankOperation()
    {
        while (!customerPriorityQueue.empty())
        {

            Customer cur_Customer = customerPriorityQueue.top();
            cur_Time = cur_Customer.EventTime;
            customerPriorityQueue.pop();

            if (cur_Customer.EventType == "Arrival")
            {

                bool isServied = false;

                for (int i = 0; i < numOfTellers; i++)
                {
                    if (tellers[i].isAvailable)
                    {

                        cur_Customer.WaitingTime = cur_Time - cur_Customer.EventTime;

                        cur_Customer.EventTime = cur_Time + cur_Customer.ServiceTime;

                        cur_Customer.EventType = "Leave";

                        cout << "customer name : " << cur_Customer.name << " Waiting Time : " << cur_Customer.WaitingTime << " Service Time : " << cur_Customer.ServiceTime << " Leave Time : " << cur_Customer.EventTime << " served with Teller number : " << tellers[i].tellerNum << endl;

                        tellers[i].isAvailable = false;


                        totalServiceTime += cur_Customer.ServiceTime;

                        totalWaitingTime += cur_Customer.WaitingTime;

                        addToPriorityQueue(cur_Customer);

                        isServied = true;

                        break;
                    }
                }

                if (!isServied)
                {
                    addToBankQueue(cur_Customer);
                }
            }
            else if (cur_Customer.EventType == "Leave")
            {

                if (!bankQueue.empty())
                {

                    Customer current = bankQueue.front();


                    current.WaitingTime = cur_Time - current.EventTime;

                    current.EventTime = cur_Time + current.ServiceTime;

                    current.EventType = "Leave";

                    cout << "customer name : " << current.name << " Waiting Time : " << current.WaitingTime << " Service Time : " << current.ServiceTime << " Leave Time : " << current.EventTime << endl;

                    totalServiceTime += current.ServiceTime;

                    totalWaitingTime += current.WaitingTime;

                    addToPriorityQueue(current);

                    bankQueue.pop();

                }
                else
                {
                    for (int i = 0; i < numOfTellers; i++)
                    {
                        if (!tellers[i].isAvailable)
                        {
                            tellers[i].isAvailable = true;
                            break;
                        }
                    }
                }
            }
        }

        cout << "Total Sevice Time is : " << totalServiceTime << " and Total Waiting Time is : " << totalWaitingTime << endl;
    }





    Teller* closestAvailableTeller()
    {

        Teller* closestTeller = nullptr;


        int closestAvailableTime = INT_MAX;

        for (int i = 0; i < numOfTellers; i++)
        {
            if (tellers[i].availableTime < closestAvailableTime)
            {
                closestTeller = &tellers[i];

                closestAvailableTime = tellers[i].availableTime;
            }
        }

        return closestTeller;
    }
    void displayCustomerDetails(Customer c, Teller t)
    {

       cout << "customer name : " << c.name<<'\n'
            << "Waiting Time : " << c.WaitingTime<<'\n'
            << "Service Time : " << c.ServiceTime<<'\n'
            << "Leave Time : " << c.LeaveTime<<'\n'
            << "served with Teller number : " << t.tellerNum << endl;


    }

    void displayTellerDetails()
    {
  cout<<"------------------------------------------"<<'\n';
        cout << endl;

        cout <<"Tellers Details : " << endl;

        for (int i = 0; i < numOfTellers; i++)
        {
            cout<<"Teller Num : " <<tellers[i].tellerNum<<'\n'
                << "Total Time served : "  << tellers[i].totalTimeServed<<'\n'
                <<"and he served : " << tellers[i].numOfCustomerServed <<" customers"<<'\n'
                << endl;

        }

    }


    void displayAverage()
    {

        cout<<'-----------------------------------------'<<'\n';
        cout << endl;

        cout << "Service and Waiting Details : " << endl;

        cout << "Total Service Time is : " << totalServiceTime
             << "and Total Waiting Time is : " << totalWaitingTime << endl;


    }


    void simulateBankOperationWithPriority()
    {

    cout<<"--------------------------------------------------------"<<'\n';
        cout << endl;

        cout << "Customers Details : " << endl;

        while (!customerPriorityQueue.empty())
        {
            Customer cur_Customer = customerPriorityQueue.top();


            bool isServied = false;
            for (int i = 0; i < numOfTellers; i++)
            {
                if (tellers[i].isAvailable)
                {

                    cur_Customer.WaitingTime = cur_Customer.ArrivalTime - cur_Customer.ArrivalTime;
                    cur_Customer.LeaveTime = cur_Customer.ArrivalTime + cur_Customer.ServiceTime;
                    displayCustomerDetails(cur_Customer, tellers[i]);


                    tellers[i].isAvailable = false;
                    tellers[i].availableTime = cur_Customer.LeaveTime;
                    tellers[i].numOfCustomerServed++;

                    tellers[i].totalTimeServed += cur_Customer.ServiceTime;
                    totalServiceTime += cur_Customer.ServiceTime;
                    totalWaitingTime += cur_Customer.WaitingTime;

                    customerPriorityQueue.pop();



                    isServied = true;
                    break;
                }

            }

            if (!isServied)
            {


                Teller* closestTeller = closestAvailableTeller();

                    closestTeller->isAvailable = true;

                    closestTeller->numOfCustomerServed++;

                    cur_Customer.WaitingTime = closestTeller->availableTime - cur_Customer.ArrivalTime;

                    cur_Customer.LeaveTime = cur_Customer.ArrivalTime + cur_Customer.WaitingTime + cur_Customer.ServiceTime;

                    displayCustomerDetails(cur_Customer, *closestTeller);

                    totalServiceTime += cur_Customer.ServiceTime;

                    totalWaitingTime += cur_Customer.WaitingTime;

                    closestTeller->totalTimeServed += cur_Customer.ServiceTime;

                    closestTeller->availableTime = cur_Customer.LeaveTime;

                    closestTeller->isAvailable = false;

                    customerPriorityQueue.pop();



            }

        }

        displayTellerDetails();
        displayAverage();
    }



    void simulateBankOperationWithTellerAvailability ()
    {

    cout<<"----------------------------------------------"<<'\n';
        cout << endl;

        cout << "Customers Details : " << endl;

        while (!customerPriorityQueue.empty())
        {
            Customer cur_Customer = customerPriorityQueue.top();




            bool IsServied = false;
            for (int i = 0; i < numOfTellers; i++)
            {
                if (tellers[i].isAvailable)
                {

                    cur_Customer.WaitingTime = cur_Customer.ArrivalTime - cur_Customer.ArrivalTime;

                    cur_Customer.LeaveTime = cur_Customer.ArrivalTime + cur_Customer.ServiceTime;

                    displayCustomerDetails(cur_Customer, tellers[i]);

                    tellers[i].isAvailable = false;

                    tellers[i].availableTime = cur_Customer.LeaveTime;

                    tellers[i].numOfCustomerServed++;

                    tellers[i].totalTimeServed += cur_Customer.ServiceTime;

                    totalServiceTime += cur_Customer.ServiceTime;


                    totalWaitingTime += cur_Customer.WaitingTime;

                    customerPriorityQueue.pop();


                    IsServied = true;

                    break;
                }

            }

            if (!IsServied)
            {


                Teller* closestTeller = closestAvailableTeller();


                closestTeller->isAvailable = true;

                closestTeller->numOfCustomerServed++;

                cur_Customer.WaitingTime = closestTeller->availableTime - cur_Customer.ArrivalTime;

                cur_Customer.LeaveTime = cur_Customer.ArrivalTime + cur_Customer.WaitingTime + cur_Customer.ServiceTime;

                displayCustomerDetails(cur_Customer, *closestTeller);

                totalServiceTime += cur_Customer.ServiceTime;

                totalWaitingTime += cur_Customer.WaitingTime;

                closestTeller->totalTimeServed += cur_Customer.ServiceTime;

                closestTeller->availableTime = cur_Customer.LeaveTime;

                closestTeller->isAvailable = false;

                customerPriorityQueue.pop();



            }

        }

        displayTellerDetails();

        displayAverage();
    }

};
