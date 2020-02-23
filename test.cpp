#include"customer.hpp"

int main()
{

    customer* myGuy =new customer;
    customer* newGuy;
    customer* thisGuy = new customer;

    myGuy->arrivalTime = 5.5;

    newGuy = myGuy;

    thisGuy->arrivalTime = 2.2;

    myGuy = thisGuy;

    std::cout << newGuy->arrivalTime << std::endl;

    return 0;
}
