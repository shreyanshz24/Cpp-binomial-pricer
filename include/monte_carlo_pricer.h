#pragma once

#include <cmath>
#include <random>
#include <stdexcept>
#include <numeric>
#include "option_types.h"

template <OptionType TheOptionType, ExerciseType TheExerciseType>
class MonteCarloPricer
{
public:
    MonteCarloPricer(double S, double K, double r, double T, double sigma, int num_sims)
        : S_(S), K_(K), r_(r), T_(T), sigma_(sigma), num_sims_(num_sims)
    {
        if (S_ <= 0 || K_ <= 0 || T_ <= 0 || sigma_ <= 0 || num_sims_ <= 0)
        {
            throw std::invalid_argument("Invalid parameters for Monte Carlo pricing. Values must be positive.");
        }
    }
    double price() const
    {
        if constexpr (TheExerciseType == ExerciseType::American)
        {
            static_assert(TheExerciseType != ExerciseType::American, "The basic Monte Carlo Pricer is only valid for European-style options.");
        }
        else if constexpr (TheExerciseType == ExerciseType::European)
        {
            double drift = (r_ - 0.5 * sigma_ * sigma_) * T_;
            double vol_term = sigma_ * std::sqrt(T_);

            double sum_payoffs = 0.0;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::normal_distribution<> standard_normal_dist(0.0, 1.0);
            for (int i = 0; i < num_sims_; ++i)
            {

                double Z = standard_normal_dist(gen);
                double ST = S_ * std::exp(drift + vol_term * Z);
                double payoff = 0.0;
                if constexpr (TheOptionType == OptionType::Call)
                {
                    payoff = std::max(ST - K_, 0.0);
                }
                else
                {
                    payoff = std::max(K_ - ST, 0.0);
                }

                sum_payoffs += payoff;
            }
            double avg_payoff = sum_payoffs / num_sims_;
            return avg_payoff * std::exp(-r_ * T_);
        }
    }
    double getDelta(double dS = 0.01) const
    {
        if (dS <= 0)
        {
            throw std::invalid_argument("dS for Delta calculation must be positive.");
        }
        MonteCarloPricer pricerUp(S_ + dS, K_, r_, T_, sigma_, num_sims_);
        MonteCarloPricer pricerDown(S_ - dS, K_, r_, T_, sigma_, num_sims_);
        double priceUp = pricerUp.price();
        double priceDown = pricerDown.price();
        return (priceUp - priceDown) / (2.0 * dS);
    }

private:
    double S_, K_, r_, T_, sigma_;
    int num_sims_;
};