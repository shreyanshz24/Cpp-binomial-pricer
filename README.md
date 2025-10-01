# High-Performance C++ Binomial Options Pricer

[![Build Status](https://github.com/shreyanshz24/Cpp-binomial-pricer/actions/workflows/cmake.yml/badge.svg)](https://github.com/shreyanshz24/Cpp-binomial-pricer/actions)

A robust, high-performance binomial options pricing engine written in modern C++. This project provides a flexible and tested implementation of the Cox-Ross-Rubinstein (CRR) binomial model for valuing various types of options.

## Features

* **Option Types:** Prices both **European** and **American** style options.
* **Payoffs:** Supports both **Call** and **Put** options.
* **Greeks Calculation:** Computes key risk metrics including **Delta** and **Gamma**.
* **Modern C++:** Built with modern C++17 features, focusing on clean design, efficiency, and robustness.
* **Templated Design:** Core pricing logic is templated to allow for different numeric precision types (e.g., `float`, `double`).
* **Fully Tested:** Comprehensive unit test suite built with the Google Test framework to ensure mathematical correctness and handle edge cases.
* **Professional Build System:** Uses CMake for cross-platform compilation and test integration.

## Core Theory: The Binomial Model

The project implements the Cox-Ross-Rubinstein (CRR) model, which discretizes time to model the evolution of a stock price. In each time step $\Delta t$, the stock price $S$ can either move up by a factor of $u$ or down by a factor of $d$.

The key is to calculate a "risk-neutral probability" $p$ for the upward movement. This is the probability that would exist in a world where all assets are expected to grow at the risk-free rate $r$. The formulas are:

* Up-factor: $ u = e^{\sigma\sqrt{\Delta t}} $
* Down-factor: $ d = e^{-\sigma\sqrt{\Delta t}} = 1/u $
* Risk-Neutral Probability: $ p = \frac{e^{r\Delta t} - d}{u - d} $

The option's value is then found by calculating its expected payoff at expiration and discounting it back to the present time, step by step, through the binomial tree. For American options, the possibility of early exercise is checked at each node.

## Build Instructions

This project uses CMake for building. A C++17 compliant compiler is required.

```bash
# 1. Clone the repository
git clone [https://github.com/shreyanshz24/Cpp-binomial-pricer.git](https://github.com/shreyanshz24/Cpp-binomial-pricer.git)
cd Cpp-binomial-pricer

# 2. Create a build directory
mkdir build
cd build

# 3. Configure the project with CMake
cmake ..

# 4. Compile the code with Make
make

