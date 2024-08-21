# SMP2 Engine

This engine is designed to load and execute SMP2 (Simulation Model Portability 2) models, facilitating the development and integration of complex system simulations, particularly in the aerospace industry.
The engine is based in SMP2 issue 1.2 and it is not yet supporting all the features of the standard.

## Overview

The **SMP2 Engine** provides a core framework to load, manage, and execute SMP2-compliant simulation models. With this engine, users can easily integrate different models, simulate spacecraft operations, or other complex systems, and ensure interoperability across different platforms and organizations.

## Features

- **SMP2 Model Loader:**Loads and validates SMP2 models according to the SMP2 standard.
- **Modular Architecture:** Supports the integration of modular components, making it easy to extend or replace individual simulation models.
- **Interoperability:** Ensures models developed with different tools or by different organizations can work together seamlessly.
- **Basic Models Included:** Includes a couple of basic SMP2 models as examples to get started quickly.

## Getting Started

### Prerequisites

To build and run the SMP2 Engine, you will need the following:

- **C++ Compiler** (gcc, clang, mingw)
- **Make**

### Installation

1. **Clone the repository:**

    ```bash
    git clone https://github.com/iflumpi/smp2engine.git
    cd smp2engine
    ```

2. **Build the project:**

    ```bash
    make
    ```

3. **Run the Engine:**

    ```bash
    ./smp2engine
    ```

### Running Example Models

The building process compiles some basic SMP2 models as dynamic libraries to demonstrate the engine’s capabilities. These models cover simple scenarios that will help you understand how to structure and execute your own SMP2-compliant simulations.

To run an example:

```bash
./smp2engine ./libExample.so
