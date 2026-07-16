#ifndef STACK_HH
#define STACK_HH

#include <iostream>
#include <stdexcept>


/**********************************************************************************
 **********************************************************************************
 **********************************************************************************
 * THIS WAS MADE BY Eltrilicooo !!!
 * 
 * Follow me on Github PLEASEEEEE
 **********************************************************************************
 **********************************************************************************
 **********************************************************************************/



/**
 * @brief this is an implementation of a stack (LIFO - last in first out) using a simple linked list
 * and dinamic memory without maximum capacity
 * @tparam T is the type of data that the stack will store
 */

template<typename T>
class stack {
private:
    struct node
    {
        T value;
        node *next;
    };

    node *_top;
    int _size;


    /**
     * Pre: true
     * Post: Empties the stack
     */
    void clear() {
        while(!empty()) {
            pop();
        }
    }

    /**
     * Pre: The stack must be empty
     * Post: Copies "other"'s nodes in the actual stack
     */
    void copy_nodes(const stack& other) {
        if(other.empty()) return;

        node *other_aux = other._top;
        push(other_aux->value);
        other_aux = other_aux->next;
        node *act = _top;

        while(other_aux != nullptr) {
            node *new_node = new node;
            new_node->value = other_aux->value;
            new_node->next = nullptr;
            
            act->next = new_node;
            act = new_node;

            other_aux = other_aux->next;

            _size++;
        }
    }

public:

    stack() : _top(nullptr), _size(0) {}

    stack(const stack& other) : _top(nullptr), _size(0) {
        copy_nodes(other.top);
    }

    ~stack() {
        clear();
    }


    /**
     * Pre: True
     * Post: Returns if stack is empty
     */
    bool empty() const {
        return _size == 0;
    }

    /**
     * Pre: true
     * Post: returns the stack's size
     */
    int size() const {
        return _size;
    }

    /**
     * Pre: Stack must not be empty. Throws an underflow_error otherwise
     * Post: deletes the top element of the stack
     */
    void pop() {
        if(empty()) {
            throw std::underflow_error("Empty queue");
        }

        node *aux = _top;
        _top = aux->next;
        
        delete aux;
        _size--;
    }

    /**
     * Pre: true
     * Post: adds 'value' to the top of the stack
     */
    void push(const T& value) {
        node *new_node = new node;
        new_node->value = value;
        new_node->next = _top;
        _top = new_node;
        _size++;
    }

    /**
     * Pre: stack must not be empty. returns underflow_error otherwise
     * Post: returns the modifiable top value
     */
    T& top() {
        if(empty()) {
            throw std::underflow_error("Empty queue");
        }

        return _top->value;
    }

    /**
     * Pre: stack must not be empty. returns underflow_error otherwise
     * Post: returns the NOT modifiable top value
     */
    const T& top() const {
        if(empty()) {
            throw std::underflow_error("Empty queue");
        }

        return _top->value;
    }


    void operator=(const stack& other) {
        clear();
        copy_nodes(other);
    }



    bool operator==(const stack& other) const {
        if(this == &other) return true;
        if(_size != other._size) return false;
        if(_size == 0) return true;

        node *aux = _top;
        node *other_aux = other._top;

        while(aux != nullptr) {
            if(aux->value != other_aux->value) return false;
            aux = aux->next;
            other_aux = other_aux->next;
        }
        return true;
    }


    bool operator!=(const stack& other) {
        return !(operator==(other));
    }



    friend std::ostream& operator<<(std::ostream& os, const stack& s) {
        os << "<top> {";
        node *aux = s._top;
        while(aux != nullptr) {
            os << aux->value;
            if(aux->next != nullptr) os << ", ";
            aux = aux->next;
        }
        os << "} <bottom>";
        return os;
    }
};

#endif