#pragma once
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "option_types.h"
template <OptionType TheOptionType, ExerciseType TheExerciseType>
class BinomialPricer
{
public:
    // Constructor: Takes market inputs and pre-calculates model parameters
    BinomialPricer(double S, double K, double r, double T, int N, double sigma)
        : S_(S), K_(K), r_(r), T_(T), N_(N), sigma_(sigma)
    {
        if (N_ <= 0 || S_ <= 0 || K_ < 0 || T_ < 0 || sigma_ < 0)
        {
            throw std::invalid_argument("Invalid parameters for option pricing.");
        }
        dt_ = T_ / N_;
        u_ = std::exp(sigma_ * std::sqrt(dt_));
        d_ = 1.0 / u_;
        double denom = u_ - d_;
        if (std::fabs(denom) < 1e-12)
        {
            p_ = (std::exp(r_ * dt_) > 1.0) ? 1.0 : 0.5;
        }
        else
        {
            p_ = (std::exp(r_ * dt_) - d_) / denom;
        }
        p_ = std::clamp(p_, 0.0, 1.0);
    }
    double price() const
    {
        std::vector<double> values(N_ + 1);
        for (int j = 0; j <= N_; ++j)
        {
            double ST = S_ * std::pow(u_, j) * std::pow(d_, N_ - j);
            if constexpr (TheOptionType == OptionType::Call)
            {
                values[j] = std::max(ST - K_, 0.0);
            }
            else
            { // Put
                values[j] = std::max(K_ - ST, 0.0);
            }
        }
        double discount = std::exp(-r_ * dt_);
        for (int i = N_ - 1; i >= 0; --i)
        {
            for (int j = 0; j <= i; ++j)
            {
                double hold_value = discount * (p_ * values[j + 1] + (1.0 - p_) * values[j]);
                if constexpr (TheExerciseType == ExerciseType::European)
                {
                    values[j] = hold_value;
                }
                else
                {
                    double current_ST = S_ * std::pow(u_, j) * std::pow(d_, i - j);
                    double exercise_value = 0.0;
                    if constexpr (TheOptionType == OptionType::Call)
                    {
                        exercise_value = std::max(current_ST - K_, 0.0);
                    }
                    else
                    {
                        exercise_value = std::max(K_ - current_ST, 0.0);
                    }
                    values[j] = std::max(hold_value, exercise_value);
                }
            }
        }
        return values[0];
    }
    double getDelta() const
    {
        if (N_ < 1)
            return 0.0;
        BinomialPricer pricerUp(S_ * u_, K_, r_, T_ - dt_, N_ - 1, sigma_);
        BinomialPricer pricerDown(S_ * d_, K_, r_, T_ - dt_, N_ - 1, sigma_);
        return (pricerUp.price() - pricerDown.price()) / (S_ * u_ - S_ * d_);
    }

private:
    double S_, K_, r_, T_, sigma_;
    int N_;
    double dt_, u_, d_, p_;
};