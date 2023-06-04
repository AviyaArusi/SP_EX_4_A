#pragma once

#include <vector>
#include <map>
#include <iterator>
#include <stdexcept>

#define NODE_SIZE sizeof(Node)

namespace ariel 
{
    typedef struct Node
    {
        int data = 0;
        bool is_prime = false;
        struct Node* prevPrime = NULL; // Hold the nextUp index
        struct Node* nextPrime = NULL;// Hold the next prime index
    }Node, *pNode;
    
    pNode creatNode(int data);


    class MagicalContainer 
    {
    private:
        std::vector<pNode> _elements;  // using a dynamic array for internal storage
        pNode _lastPrime;
        pNode _firstPrime;
        size_t _size = 0;

        void insertSorted(pNode newNode);
        void addPrimeElement(pNode newNode);
        void removePrimeElement(size_t elementIndex);
        int contains(int element);

    public:
        // Methods for MagicalContainer
        void addElement(int);
        void removeElement(int);
        size_t size() const;

        std::vector<pNode>& getElements();

    // Base class for all custom iterators
    class IteratorBase 
    {
    public:
        IteratorBase(MagicalContainer& container);
        IteratorBase(IteratorBase&) = default;
        IteratorBase& operator=(const IteratorBase&);
        IteratorBase(IteratorBase&&) noexcept = default;
        IteratorBase& operator=( IteratorBase&&) noexcept;
        virtual ~IteratorBase() = default;
        
        // Required operators for all iterators
        bool operator==(const IteratorBase&) const;
        bool operator!=(const IteratorBase&) const;
        bool operator>(const IteratorBase&) const;
        bool operator<(const IteratorBase&) const;
        int operator*();
        virtual IteratorBase& operator++();

        virtual IteratorBase& begin() = 0;
        virtual IteratorBase& end() = 0;

        MagicalContainer& _container;
        std::size_t _current;
    };


    // AscendingIterator
    class AscendingIterator : public IteratorBase 
    {
    public:
        AscendingIterator(MagicalContainer&);

        AscendingIterator& begin() override;
        AscendingIterator& end() override;
    };


    // SideCrossIterator
    class SideCrossIterator : public IteratorBase 
    {
    public:
        SideCrossIterator(MagicalContainer&);

        SideCrossIterator& begin() override;
        SideCrossIterator& end() override;

        SideCrossIterator& operator++() override;

    private:
        bool reverse;
    };


    // PrimeIterator
    class PrimeIterator : public IteratorBase 
    {
    public:
        PrimeIterator(MagicalContainer&);

        PrimeIterator& begin() override;
        PrimeIterator& end() override;

        PrimeIterator& operator++() override;
    };

};


} // namespace ariel

