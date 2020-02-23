/*
 *      File  : simulation.cpp
 *      Author: Stephen Lamalie
 *      Course: COP4534
 *      Proj  : Project 02
 */
#include "p_queue.hpp"
#include<queue>

void prompt(int*, int*,int*,int*);
float getIdleTime(float, float, float);
int factorial(int);
float getPeopleInSystem(float, float, float, float);
void displayStats(int*, int*, int*);
float getCustomerTime(float, float);
float getCustomersInQueue(float, float, float);
float getRho(float, float, float);
float getNextRandomInterval(int);
void showResults(int*,int*,int*,float*,float*,float*,float*,float*);
//void processStats(customer*);


// so i dont have to type std:: every time
using std::cout;
using std::cin;
using std::endl;

int main()
{
    //declare stuff

    // needed value for the stats
    int n; // number of arrivals to simulate
    int customersInSystem;
    int lambda; // average arrivals in a time period
    int mu;  // the average number served in a time period
    int servers;  // number of servers
    // for the simulation results
    float simTime = 0.0;  //the absolute time in the system
    float idleTime = 0.0; // the time when no one is in the system
    float waitedInLineTime = 0.0; // time spent waiting in line
    float serviceTime;  // time a customer spends getting service
    std::queue<customer*> fifo_queue; // fifo queue simulates people in the line
    p_queue my_pq; // priority queue that holds arrival and depare events
    float myTime; // the interval time for a customer
    int availableServers; // the amount of servers are are free
    customer* temp;
    customer* lastDepart = NULL;
    customer* nextInLine;
    int remainingCustomers; // remaining customers to be processed
    int waitedInQueue = 0;
    float timeInSim;
    int i;
    int count = 0;

    // to seed a random time varibale
    srand(time(0));
    //promt the user for the expected valies
    prompt(&n,&lambda,&mu,&servers);
    //display statistical results
    displayStats(&lambda, &mu, &servers);
    customersInSystem = n;
    //put max number of arrivals in the queue

    for(i = 0;i<my_pq.MAXSIZE;i++)
    {
        myTime = getNextRandomInterval(lambda);
        customer* newGuy = new customer();
        newGuy->arrivalTime = simTime + myTime;
        simTime += myTime;
        my_pq.insert(newGuy);
    }
    availableServers = servers; 


    while(customersInSystem > 0) 
    {   cout << ++count << endl;
        //customer* myGuy = new customer();
        temp = my_pq.pop();
        // if the event was an arrival
        if(!temp->hasArrived)
        {   if((availableServers == servers) && (lastDepart != NULL))
            {   
                idleTime = idleTime + (temp->arrivalTime - lastDepart->departTime);
            }
            // if there are serveres available
            if(availableServers > 0)
            {   
                --availableServers;
                
                temp->startOfService = temp->arrivalTime;
                myTime = getNextRandomInterval(mu);
                serviceTime = serviceTime + myTime;
                
                temp->departTime = temp->startOfService + myTime;
                temp->hasArrived = true;
                my_pq.insert(temp);
            } // else place customer in fifo queue
            else
            {
                //cout << ++count << endl;
                fifo_queue.push(temp);                
            }
            
        } // else it was a departure
        else
        {
            lastDepart = temp;
            ++availableServers;
            --customersInSystem;
            if(temp->arrivalTime != temp->startOfService)
            {
                waitedInQueue++;
                waitedInLineTime = waitedInLineTime + (temp->startOfService - temp->arrivalTime);
            }
            timeInSim = timeInSim + (temp->departTime - temp->arrivalTime);
            
            
            // if the fifo is not empty add a customer to the PQ from the fifo
            if(!fifo_queue.empty())
            {
                //remove customer from fifo queue
                nextInLine = fifo_queue.front();
                fifo_queue.pop();

                // add the customers approiate times
                myTime = getNextRandomInterval(mu);
                
                serviceTime = serviceTime + myTime;
                //cout << serviceTime << endl;
                nextInLine->startOfService = temp->departTime;
                nextInLine->departTime = nextInLine->startOfService + myTime;
                nextInLine->hasArrived = true;
                --availableServers;
                my_pq.insert(nextInLine);
            }
            //delete temp;
        }
        // if there are more arrivals to be processed and 
        // there are only at most servers + 1 people in priority queue
        // process more poeple
        if((my_pq.currentSize <= (servers+1)) && (customersInSystem > 0))
        {
            if(customersInSystem >= my_pq.MAXSIZE)
            {
                //fills up the priority queue until its "full"
                remainingCustomers = (my_pq.MAXSIZE - my_pq.currentSize);
            }
            else
            {
                remainingCustomers = customersInSystem - (servers + 1);
            }
            
            for(i = 0; i < remainingCustomers; i++)
            {   
                myTime = getNextRandomInterval(lambda);
                customer* newGuy = new customer();
                newGuy->arrivalTime = simTime + myTime;
                simTime += myTime;
                my_pq.insert(newGuy);
            }
        }


    }
    
    showResults(&n, &servers, &waitedInQueue, &simTime, &idleTime, &timeInSim, &serviceTime, &waitedInLineTime);
    /*cout <<  "numcustomers: " << n << endl;
    cout <<  "servers: " << servers << endl;
    cout <<  "num waited in queue: " << waitedInQueue << endl;
    cout <<  "sim time: " << simTime << endl;
    cout <<  "idel time: " << idleTime << endl;
    cout <<  "time spent in sim: " << timeInSim << endl;
    cout << "service time: "  << serviceTime << endl;
    cout <<  "waited in line time: " << waitedInLineTime << endl;

*/



    return 0;
}
void showResults(int* numCustomers, int* numServers, int* numWaited, float* sim, float* idle, float* inSystem, float* serveTime, float* timeInLine)
{
    cout << "Here are the simulated results:" << endl;

    cout << "The percent of idle time of the system:  ";
    cout <<  ((*idle / *sim) * 100.0) << endl;

    cout << "The average time a customer spends in the system:  ";
    cout << (*inSystem / *numCustomers) << endl;

    cout << "The average time a customer spends waiting in the queue:  ";
    
    if(*numWaited != 0)
    {
        cout << (*timeInLine / *numWaited) << endl;
    }
    else
    {
        cout << "0" << endl;
    }
    
    cout << "The utilization factor for the system:  ";
    cout << ((*serveTime) / ((*numServers) * (*sim))) << endl;


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

    cout << "The percent of idle time of the system:  ";
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
