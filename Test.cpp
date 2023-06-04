#include <iostream>
#include "doctest.h"
#include "sources/MagicalContainer.hpp"


using namespace std;
using namespace ariel;

TEST_SUITE("MagiclContainer tests")
{
    TEST_CASE("MagicalContainer constructor") 
    {
        CHECK_NOTHROW(MagicalContainer container);
        MagicalContainer container;
        CHECK(container.size() == 0);
        
    }

    TEST_CASE("MagicalContainer addElement and size") 
    {
        MagicalContainer container;
        CHECK(container.size() == 0);
        container.addElement(1);
        CHECK(container.size() == 1);
    }

    TEST_CASE("MagicalContainer addElement duplicate") 
    {
        MagicalContainer container;
        container.addElement(1);
        container.addElement(1);
        CHECK(container.size() == 1);
    }

    TEST_CASE("MagicalContainer removeElement") 
    {
        MagicalContainer container;
        CHECK(container.size() == 0);
        container.addElement(1);
        CHECK(container.size() == 1);
        container.removeElement(1);
        CHECK(container.size() == 0);
    }


    TEST_CASE("MagicalContainer removeElement Empty & nonexistent") 
    {
        MagicalContainer container;
        // Empty Container
        CHECK_THROWS_AS(container.removeElement(1), runtime_error); 
        container.addElement(1);
        CHECK_THROWS_AS(container.removeElement(2), runtime_error);
        CHECK(container.size() == 1);
    }
}

TEST_SUITE("AscendingIterator test")
{
    TEST_CASE("AscendingIterator empty")
    {
        MagicalContainer container;
        MagicalContainer::AscendingIterator ascIter(container);
        CHECK_EQ(ascIter.begin(), ascIter.end());
    }

    TEST_CASE("AscendingIterator single element") 
    {
        MagicalContainer container;
        container.addElement(1);
        MagicalContainer::AscendingIterator ascIter(container);
        CHECK(*ascIter.begin() == 1);
        CHECK(*ascIter.end() == 1);
    }

    TEST_CASE("AscendingIterator ++") 
    {
        MagicalContainer container;
        container.addElement(3);
        container.addElement(13);
        container.addElement(11);
        MagicalContainer::AscendingIterator ascIter(container);
        // checking that the iterator is ordered
        CHECK(*ascIter == 3);
        ++ascIter;
        CHECK(*ascIter == 11);
        ++ascIter;
        CHECK(*ascIter == 13);
        ++ascIter;

        // checking that we can't use operator++ after the end of the Container
        CHECK_THROWS_AS(++ascIter, out_of_range);
        
    }
        
}

TEST_SUITE("SideCrossIterator test")
{
    TEST_CASE("SideCrossIterator test") 
    {
        MagicalContainer container;
        container.addElement(2);
        container.addElement(9);
        container.addElement(4);
        MagicalContainer::SideCrossIterator crossIter(container);
    }
    TEST_CASE("SideCrossIterator empty") 
    {
        MagicalContainer container;
        MagicalContainer::SideCrossIterator crossIter(container);
        CHECK_EQ(crossIter.begin(), crossIter.end());
    }

    TEST_CASE("SideCrossIterator single element") 
    {
        MagicalContainer container;
        container.addElement(1);
        MagicalContainer::SideCrossIterator crossIter(container);
        CHECK(*crossIter.begin() == 1);
        CHECK(*crossIter.end() == 1);
    }

    TEST_CASE("SideCrossIterator odd number of elements") 
    {
        MagicalContainer container;
        container.addElement(1);
        container.addElement(2);
        container.addElement(3);
        MagicalContainer::SideCrossIterator crossIter(container);
    }
    
    TEST_CASE("SideCrossIterator ++") 
    {
        MagicalContainer container;
        container.addElement(2);
        container.addElement(23);
        container.addElement(7);
        container.addElement(9);
        MagicalContainer::SideCrossIterator crossIter(container);
        // checking that the iterator is ordered
        CHECK(*crossIter == 2);
        ++crossIter;
        CHECK(*crossIter == 23);
        ++crossIter;
        CHECK(*crossIter == 7);
        ++crossIter;
        CHECK(*crossIter == 9);
        ++crossIter;

        // checking that we can't use operator++ after the end of the Container
        CHECK_THROWS_AS(++crossIter, out_of_range); 
    }
}

TEST_SUITE("PrimeIterator test")
{
    TEST_CASE("PrimeIterator test") 
    {
        MagicalContainer container;
        container.addElement(1);
        container.addElement(2);
        container.addElement(3);
        CHECK_NOTHROW(MagicalContainer::PrimeIterator primeIter(container));
    }

    TEST_CASE("PrimeIterator empty") 
    {
        MagicalContainer container;
        MagicalContainer::PrimeIterator primeIter(container);
        CHECK_EQ(primeIter.begin(), primeIter.end());
    }

    TEST_CASE("PrimeIterator single element non-prime") 
    {
        MagicalContainer container;
        container.addElement(7);
        MagicalContainer::PrimeIterator primeIter(container);
        CHECK(primeIter.begin() == primeIter.end());
    }

    TEST_CASE("PrimeIterator single element prime") 
    {
        MagicalContainer container;
        container.addElement(2);
        MagicalContainer::PrimeIterator primeIter(container);
        CHECK(*primeIter.begin() == 2);
        CHECK(*primeIter.end() == 2);

    }

    TEST_CASE("PrimeIterator ++") 
    {
        MagicalContainer container;
        container.addElement(4);
        container.addElement(11);
        container.addElement(3);
        container.addElement(18);
        MagicalContainer::PrimeIterator primeIter(container);
        // checking that the iterator is ordered
        CHECK(*primeIter == 3);
        ++primeIter;
        CHECK(*primeIter == 11);
        ++primeIter;

        // checking that we can't use operator++ after the end of the Container
        CHECK_THROWS_AS(++primeIter, out_of_range); 
    }

}


TEST_SUITE("Iterator opertors - check once the base class for all the Iterators")
{
    TEST_CASE("Comparison methods")
    {
        MagicalContainer container;
        container.addElement(12);
        container.addElement(1);
        container.addElement(18);
        container.addElement(29);
        container.addElement(33);
        container.addElement(35);

        MagicalContainer::AscendingIterator ascIter1(container);
        MagicalContainer::AscendingIterator ascIter2(container);

        // equality
        CHECK(ascIter1 == ascIter2);
            ++ascIter1;
        CHECK_FALSE(ascIter1 == ascIter2);

        CHECK(ascIter1 != ascIter2);
        ++ascIter2;
        CHECK_FALSE(ascIter1 != ascIter2);
        ++ascIter1;
        CHECK(ascIter1 > ascIter2);
        CHECK_FALSE(ascIter2 > ascIter1);
        ++ascIter2;
        ++ascIter2;
        ++ascIter2;
        CHECK(ascIter1 < ascIter2);
        CHECK_FALSE((ascIter2 < ascIter1));
    }

    TEST_CASE("2 difference iterators all the options for all 3 Iterators")
    {
        MagicalContainer container;
        container.addElement(20);
        container.addElement(6);
        container.addElement(10);
        container.addElement(3);

        MagicalContainer::AscendingIterator ascIter(container);
        MagicalContainer::SideCrossIterator crossIter(container);
        MagicalContainer::PrimeIterator primeIter(container);

        bool exeption;

        CHECK_THROWS(exeption = (ascIter == crossIter));
        CHECK_THROWS(exeption = (ascIter == primeIter));        
        CHECK_THROWS(exeption = (primeIter == crossIter));

        CHECK_THROWS(exeption = (ascIter != crossIter));
        CHECK_THROWS(exeption = (ascIter != primeIter));
        CHECK_THROWS(exeption = (primeIter != crossIter));

        CHECK_THROWS(exeption = (ascIter > crossIter));
        CHECK_THROWS(exeption = (ascIter > primeIter)); 
        CHECK_THROWS(exeption = (primeIter > ascIter)); 

        CHECK_THROWS(exeption = (ascIter < crossIter));
        CHECK_THROWS(exeption = (ascIter < primeIter)); 
        CHECK_THROWS(exeption = (primeIter < ascIter)); 

        CHECK_THROWS(exeption = (ascIter < crossIter));  
        CHECK_THROWS(exeption = (primeIter < ascIter));  
        CHECK_THROWS(exeption = (crossIter < primeIter)); 

        CHECK_THROWS(exeption = (ascIter > crossIter));  
        CHECK_THROWS(exeption = (primeIter > ascIter));  
        CHECK_THROWS(exeption = (crossIter > primeIter)); 
    }


}
