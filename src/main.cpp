#include "binomial_pricer.h"
#include "monte_carlo_pricer.h"
#include "option_types.h"
#include <iostream>
#include <stdexcept>
#include <iomanip> // Added for formatting

int main()
{
    // Set precision for currency
    std::cout << std::fixed << std::setprecision(5);

    try
    {
        BinomialPricer<OptionType::Call, ExerciseType::European> euroCall(50.0, 52.0, 0.05, 2.0, 1000, 0.3);
        BinomialPricer<OptionType::Put, ExerciseType::European> euroPut(50.0, 52.0, 0.05, 2.0, 1000, 0.3);
        BinomialPricer<OptionType::Put, ExerciseType::American> amerPut(50.0, 52.0, 0.05, 2.0, 1000, 0.3);

        std::cout << "--- Binomial ---" << std::endl;
        std::cout << "European Call Price: " << euroCall.price() << std::endl;
        std::cout << "European Put Price:  " << euroPut.price() << std::endl;
        std::cout << "American Put Price:  " << amerPut.price() << std::endl;
        std::cout << "Delta of the Call:   " << euroCall.getDelta() << std::endl;

        MonteCarloPricer<OptionType::Call, ExerciseType::European> mcEuroCall(50.0, 52.0, 0.05, 2.0, 0.3, 200000);

        std::cout << "\n--- Monte Carlo ---" << std::endl;
        std::cout << "European Call Price: " << mcEuroCall.price() << std::endl;
        std::cout << "Delta of the Call:   " << mcEuroCall.getDelta() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}