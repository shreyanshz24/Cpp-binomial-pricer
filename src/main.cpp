#include <iostream>
#include "../include/binomial_pricer.h"

int main()
{
    try
    {
        BinomialPricer<OptionType::Call, ExerciseType::European> euroCall(50.0, 52.0, 0.05, 2.0, 1000, 0.3);
        BinomialPricer<OptionType::Put, ExerciseType::European> euroPut(50.0, 52.0, 0.05, 2.0, 1000, 0.3);
        BinomialPricer<OptionType::Call, ExerciseType::American> amerCall(50.0, 52.0, 0.05, 2.0, 1000, 0.3);
        BinomialPricer<OptionType::Put, ExerciseType::American> amerPut(50.0, 52.0, 0.05, 2.0, 1000, 0.3);

        std::cout << "European Call Price: " << euroCall.price() << std::endl;
        std::cout << "European Put Price:  " << euroPut.price() << std::endl;
        std::cout << "American Call Price: " << amerCall.price() << std::endl;
        std::cout << "American Put Price:  " << amerPut.price() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
