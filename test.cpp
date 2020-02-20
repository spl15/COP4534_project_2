#include"p_queue.hpp"

int main()
{

    customer* myGuy = new customer;
    customer* newGuy = new customer;

    myGuy->arrivalTime = 5.5;

    newGuy = myGuy;

    //delete myGuy;

    std::cout << newGuy->arrivalTime << std::endl;

    return 0;
}
