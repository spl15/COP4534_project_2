/*
 *      File  : p_queue.hpp
 *      Author: Stephen Lamalie
 *      Course: COP4534
 *      Proj  : Project 02
 */

#ifndef P_QUEUE_HPP
#define P_QUEUE_HPP
#include "customer.hpp"

class p_queue
{
    public:
        p_queue();
        void insert(customer*);
        customer* pop();
        int getLeftChild(int);
        int getRightChild(int);
        int getParent(int);
        void swap(int,int);
        void perkDown(int);
        void perkUp(int);
        customer* head;
        int currentSize;
        const int MAXSIZE = 200;
        customer** theLine;        
};

#endif