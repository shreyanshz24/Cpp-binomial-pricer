High-Performance C++ Binomial Options Pricer
A robust, high-performance binomial options pricing engine written in modern C++17. This project provides a flexible and tested implementation of the Cox-Ross-Rubinstein (CRR) binomial model for valuing various types of options.

Features
Option Types: Prices both European and American style options.

Payoffs: Supports both Call and Put options.

Greeks Calculation: Computes key risk metrics including Delta and Gamma.

Modern C++: Built with modern C++17 features, focusing on clean design, efficiency, and robustness.

Templated Design: Core pricing logic is templated to allow for different numeric precision types (float, double).

Fully Tested: Comprehensive unit test suite built with the Google Test framework to ensure mathematical correctness and handle edge cases.

Professional Build System: Uses CMake for cross-platform compilation and test integration.

Core Theory: The Binomial Model
The project implements the Cox-Ross-Rubinstein (CRR) model, which discretizes time to model the evolution of a stock price. In each time step Δt, the stock price S can either move up by a factor of u or down by a factor of d.

The key is to calculate a "risk-neutral probability" p for the upward movement. This is the probability that would exist in a world where all assets are expected to grow at the risk-free rate r. The formulas are:

Up-factor: $ u = e^{\sigma\sqrt{\Delta t}} $

Down-factor: $ d = e^{-\sigma\sqrt{\Delta t}} = 1/u $

Risk-Neutral Probability: $ p = \frac{e^{r\Delta t} - d}{u - d} $

The option's value is then found by calculating its expected payoff at expiration and discounting it back to the present time, step by step, through the binomial tree. For American options, the possibility of early exercise is checked at each node.

Build and Usage
1. Build from Source
This project uses CMake. A C++17 compliant compiler is required.

# Clone the repository
git clone [https://github.com/shreyanshz24/Cpp-binomial-pricer.git](https://github.com/shreyanshz24/Cpp-binomial-pricer.git)
cd Cpp-binomial-pricer

# Configure the project with CMake
mkdir build
cd build
cmake ..

# Compile the code
make

This will create two executables in the build directory: pricer and runTests.

2. Run the Pricer
The pricer executable can be run from the command line with arguments.

# Example command-line usage from the build directory:
./pricer --option call --type american --S 100 --K 100 --r 0.05 --T 1.0 --N 500 --sigma 0.2

Example Output:

Option Type:      Call
Exercise:         American
Underlying (S):   100.00
Strike (K):       100.00
Maturity (T):     1.0 years
Risk-Free Rate (r): 5.00%
Steps (N):        500
Volatility (σ):   20.00%
--------------------
Computed Option Price: 10.43
Delta:                 0.62
Gamma:                 0.037

3. Run Unit Tests
The project uses Google Test, which is downloaded automatically.

# From the build directory, run the test suite:
ctest

If all tests pass, the GitHub Actions build badge at the top of this README will show ✅ passing.

Project Structure
Cpp-binomial-pricer/
├── .github/workflows/    # CI/CD pipeline (GitHub Actions)
│   └── cmake.yml
├── include/              # Header-only implementation of the templated class
│   └── binomial_pricer.h
├── src/                  # Core source files
│   └── main.cpp
├── tests/                # GoogleTest unit tests
│   └── main_test.cpp
├── .gitignore            # Specifies files for Git to ignore
├── CMakeLists.txt        # Build configuration
└── README.md             # This file

Example Integration in C++
To use the pricer library in your own C++ projects:

#include "include/binomial_pricer.h"
#include <iostream>

int main() {
    // Example: Create a pricer for an American Call
    BinomialPricer pricer(100.0, 100.0, 0.05, 1.0, 500, 0.2);

    std::cout << "American Call Price: " << pricer.priceAmericanCall() << std::endl;
    std::cout << "Delta: " << pricer.getDelta() << std::endl;
    std::cout << "Gamma: " << pricer.getGamma() << std::endl;

    return 0;
}

Contributing
Pull requests, issues, and feature suggestions are welcome! Fork the repo, make your changes, and submit a pull request.

License
This project is licensed under the MIT License. See the LICENSE file for details.
