#include <iostream>
#include "../include/binomial_pricer.h"

int main()
{
    try
    {
        BinomialPricer myPricer(50.0, 52.0, 0.05, 2.0, 1000, 0.3);
        std::cout << "European Call Price: " << myPricer.priceEuropeanCall() << std::endl;
        std::cout << "European Put Price: " << myPricer.priceEuropeanPut() << std::endl;
        std::cout << "American Call Price: " << myPricer.priceAmericanCall() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}