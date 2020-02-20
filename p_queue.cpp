/*
 *      File  : p_queue.cpp
 *      Author: Stephen Lamalie
 *      Course: COP4534
 *      Proj  : Project 02
 */
#include "p_queue.hpp"
p_queue::p_queue()
{
    this->currentSize = 0;
    // create the array of customers
    theLine = new customer*[MAXSIZE];
    for(int i = 0;i < MAXSIZE; i++)
    {
        theLine[i] = NULL;
    }
    head = NULL;
}
void p_queue::swap(int swap_1, int swap_2)
{
    theLine[0] = theLine[swap_1];
    theLine[swap_1] = theLine[swap_2];
    theLine[swap_2] = theLine[0];
}
customer* p_queue::pop()
{
    //if (head != NULL)
    //{
        //delete head;
    //}
    head = theLine[1];
    theLine[1] = theLine[currentSize];
    --currentSize;
    perkDown(1);

    return head;
}
void p_queue::perkDown(int pivit)
{
    float left;
    float right;
    float parent;
    // if the left and right children are out of scope, we are done
    if((pivit * 2) > MAXSIZE)
    {
        return;
    }   //else if the left child is the last element, compare left child with parent
    else if(((pivit * 2) == MAXSIZE) && (theLine[getLeftChild(pivit)] != NULL))
    {
        if(theLine[pivit]->hasArrived)
        {
            parent = theLine[pivit]->departTime;
        }
        else
        {
            parent = theLine[pivit]->arrivalTime;
        }

        if(theLine[getLeftChild(pivit)]->hasArrived)
        {
            left = theLine[pivit]->departTime;
        }
        else
        {
            left = theLine[pivit]->arrivalTime;
        }

        if(left < parent)
        {
            swap(pivit, getLeftChild(pivit));
        }
        
        return;
    }   // normal scenario
    else
    {   //if both children are null we are done
        if((theLine[getLeftChild(pivit)] == NULL) && (theLine[getRightChild(pivit)] == NULL))
        {
            return;
        }   // if the right child in null and the left child isnt, we are at the end of the heap
        else if((theLine[getLeftChild(pivit)] != NULL) && (theLine[getRightChild(pivit)] == NULL))
        {
            if(theLine[pivit]->hasArrived)
            {
                parent = theLine[pivit]->departTime;
            }
            else
            {
                parent = theLine[pivit]->arrivalTime;
            }

            if(theLine[getLeftChild(pivit)]->hasArrived)
            {
                left = theLine[pivit]->departTime;
            }
            else
            {   
                left = theLine[pivit]->arrivalTime;
            }

            if(left < parent)
            {
                p_queue::swap(pivit, getLeftChild(pivit));
            }
        
            return;
        }  // when both children are NOT null
        else
        {
            if(theLine[pivit]->hasArrived)
            {
                parent = theLine[pivit]->departTime;
            }
            else
            {
                parent = theLine[pivit]->arrivalTime;
            }

            if(theLine[getLeftChild(pivit)]->hasArrived)
            {
                left = theLine[getLeftChild(pivit)]->departTime;
            }
            else
            {
                left = theLine[getLeftChild(pivit)]->arrivalTime;
            }
            
            if(theLine[getRightChild(pivit)]->hasArrived)
            {
                right = theLine[getRightChild(pivit)]->departTime;
            }
            else
            {
                right = theLine[getRightChild(pivit)]->arrivalTime;
            }
            
            if (left < right)
            {
                // compare left child with parent
                if(parent < left)
                {
                    return;
                }
                else
                {
                    // left child is less than parent, needs to swap and recurse on left child
                    p_queue::swap(pivit, getLeftChild(pivit));
                    perkDown(getLeftChild(pivit));
                }


            }
            else
            {
                // compare right child with parent
                if(parent < right)
                {
                    return;
                }
                else
                {
                    // right child is less than parent, needs to swap and recurse on right child
                    p_queue::swap(pivit, getRightChild(pivit));
                    perkDown(getRightChild(pivit));
                }
            }
        }
    }
}

void p_queue::perkUp(int pivit)
{
    float child;
    float parent;
    if(pivit == 1)
    {
        return;
    }
    else
    {
        if(theLine[pivit]->hasArrived)
        {
            child = theLine[pivit]->departTime;
        }
        else
        {
            child = theLine[pivit]->arrivalTime;
        }

        if(theLine[getParent(pivit)]->hasArrived)
        {
            parent = theLine[getParent(pivit)]->departTime;
        }
        else
        {
            parent = theLine[getParent(pivit)]->arrivalTime;
        }
    
        if(child < parent)
        {
            p_queue::swap(pivit, getParent(pivit));
            perkUp(getParent(pivit));
        }
        else
        {
            return;
        }
    }
}

int p_queue::getLeftChild(int parent)
{
    return (parent * 2);
}
int p_queue::getRightChild(int parent)
{
    return ((parent * 2) + 1);
}
int p_queue::getParent(int child)
{
    return (child / 2);
}

void p_queue::insert(customer* newGuy)
{
    if(currentSize == MAXSIZE)
    {
        std::cout << "cannot add any more to the queue" << std::endl;
    }
    else
    {
        ++currentSize;
        if(currentSize == 1)
        {
            theLine[currentSize] = newGuy;
            return;
        }
        else
        {
            theLine[currentSize] = newGuy;
            perkUp(currentSize);
        }
        return;
    }
    
}
int main()
{
    p_queue pq;

    //ustomer newGuy1;
    customer* ptr1 = new customer();
    customer* ptr3 = new customer();
    customer* ptr4 = new customer();
    customer* ptr5 = new customer();
    
    //customer newGuy2;
    customer* ptr2 = new customer();
    
    ptr1->hasArrived = true;
    ptr1->departTime = 5.746;
    ptr2->arrivalTime = 5.3489;
    ptr5->hasArrived = true;
    ptr5->departTime = 3.72;
    ptr3->arrivalTime = 4.85;
    ptr4->arrivalTime = 7.43212;




    pq.insert(ptr1);
    pq.insert(ptr2);
    pq.insert(ptr3);
    pq.insert(ptr4);
    pq.insert(ptr5);

    pq.pop();
    pq.pop();
    std::cout << "Arrival Time: " << pq.head->arrivalTime << std::endl;
    std::cout << "Departure Time: " << pq.head->departTime << std::endl;
    
    std::cout << pq.currentSize << std::endl;

    return 0;
}
