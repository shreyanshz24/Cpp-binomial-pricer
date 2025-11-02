High-Performance C++ Options Pricer

A robust, high-performance C++17 library for pricing European and American options using both Binomial Tree and Monte Carlo methods.
This project provides flexible, efficient, and well-tested implementations for valuing various option types.

🚀 Features

Two Pricing Models:
Implements both the Cox-Ross-Rubinstein (CRR) Binomial Model and a Geometric Brownian Motion Monte Carlo simulation.

Option Types:
Prices European and American style options (Binomial) and European options (Monte Carlo).

Payoffs:
Supports both Call and Put options.

Greeks Calculation:
Computes key risk metrics including Delta.

Modern C++17:
Uses modern features (if constexpr, templates) for clean design and robustness.

Templated Architecture:
Core pricing classes are templated on OptionType and ExerciseType for compile-time polymorphism.

Fully Tested:
Includes a custom unit test suite to ensure mathematical correctness and handle edge cases.

Cross-Platform Build System:
Built using CMake, with CTest integration for testing.

📘 Core Theory
1. Binomial Model (Cox-Ross-Rubinstein)

The Binomial Model discretizes time to model the evolution of a stock price.
In each time step In each time step Δ𝑡, the stock price S can either move up by a factor 𝑢 or down by a factor 𝑑

Formulas:

Up factor: u = exp(σ * sqrt(Δt))

Down factor: d = exp(-σ * sqrt(Δt))

Risk-neutral probability: p = (exp(r * Δt) - d) / (u - d)

The option’s value is calculated by discounting the expected payoff step-by-step through the tree.
For American options, early exercise is checked at every node.

2. Monte Carlo Model

The Monte Carlo model simulates thousands of random paths for the asset price using Geometric Brownian Motion (GBM): S_T = S_0 * exp((r - 0.5 * σ^2) * T + σ * sqrt(T) * Z)
where
Z ~ N(0, 1) → (a random number from the standard normal distribution)

Steps:

Compute the payoff for each simulated path (e.g. 
maxpayoff = max(S_T - K, 0)

Take the average of all simulated payoffs.
Discount the average payoff to present value using price = exp(-r * T) * average(payoff)

⚙️ Build and Usage
1. Clone the Repository
git clone https://github.com/shreyanshz24/Cpp-binomial-pricer.git
cd Cpp-binomial-pricer

2. Configure the Project with CMake
cmake -B build -S .

3. Compile the Code
cmake --build build


This will generate two executables inside the build/ directory:

pricer — the demo executable

runTests — the unit test suite

4. Run the Pricer Demo

From the project root:

.\build\pricer.exe


Example Output:

--- Binomial ---
European Call Price: 9.71038
European Put Price:  6.76193
American Put Price:  7.47345
Delta of the Call:   0.63881

--- Monte Carlo ---
European Call Price: 9.63660
Delta of the Call:   -0.85484

5. Run Unit Tests

From the build/ directory:

ctest --output-on-failure


This runs the runTests executable and shows detailed results.
All tests passing will mark your CI badge ✅ passing on GitHub Actions.

📂 Project Structure
Cpp-binomial-pricer/
├── .github/workflows/
│   └── cmake.yml              # CI/CD pipeline (GitHub Actions)
├── include/
│   ├── binomial_pricer.h      # Header-only Binomial Pricer
│   ├── monte_carlo_pricer.h   # Header-only Monte Carlo Pricer
│   └── option_types.h         # Shared enum definitions
├── src/
│   └── main.cpp               # Demo executable
├── tests/
│   └── main_test.cpp          # Custom unit tests
├── .gitignore
├── CMakeLists.txt             # Build configuration
└── README.md                  # Project documentation

💻 Example Integration in Your Project

Include the headers and use the templated pricer classes:

#include "include/binomial_pricer.h"
#include "include/monte_carlo_pricer.h"
#include "include/option_types.h"
#include <iostream>
#include <iomanip>

int main() {
    std::cout << std::fixed << std::setprecision(5);

    // Example 1: Binomial Pricer for an American Put
    BinomialPricer<OptionType::Put, ExerciseType::American> amerPut(50.0, 52.0, 0.05, 2.0, 1000, 0.3);
    std::cout << "Binomial American Put Price: " << amerPut.price() << std::endl;
    std::cout << "Delta: " << amerPut.getDelta() << std::endl;

    // Example 2: Monte Carlo Pricer for a European Call
    MonteCarloPricer<OptionType::Call, ExerciseType::European> mcEuroCall(50.0, 52.0, 0.05, 2.0, 0.3, 200000);
    std::cout << "Monte Carlo European Call Price: " << mcEuroCall.price() << std::endl;
    std::cout << "Delta: " << mcEuroCall.getDelta() << std::endl;

    return 0;
}

🤝 Contributing

Contributions are welcome!

Fork the repo

Create a new branch

Commit your changes

Submit a Pull Request

Feature suggestions and issue reports are also appreciated.

📜 License

This project is licensed under the MIT License.
See the LICENSE file for details.
