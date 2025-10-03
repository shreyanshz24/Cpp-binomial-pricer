#include <cmath>
class BinomialPricer
{
public:
    BinomialPricer(double S, double K, double r, double T, int N, double sigma);
    double priceEuropeanCall() const;
    double priceEuropeanPut() const;
    double priceAmericanCall() const;
    double priceAmericanPut() const;

private:
    double S_, K_, r_, T_, sigma_;
    int N_;
    double dt_, u_, d_, p_;
};