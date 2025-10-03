#include "../include/binomial_pricer.h"
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>

BinomialPricer::BinomialPricer(double S, double K, double r, double T, int N, double sigma)
    : S_(S), K_(K), r_(r), T_(T), N_(N), sigma_(sigma)
{
    if (N_ <= 0)
    {
        throw std::invalid_argument("N must be greater than 0");
    }
    if (S_ <= 0 || K_ <= 0)
    {
        throw std::invalid_argument("S and K must be greater than 0");
    }
    if (sigma_ < 0 || T_ < 0)
    {
        throw std::invalid_argument("sigma and T must be >= 0");
    }

    dt_ = T_ / N_;
    if (dt_ == 0)
    {
        u_ = 1.0;
        d_ = 1.0;
        p_ = 0.5;
    }
    else
    {
        u_ = std::exp(sigma_ * std::sqrt(dt_));
        d_ = 1.0 / u_;
        double denom = u_ - d_;
        if (std::fabs(denom) < 1e-12)
        {
            p_ = 0.5;
        }
        else
        {
            p_ = (std::exp((r_ - 0.0) * dt_) - d_) / (u_ - d_);
        }
    }
    p_ = std::clamp(p_, 0.0, 1.0);
    std::cout << "dt=" << dt_ << " u=" << u_ << " d=" << d_ << " p=" << p_ << "\n";
}
double BinomialPricer::priceEuropeanCall() const
{
    std::vector<double> values(N_ + 1);
    for (int j = 0; j <= N_; ++j)
    {
        double ST = S_ * std::pow(u_, j) * std::pow(d_, N_ - j);
        values[j] = std::max(ST - K_, 0.0);
    }
    double discount = std::exp(-r_ * dt_);
    for (int i = N_ - 1; i >= 0; --i)
    {
        for (int j = 0; j <= i; ++j)
        {
            values[j] = (p_ * values[j + 1] + (1.0 - p_) * values[j]) * discount;
        }
    }
    return values[0];
}
double BinomialPricer::priceEuropeanPut() const
{
    std::vector<double> values(N_ + 1);
    double discount = std::exp(-r_ * dt_);
    for (int j = 0; j <= N_; ++j)
    {
        double ST = S_ * std::pow(u_, j) * std::pow(d_, N_ - j);
        values[j] = std::max(K_ - ST, 0.0);
    }
    for (int i = N_ - 1; i >= 0; --i)
    {
        for (int j = 0; j <= i; ++j)
        {
            values[j] = (p_ * values[j + 1] + (1.0 - p_) * values[j]) * discount;
        }
    }

    return values[0];
}

double BinomialPricer::priceAmericanCall() const
{
    return 0.0;
}

double BinomialPricer::priceAmericanPut() const
{
    return 0.0;
}