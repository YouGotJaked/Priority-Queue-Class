#include <cstdlib>
#include <iostream>
#include "pqueue.h"

namespace coen70_lab8 {

    //CONSTRUCTOR

    PriorityQueue::PriorityQueue() {
        many_nodes = 0;
        head_ptr = NULL;
    }

    //COPY CONSTRUCTOR

    PriorityQueue::PriorityQueue(const PriorityQueue& other) {
        //check for self assignment
        if (this == &other) {
            return;
            //check for empty source
        } else if (other.is_empty()) {
            head_ptr = NULL;
            many_nodes = 0;
        } else {
            operator=(other);
        }
    }

    //DESTRUCTOR

    PriorityQueue::~PriorityQueue() {
        clear();
    }

    //ASSIGNMENT OPERATOR

    void PriorityQueue::operator=(const PriorityQueue& other) {
        //check for self assignment
        if (this == &other) {
            return;
        }
        //deallocate original queue
        clear();

        //check if source is empty
        if (other.is_empty()) {
            head_ptr = NULL;
            many_nodes = 0;
            return;
        }

        for (node *temp = other.head_ptr; temp != NULL; temp = temp->link()) {
            insert(temp->data(), temp->priority());
        }
    }

    void PriorityQueue::insert(const Item& entry, unsigned int priority) {
        node *iter = head_ptr, *prev = NULL, *temp;

        //check if queue is empty
        if (is_empty()) {
            head_ptr = new node;
            head_ptr->set_link(NULL);
            temp = head_ptr;
        } else {
            //check where to insert
            while (iter != NULL && priority <= iter->priority()) {
                prev = iter;
                iter = iter->link();
            }
            //if inserting before head
            if (prev == NULL) {
                prev = new node;
                prev->set_link(head_ptr);
                head_ptr = prev;
                temp = head_ptr;
            } else {
                temp = new node;
                prev->set_link(temp);
                temp->set_link(iter);
            }
        }
        temp->set_data(entry);
        temp->set_priority(priority);
        many_nodes++;
    }

    PriorityQueue::Item PriorityQueue::get_front() {
        if (!is_empty()) {
            node *temp = head_ptr;
            head_ptr = head_ptr->link();

            Item front = temp->data();

            delete temp;
            many_nodes--;
            return front;
        }
        return (PriorityQueue::Item)NULL;
    }

    void PriorityQueue::printlist() {
        for (node *temp = head_ptr; temp != NULL; temp = temp->link()) {
            std::cout << temp->data() << std::endl;
        }
    }

    void PriorityQueue::clear() {
        node *temp = head_ptr;

        while (head_ptr != NULL) {
            head_ptr = head_ptr->link();
            delete temp;
            temp = head_ptr;
        }
        many_nodes = 0;
    }

}

