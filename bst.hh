/*************************************************************************************************************
 *************************************************************************************************************
 *************************************************************************************************************
 * This was made by Eltrilicooo
 * 
 * FOLLOW ME ON GITHUB PLEASEEEE
 */



/**
 * THIS took me like 4 days, so im kind if proud (because i finished it) and not proud (because
 * it's an easy thing that was really difficult for me)
 * 
 * but even with that I still wanna keep doing these things. I don't know what I'll do next, but I'll keep doing
 * BTW right now I'm listening to "Disobidient" from Steven Universe. Peak song
 * 
 * and now, at 04:00, i have to comment every method... :sob_emoji:
 */






#ifndef BST_HH
#define BST_HH

#include <iostream>
#include <stdexcept>

#include "stack.hh"

template<typename T>
class bst {
private:
    struct node
    {
        T value;
        node *left;
        node *right;
    };
    node *_root;
    int _size;

    /**
     * Pre: true
     * Post: inserts the new value in the BST
     */
    void insert(node *&local_root, const T& value) {
        if(local_root == nullptr) {
            node* new_node = new node;
            new_node->value = value;
            new_node->left = new_node->right = nullptr;
            local_root = new_node;

            _size++;

            return;
        }

        if(local_root->value < value) {
            insert(local_root->right, value);
            return;
        }

        if(local_root->value > value) {
            insert(local_root->left, value);
            return;
        }

        /**
         * If none of the others were true, it means we are inserting an already existen value
         */
        throw std::invalid_argument("Key already existed in BST");
    }

    /**
     * Pre: true
     * Post: returns if "value" is in the BST
     */
    bool search(const node *local_node, const T& value) const {
        if(local_node == nullptr) return false;

        if(local_node->value == value) return true;

        if(local_node->value < value) return search(local_node->right, value);

        return search(local_node->left, value);
    }

    /**
     * Pre: true
     * Post: returns BST's height
     */
    int height(const node *local_node) const {
        if(local_node == nullptr) return 0;
        int h_left = 1 + height(local_node->left);
        int h_right = 1 + height(local_node->right);

        return ((h_left > h_right) ? h_left : h_right);
    }

    /**
     * Pre: true
     * Post: deletes every node in the BST
     */
    void clear(node *&local_node) {
        if(local_node == nullptr) return;

        clear(local_node->left);
        clear(local_node->right);

        delete local_node;
        local_node = nullptr;
    }

    /**
     * Pre: BST can't be empty
     * Post: returns biggest value in BST
     */
    node* search_biggest(node* local_node) {
        if(local_node->right == nullptr) return local_node;

        return search_biggest(local_node->right);
    }

    /**
     * Pre: true
     * Post: removes "value" from BST
     */
    void remove(node *&local_node, const T& value) {
        if(local_node == nullptr) throw std::underflow_error("Key not found in BST");

        if(local_node->value < value) {
            remove(local_node->right, value);
            return;
        }

        if(local_node->value > value) {
            remove(local_node->left, value);
            return;
        }

        // If local_node has only a left child
        if(local_node->right == nullptr) {
            node *aux = local_node;
            local_node = local_node->left;
            delete aux;
            return;
        }

        // If local_node has only a right child
        if(local_node->left == nullptr) {
            node *aux = local_node;
            local_node = local_node->right;
            delete aux;
            return;
        }

        // Otherwise, local_node has a left and a right child
        node *biggest_left = search_biggest(local_node->left);
        local_node->value = biggest_left->value;
        remove(local_node->left, biggest_left->value);
    }

    /**
     * Pre: "local_node" must be a valid, newly allocated node
     * Post: copies "n" into "local_node"
     */
    void copy(node *n, node *local_node) {
        local_node->value = n->value;
        local_node->left = nullptr;
        local_node->right = nullptr;

        if(n->left != nullptr) {
            node *left_child = new node;
            local_node->left = left_child;
            copy(n->left, left_child);
        }

        if(n->right != nullptr) {
            node *right_child = new node;
            local_node->right = right_child;
            copy(n->right, right_child);
        }
    }
public:
    bst() : _root(nullptr), _size(0) {}

    ~bst() {
        clear();
    }

    /**
     * Pre: true
     * Post: clears BST
     */
    void clear() {
        clear(_root);
        _size = 0;
    }

    /**
     * Pre: true
     * Post: returns true if BST is empty, false if otherwise
     */
    bool empty() {
        return _size == 0;
    }

    /**
     * Pre: true
     * Post: returns BST's _size
     */
    int size() const {
        return _size;
    }

    /**
     * Pre: true
     * Post: inserts "value" in the BST
     */
    void insert(const T& value) {
        insert(_root, value);
    }

    /**
     * Pre: true
     * Post: removes "value" from BST
     */
    void remove(const T& value) {
        if(_size == 0) throw std::underflow_error("Key not found in BST");
        remove(_root, value);
    }

    /**
     * Pre: true
     * Post: returns if "value" is in the BST
     */
    bool search(const T& value) const {
        return search(_root, value);
    }

    /**
     * Pre: true
     * Post: returns BST's height
     */
    int height() const {
        return height(_root);
    }


    class iterator {
    private:
        stack<node*> _stack;
        node* _root;

        /**
         * Pre: true
         * Post: pushes every left child into _stack
         */
        void push_left(node *n) {
            while(n != nullptr) {
                _stack.push(n);
                n = n->left;
            }
        }

        /**
         * Pre: true
         * Post: pushes every right child into _stack
         */
        void push_right(node *n) {
            while(n != nullptr) {
                _stack.push(n);
                n = n->right;
            }
        }

    public:

        iterator() : _stack(), _root(nullptr) {}

        iterator(node *root) : _stack(), _root(root) {
            push_left(root);
        }

        iterator(iterator& it) : _stack(), _root(nullptr) {
            operator=(it);
        }

        T operator*() const {
            return _stack.top()->value;
        }
    
        iterator& operator++() {
            node *aux = _stack.top();
            _stack.pop();
            
            if(aux->right != nullptr) push_left(aux->right);

            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            node *aux = _stack.top();
            _stack.pop();
            
            if(aux->left != nullptr) push_right(aux->left);

            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const iterator& other) const {
            return _stack == other._stack;
        }

        bool operator!=(const iterator& other) const {
            return !(*this==other);
        }

        iterator& operator=(const iterator& other) {
            if(this != &other) {
                _root = other._root;
                _stack = other._stack;
            }
            return *this;
        }

        const T* operator->() const {
            return &(_stack.top()->value);
        }
    };


    /**
     * Pre: true
     * Post: returns the beggining of the BST
     */
    iterator begin() {
        return iterator(_root);
    }

    /**
     * Pre: true
     * Post: returns the end of the BST
     */
    iterator end() {
        return iterator(nullptr);
    }


    bst& operator=(const bst& other) {
        clear();
        
        if(other._root == nullptr) {
            return *this;
        }

        _root = new node;
        copy(other._root, _root);
        _size = other._size;

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, bst& b) {
        const int size = b.size();
        os << "[";
        auto it = b.begin();
        for(int i = 0; i < size; i++) {
            os << *it;
            if(i + 1 != size) os << ", ";
            ++it;
        }
        os << "]";
        return os;
    }
};

#endif


//I hope you liked it. And never forget to love everyone, even if they don't love you back
//No one deserves to be lonely

//And, finally, FREE PALESTINE!