#include "binomial_pricer.h"
#include "option_types.h"
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
int test_count = 0;
int pass_count = 0;

#define EXPECT_NEAR(val1, val2, abs_error)                                          \
    do                                                                              \
    {                                                                               \
        test_count++;                                                               \
        if (std::abs((val1) - (val2)) <= (abs_error))                               \
        {                                                                           \
            pass_count++;                                                           \
            std::cout << "[ \033[32mPASSED\033[0m ] " << __FUNCTION__ << std::endl; \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            std::cout << "[ \033[31mFAILED\033[0m ] " << __FUNCTION__ << std::endl; \
            std::cout << "  Expected value near: " << (val2) << std::endl;          \
            std::cout << "  Got:                 " << (val1) << std::endl;          \
        }                                                                           \
    } while (0)

#define EXPECT_THROW(statement, exception_type)                                                                                                  \
    do                                                                                                                                           \
    {                                                                                                                                            \
        test_count++;                                                                                                                            \
        try                                                                                                                                      \
        {                                                                                                                                        \
            statement;                                                                                                                           \
            std::cout << "[ \033[31mFAILED\033[0m ] " << __FUNCTION__ << " - Expected exception '" #exception_type "' not thrown." << std::endl; \
        }                                                                                                                                        \
        catch (const exception_type &e)                                                                                                          \
        {                                                                                                                                        \
            pass_count++;                                                                                                                        \
            std::cout << "[ \033[32mPASSED\033[0m ] " << __FUNCTION__ << std::endl;                                                              \
        }                                                                                                                                        \
        catch (...)                                                                                                                              \
        {                                                                                                                                        \
            std::cout << "[ \033[31mFAILED\033[0m ] " << __FUNCTION__ << " - Wrong exception type thrown." << std::endl;                         \
        }                                                                                                                                        \
    } while (0)

void PricerTest_EuropeanCallKnownValue()
{
    BinomialPricer<OptionType::Call, ExerciseType::European> pricer(50.0, 52.0, 0.05, 2.0, 1000, 0.3);
    double price = pricer.price();
    EXPECT_NEAR(price, 9.71, 0.03);
}

void PricerTest_EuropeanPutKnownValue()
{
    BinomialPricer<OptionType::Put, ExerciseType::European> pricer(50.0, 52.0, 0.05, 2.0, 1000, 0.21);
    double price = pricer.price();
    EXPECT_NEAR(price, 4.36, 0.02);
}

void PricerTest_InvalidParameters()
{
    EXPECT_THROW((BinomialPricer<OptionType::Call, ExerciseType::European>(0.0, 52.0, 0.05, 2.0, 100, 0.3)), std::invalid_argument);
    EXPECT_THROW((BinomialPricer<OptionType::Call, ExerciseType::European>(50.0, 52.0, 0.05, 2.0, 0, 0.3)), std::invalid_argument);
}

int main()
{
    std::cout << "--- Running Pricer Tests ---" << std::endl;
    PricerTest_EuropeanCallKnownValue();
    PricerTest_EuropeanPutKnownValue();
    PricerTest_InvalidParameters();

    std::cout << "----------------------------------" << std::endl;
    std::cout << "Tests Summary: " << pass_count << "/" << test_count << " passed." << std::endl;

    return (test_count - pass_count == 0) ? 0 : 1;
}
