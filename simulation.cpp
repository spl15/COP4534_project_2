/*
 *      File  : simulation.cpp
 *      Author: Stephen Lamalie
 *      Course: COP4534
 *      Proj  : Project 02
 */
#include "customer.hpp"

void prompt(int*, int*,int*,int*);
float getIdleTime(float, float, float);
int factorial(int);
float getPeopleInSystem(float, float, float, float);
void displayStats(int*, int*, int*);
float getCustomerTime(float, float);
float getCustomersInQueue(float, float, float);
float getRho(float, float, float);
float getNextRandomInterval(int);

// so i dont have to type std:: every time
using std::cout;
using std::cin;
using std::endl;

int main()
{
    //declare stuff

    int n; // nuumber of arrivals to simulate
    int lambda; // average arrivals in a time period
    int mu;  // the average number served in a time period
    int servers;  // number of servers

    // to seed a random time varibale
    srand(time(0));
    
    
    //prompt(&n,&lambda,&mu,&servers);
    //displayStats(&lambda, &mu, &servers);
    
    return 0;
}
void prompt(int* myN,int* myLambda, int* myMu, int* myServers)
{
    cout << "Please enter the following values" << endl;

    cout << "number of arrivals to simulate: "<< endl;
    cout << "(must be between 1000-5000)" << endl;
    
    std::cin >> *myN;
    while((*myN < 1000) || (*myN > 5000))
    {
        cout << "Please try again" << endl;
        cout << "(must be between 1000-5000)" << endl;
        cin >> *myN;
    }

    cout << "average arrivals in a time period" << endl;
    cin >> *myLambda;

    cout << "the average number served in a time period" << endl;
    cin >> *myMu;

    cout << "the number of service channels between 1 and 10" << endl;
    cin >> *myServers;
    while((*myServers < 1) || (*myServers > 10))
    {
        cout << "(1-10)" << endl;
        cin >> *myServers;
    }
}

int factorial(int x)
{
    if(x == 0)
    {
        return 1;
    }
    else
    {
        int total = 1;
        for(int i = 1; i <= x;i++)
        {
            total *= i;
        }
        return total;
    }
    
}
float getIdleTime(float myLambda, float myMu, float myServers)
{
    float bottomRight;
    float bottomLeft;
    float total;
    float temp = myLambda / myMu;

    for(int i = 0;i < myServers;i++)
    {
        total = (1 / factorial(i)) * (pow(temp,i));
        bottomLeft += total;     
    }

    bottomRight = (1.0/ factorial(myServers)) * (pow(temp,myServers)) * ((myServers * myMu) / ((myServers * myMu) - myLambda));

    temp = bottomRight + bottomLeft;

    return (1 / temp);

}
float getPeopleInSystem(float myLambda, float myMu, float myServers, float myIdle)
{
    float total = 0.0;
    float temp = (myLambda / myMu);


    total = ((myLambda * myMu * (pow(temp,myServers))) / (((float)factorial(myServers - 1)) * (pow((myServers * myMu - myLambda),2)))) * (myIdle) + (temp);


    return total;
}
float getCustomersInQueue(float myLambda, float myMu, float myPeopleInSystem)
{
    float total = myPeopleInSystem;
    float temp = (myLambda / myMu);
    total -= temp;

    return total;
}
float getCustomerTime(float myLambda, float myPeopleInSystem)
{
    float total;

    total = (myPeopleInSystem / myLambda);

    return total;
}
float getTimeWaiting(float myLambda, float myCustomersInQueue)
{
    float total = myCustomersInQueue / myLambda;

    return total;
}
float getRho(float myLambda, float myMu, float myServers)
{
    float total;
    total = ((myLambda) / (myServers * myMu));
    return total;
}
void displayStats(int* myLambda, int* myMu, int* myServers)
{
    float idleTime;
    float peopleInSystem;
    float timeSpentInSystem;
    float customersInQueue;
    float timeInQueue;
    float rho;


    cout << "\nHere are the analytical statistics:\n" << endl;

    cout << "The idle time of the system:  ";
    idleTime = getIdleTime((float)*myLambda, (float)*myMu, (float)*myServers);
    cout << idleTime << endl;

    cout << "The average number of people in the system:  ";
    peopleInSystem = getPeopleInSystem((float)*myLambda, (float)*myMu, (float)*myServers, idleTime);
    cout << peopleInSystem << endl;

    cout << "The average time a customer spends in the system:  ";
    timeSpentInSystem = getCustomerTime((float)*myLambda, peopleInSystem);
    cout << timeSpentInSystem << endl;

    cout << "The average numbers of customers in the queue:  ";
    customersInQueue = getCustomersInQueue((float)*myLambda,(float)*myMu , peopleInSystem);
    cout << customersInQueue << endl;

    cout << "The average time a customer spends waiting in the queue:  ";
    timeInQueue = getTimeWaiting((float)*myLambda, customersInQueue);
    cout << timeInQueue << endl;

    cout << "The utilization factor for the system:  ";
    rho = getRho((float)*myLambda,(float)*myMu,(float)*myServers);
    cout << rho <<endl;

}
float getNextRandomInterval(int avg)
{
    float intervalTime = 0.0;
    float f = (rand() / (RAND_MAX * 1.0));
    intervalTime = (-1.0) * (1.0 / avg) * (log(f));
    
    return intervalTime;
}
