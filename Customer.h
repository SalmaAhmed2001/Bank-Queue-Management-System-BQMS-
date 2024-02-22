#include <string>
using namespace std;
class Customer
{


public:
	string name;

	int EventTime;//arrival or leave 7sab el event

	string EventType="Arrival";//arrive o r leave the same previous

	int WaitingTime;

	int ServiceTime;


	int isVIP;

	int LeaveTime;


	Customer(){}


	int ArrivalTime, LeavingTime;
	Customer(string name, int arrivalTime, int serviceTime)
	{
		this->name = name;
		this->ArrivalTime = arrivalTime;
		this->ServiceTime = serviceTime;

	}


	Customer(string name, int arrivalTime, int serviceTime , int vip)
	{
		this->name = name;
		this->ArrivalTime = arrivalTime;
		this->ServiceTime = serviceTime;
		this->isVIP = vip;

	}
};
