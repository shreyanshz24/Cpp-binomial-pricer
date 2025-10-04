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
            double hold_value = discount * (p_ * values[j + 1] + (1.0 - p_) * values[j]);
            double S_ij = S_ * std::pow(u_, j) * std::pow(d_, i - j);
            double exercise_value = std::max(S_ij - K_, 0.0);
            values[j] = std::max(hold_value, exercise_value);
        }
    }
    return values[0];
}
double BinomialPricer::priceAmericanPut() const
{
    std::vector<double> values(N_ + 1);
    for (int j = 0; j <= N_; ++j)
    {
        double ST = S_ * std::pow(u_, j) * std::pow(d_, N_ - j);
        values[j] = std::max(K_ - ST, 0.0);
    }
    double discount = std::exp(-r_ * dt_);
    for (int i = N_ - 1; i >= 0; --i)
    {
        for (int j = 0; j <= i; ++j)
        {
            double hold_value = discount * (p_ * values[j + 1] + (1.0 - p_) * values[j]);
            double S_ij = S_ * std::pow(u_, j) * std::pow(d_, i - j);
            double exercise_value = std::max(K_ - S_ij, 0.0);
            values[j] = std::max(hold_value, exercise_value);
        }
    }
    return values[0];
}
double BinomialPricer::getDeltaCall() const
{
    double S_up = S_ * u_;
    double S_down = S_ * d_;
    double V_up = std::max(S_up - K_, 0.0);
    double V_down = std::max(S_down - K_, 0.0);
    double Delta = (V_up - V_down) / (S_up - S_down);
    return Delta;
}
double BinomialPricer::getDeltaPut() const
{
    double S_up = S_ * u_;
    double S_down = S_ * d_;
    double V_up = std::max(K_ - S_up, 0.0);
    double V_down = std::max(K_ - S_down, 0.0);
    double Delta = (V_up - V_down) / (S_up - S_down);
    return Delta;
}
double BinomialPricer::getGammaCall() const
{
    double S_uu = S_ * u_ * u_;
    double S_ud = S_ * u_ * d_;
    double S_dd = S_ * d_ * d_;
    double V_uu = std::max(S_uu - K_, 0.0);
    double V_ud = std::max(S_ud - K_, 0.0);
    double V_dd = std::max(S_dd - K_, 0.0);
    double Delta_up = (V_uu - V_ud) / (S_uu - S_ud);
    double Delta_down = (V_ud - V_dd) / (S_ud - S_dd);
    double S_up = S_ * u_;
    double S_down = S_ * d_;
    double Gamma = (Delta_up - Delta_down) / (S_up - S_down);
    return Gamma;
}
double BinomialPricer::getGammaPut() const
{
    double S_uu = S_ * u_ * u_;
    double S_ud = S_ * u_ * d_;
    double S_dd = S_ * d_ * d_;
    double V_uu = std::max(K_ - S_uu, 0.0);
    double V_ud = std::max(K_ - S_ud, 0.0);
    double V_dd = std::max(K_ - S_dd, 0.0);
    double Delta_up = (V_uu - V_ud) / (S_uu - S_ud);
    double Delta_down = (V_ud - V_dd) / (S_ud - S_dd);
    double S_up = S_ * u_;
    double S_down = S_ * d_;
    double Gamma = (Delta_up - Delta_down) / (S_up - S_down);
    return Gamma;
}