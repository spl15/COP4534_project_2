/*
 *      File  : customer.cpp
 *      Author: Stephen Lamalie
 *      Course: COP4534
 *      Proj  : Project 02
 */
#include "customer.hpp"
customer::customer()
{
    this->arrivalTime = 0;
    this->departTime = 0;
    this->hasArrived = false;
    this->startOfService = 0;
    this->nextCustomer = NULL;
}