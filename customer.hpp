/*
 *      File  : customer.hpp
 *      Author: Stephen Lamalie
 *      Course: COP4534
 *      Proj  : Project 02
 */
#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <iostream>
#include <cmath>

class customer
{
    public:
        customer();
        float arrivalTime;
        float startOfService;
        float departTime;
        bool hasArrived;
        customer* nextCustomer;

};

#endif