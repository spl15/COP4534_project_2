/*
 *      File  : customer.cpp
 *      Author: Stephen Lamalie
 *      Course: COP4534
 *      Proj  : Project 02
 */
#include "customer.hpp"
customer::customer()
{
    this->arrivalTime = -1;
    this->departTime = -1;
    this->hasArrived = false;
    this->startOfService = -1;
    this->nextCustomer = NULL;
}