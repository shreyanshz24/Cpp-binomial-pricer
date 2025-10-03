#include "../include/binomial_pricer.h"
#include <gtest/gtest.h>

TEST(PriceTest, EuropeanCallKnownValue)
{
    BinomialPricer pricer(50.0, 52.0, 0.05, 2.0, 1000, 0.3);
    double price = pricer.priceEuropeanCall();
    EXPECT_NEAR(price, 9.71, 0.2);
}

TEST(PriceTest, EuropeanPutKnownValue)
{
    BinomialPricer pricer(50.0, 52.0, 0.05, 2.0, 1000, 0.3);
    double price = pricer.priceEuropeanPut();
    EXPECT_GT(price, 0.0);
    EXPECT_LT(price, 10.0);
}

TEST(PriceTest, InvalidParameters)
{
    EXPECT_THROW(BinomialPricer(0.0, 52.0, 0.05, 2.0, 100, 0.3), std::invalid_argument);
    EXPECT_THROW(BinomialPricer(50.0, 52.0, 0.05, 2.0, 0, 0.3), std::invalid_argument);
}