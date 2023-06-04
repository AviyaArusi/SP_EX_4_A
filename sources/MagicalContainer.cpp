#include "MagicalContainer.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>


using namespace std;
namespace ariel 
{
    bool isPrime(int n) 
    {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i = i + 6)
        {
            if (n % i == 0 || n % (i + 2) == 0)
            {
                return false;
            }
        }
        return true;
    }

    pNode creatNode(int data)
    {
        pNode newNode = (pNode)malloc(NODE_SIZE);
        if(newNode == NULL)
        {
            printf("malloc error!\n");
            exit(1);
        }
        newNode->data = data;
        newNode->is_prime = isPrime(data);
        return newNode;
    }

    size_t MagicalContainer::size() const { return _elements.size(); }

    int MagicalContainer::contains(int element)
    {
        auto it = find_if(_elements.begin(), _elements.end(), [element](const pNode node) {
        return node->data == element;
    });

    if (it != _elements.end()) {
        return distance(_elements.begin(), it);
    }

    return -1;
    }

    void MagicalContainer::insertSorted(pNode newNode) 
    {
        auto it = lower_bound(_elements.begin(), _elements.end(), newNode,
            [](const pNode a, const pNode b) 
            {
                return a->data < b->data;
            }
            );

        _elements.insert(it, newNode);
        // _elements.push_back(newNode);
        // inplace_merge(_elements.begin(), _elements.end() - 1, _elements.end(),
        // [](const pNode a, const pNode b) {
        //     return a->data < b->data;
        // });
    }   

    void MagicalContainer::addPrimeElement(pNode newNode)
    {
        
        // newNode->nextPrime = nullptr;

        // if (_firstPrime == nullptr) 
        // {
        //     // If the list is empty, new node becomes the first and last node.
        //     _firstPrime = newNode;
        //     _lastPrime = newNode;
        // }
        // else if (newNode->data <= (_firstPrime)->data) 
        // {
        //     // If the new node's data is less than or equal to the first node's data, 
        //     // insert it at the beginning of the list.
        //     newNode->nextPrime = _firstPrime;
        //     _firstPrime = newNode;
        // }
        // else if (newNode->data >= (_lastPrime)->data) 
        // {
        //     // If the new node's data is greater than or equal to the last node's data, 
        //     // insert it at the end of the list.
        //     (_lastPrime)->nextPrime = newNode;
        //     _lastPrime = newNode;
        // }
        // else 
        // {
        //     // Otherwise, find the correct position in the list to insert the new node.
        //     pNode current = _firstPrime;
        //     while (current->nextPrime != nullptr && current->nextPrime->data < newNode->data) 
        //     {
        //         current = current->nextPrime;
        //     }
        //     newNode->nextPrime = current->nextPrime;
        //     current->nextPrime = newNode;
        // }

    }

    void MagicalContainer::removePrimeElement(size_t elementIndex)
    {
        pNode nodeToRemove = _elements.at(elementIndex);
        if(nodeToRemove->prevPrime != nullptr && nodeToRemove->nextPrime != nullptr)
        { 
            nodeToRemove->nextPrime->prevPrime = nodeToRemove->prevPrime;
            nodeToRemove->prevPrime->nextPrime = nodeToRemove->nextPrime;
        }
        else if(nodeToRemove->prevPrime != nullptr) { nodeToRemove->prevPrime->nextPrime = nullptr; }
        else { nodeToRemove->nextPrime->prevPrime = nullptr; }
    }


    void MagicalContainer::addElement(int element) 
    {
        if(contains(element) != -1) { return; }

        pNode newNode = creatNode(element);
        insertSorted(newNode);
        addPrimeElement(newNode);
        _size++;        
    }

    void MagicalContainer::removeElement(int element) 
    {
        if(_elements.size() == 0){ throw runtime_error("Can't remove from empty Container!\n"); }
        // If the element dont exsist in the vector.
        int index = contains(element);
        if( index == -1) { throw runtime_error("Invalid argumant!\n"); }

        pNode nodeToRemove = _elements.at((size_t)index);
        if(isPrime(element)) { removePrimeElement((size_t)index); }
        _elements.erase(_elements.begin() + index);
        free(nodeToRemove);
        _size--;
    }

    vector<pNode>& MagicalContainer::getElements(){ return _elements; }

    // IteratorBase

    MagicalContainer::IteratorBase::IteratorBase(MagicalContainer& container) : _container(container), _current(0) {}

    MagicalContainer::IteratorBase& MagicalContainer::IteratorBase::operator=(const MagicalContainer::IteratorBase& other) { return *this; }

    MagicalContainer::IteratorBase& MagicalContainer::IteratorBase::operator=( MagicalContainer::IteratorBase&& other) noexcept { return *this; }

    bool MagicalContainer::IteratorBase::operator==(const IteratorBase& other) const 
    {
        return _current == other._current;
    }

    bool MagicalContainer::IteratorBase::operator!=(const IteratorBase& other) const 
    {
        return !(*this == other);
    }

    bool MagicalContainer::IteratorBase::operator>(const IteratorBase& other) const 
    {
        return _current > other._current;
    }

    bool MagicalContainer::IteratorBase::operator<(const IteratorBase& other) const 
    {
        return _current < other._current;
    }

    int MagicalContainer::IteratorBase::operator*() 
    {
        return _container.getElements().at(_current)->data;
    }

    MagicalContainer::IteratorBase& MagicalContainer::IteratorBase::operator++() 
    {
        if(_current == _container.size() ) { throw out_of_range("Index out of range!\n"); }
        ++_current;
        return *this;
    }




    // AscendingIterator

    MagicalContainer::AscendingIterator::AscendingIterator( MagicalContainer& container) : IteratorBase(container) {}

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::begin() 
    {
        _current = 0;
        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::end() 
    {
        _current = _container.size();
        return *this;
    }


    // SideCrossIterator
    MagicalContainer::SideCrossIterator::SideCrossIterator( MagicalContainer& container) : IteratorBase(container), reverse(false) {}

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::begin() 
    {
        _current = 0;
        reverse = false;
        return *this;
    }

     MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::end() 
    {
        _current = 0;
        // _current = _container.size();
        reverse = true;
        return *this;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() 
    {
        return *this;
    }



    // PrimeIterator

    MagicalContainer::PrimeIterator::PrimeIterator( MagicalContainer& container) : IteratorBase(container) {}

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::begin() 
    {
        _current = 0;
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::end() 
    {
        _current = 0;
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() 
    {
        _current = 0;
        return *this;
    }


} // namespace ariel

