#ifndef QUEUE_HH
#define QUEUE_HH

#include <stdexcept>
#include <iostream>


/**
 * @brief this is an implementation of a queue (FIFO - first in first out) using a simple linked list
 * using dinamic memory without maximum capacity
 * @tparam T is the type of data that the queue will store
 */

template<typename T>
class queue {
private:

    struct node
    {
        T value;
        node *next;
    };

    int _size;
    node *first;
    node *last;


    /**
     * Pre: true
     * Post: Empties the queue
     */
    void clear() {
        while(!empty()) {
            pop();
        }
    }

    /**
     * this funcion copies every node from "other" to the actual queue
     */
    void copy_nodes(const queue& other) {
        node *aux = other.first;

        while(aux != nullptr) {
            push(aux->value);
            aux = aux->next;
        }
    }

public:

    queue() : first(nullptr), last(nullptr), _size(0) {}

    queue(const queue& other) : first(nullptr), last(nullptr), _size(0) {
        copy_nodes(other);
    }

    ~queue() {
        clear();
    }

    /**
     * Pre: true
     * Post: Returns true if queue is empty, false if otherwise
     */
    bool empty() const {
        return _size == 0;
    }

    /**
     * Pre: true
     * Post: Returns the size of the queue
     */
    int size() const {
        return _size;
    }

    /**
     * Pre: Queue must not be empty
     * Post: Deletes first node
     */
    void pop() {
        if(empty()) {
            throw std::underflow_error("Empty queue");
        }

        node *to_delete = first;
        first = to_delete->next;
        delete to_delete;

        if(first == nullptr) last = nullptr;
        _size--;
    }

    /**
    * Pre: true
    * Post: Adds a new node with this value to the last position
    */
    void push(const T& value) {
        node *new_node = new node;
        new_node->value = value;
        new_node->next = nullptr;
        
        if(empty()) {
            first = last = new_node;
            _size++;
            return;
        }

        last->next = new_node;
        last = new_node;
        _size++;
    }

    /**
    * Pre: Queue must not be empty
    * Post: Returns the modifiable first node
    */
    T& front() {
        if(empty()) {
            throw std::underflow_error("Empty queue");
        }

        return first->value;
    }

    /**
    * Pre: Queue must not be empty
    * Post: Returns the NOT modifiable first node
    */
    const T& front() const {
        if(empty()) {
            throw std::underflow_error("Empty queue");
        }

        return first->value;
    }


    bool operator==(const queue& other) const {
        if(this->_size != other._size) return false;
        if(this->_size == 0) return true;

        node *aux_this = this->first;
        node *aux_other = other.first;

        for(int i = 0; i < _size; i++) {
            if(aux_this->value != aux_other->value) return false;
            aux_this = aux_this->next;
            aux_other = aux_other->next;
        }

        return true;
    }

    bool operator!=(const queue& other) const {
        return !(operator==(other));
    }

    
    void operator=(const queue& other) {
        if(this == &other) return;

        clear();

        copy_nodes(other);
    }


    friend std::ostream& operator<<(std::ostream& os, const queue& q) {
        os << "<first> {";

        node *aux = q.first;
        for(int i = 0; i < q._size; i++) {
            os << aux->value;
            if(i + 1 < q._size) { //if this is not the last element we add ", "
                os << ", ";
            }
            aux = aux->next;
        }
        os << "} <last>";
        return os;
    }
};

#endif