
# Particle Swarm Optimization (PSO) - Rescue Mission

## Overview
This project is a C implementation of the **Particle Swarm Optimization (PSO)** algorithm.

The project is designed with modularity in mind, adhering to C99 standards, and includes tools for map generation, logging, and automated testing.

## Features
* **PSO Algorithm**: Full implementation with configurable inertia weight and cognitive/social coefficients.
* **Modular Architecture**: Clean separation of logic (`pso`, `map`, `logger`, `utils`).
* **CLI Interface**: Fully configurable via command-line arguments.
* **Data Logging**: Exports particle positions and fitness values to `results.csv` for visualization.
* **Map Generator**: Built-in tool to create custom test maps.
* **Automated Testing**: Includes both Unit tests and Functional (End-to-End) tests.

## Project Structure

```text
.
├── main.c              # Entry point for the simulation
├── Makefile            # Build automation script
├── src/                # Source code modules
│   ├── map.c / .h      # Map loading and memory management
│   ├── pso.c / .h      # PSO algorithm logic and swarm management
│   ├── logger.c / .h   # CSV logging functionality
│   ├── utils.c / .h    # Helper functions and RNG
│   ├── map_generator.c # Map generation tool
│   ├── test_unit.c     # Unit testing suite
│   └── test_functional.c # Functional testing suite
└── README.md

```

## Prerequisites

* **GCC** compiler.
* **Make** build tool.
* Standard C libraries.

## Building the Project

The project uses a `Makefile` to manage compilation and linking.

### Build Everything

To compile the main simulation `pso`:

```bash
make

```

### Build Specific Targets

* **Map Generator**:
```bash
make gen

```


* **Tests**:
```bash
make unit    # Build and run unit tests
make func    # Build and run functional tests

```



### Clean Build

To remove compiled binaries, object files, and temporary logs:

```bash
make clean

```

## Usage

### 1. Generating a Map

Before running the simulation, you need a map file. You can generate one using the included tool:

```bash
# First, build the generator
make gen

# Usage: ./generator <width> <height> <output_filename>
./generator 100 100 my_map.txt

```

### 2. Running the Simulation

Run the `pso` executable with the map file.

**Basic Syntax:**

```bash
./pso <map_file> [options]

```

**Options:**
| Flag | Description | Default |
|------|-------------|---------|
| `-p` | Number of particles (swarm size) | 30 |
| `-i` | Number of iterations | 100 |
| `-n` | Log interval (0 = disabled, 1 = log every step) | 0 |
| `-c` | Path to configuration file for coefficients | Default values |

**Example:**
Run with 50 particles for 200 iterations and log every step:

```bash
./pso my_map.txt -p 50 -i 200 -n 1

```

### 3. Output

The program outputs the best found position and signal value to the console:

```text
Start simulation: 
Map=my_map.txt, 
Particles=50, 
Iterations=200

--- Results ---
Found optimum (gBest):
X: 25.0042
Y: 25.0011
Signal Value: 100.0000

```

If `-n` is set, a `results.csv` file is created containing the history of particle movements.

## Testing

The project includes a robust testing suite to ensure correctness.

### Unit Tests

Checks individual modules (Map loading, Swarm initialization, etc.) in isolation.

```bash
make unit

```

### Functional Tests

Runs the algorithm on generated scenarios (maps with known peaks) to verify that the swarm actually finds the target.

```bash
make func

```

### Run All Tests

To run both unit and functional tests sequentially:

```bash
make test

```

## Visualization

The project includes a Python script `visualizer.py` to visualize the map and animate the swarm movement.

### Prerequisites
* Python 3.x
* Required libraries:
  ```bash
  pip install matplotlib pandas numpy

### How to Run

1. **Run the simulation** with logging enabled (`-n 1`). This generates the `results.csv` file.
```bash
./pso my_map.txt -p 50 -i 200 -n 1

```

2. **Run the visualizer** passing the map file as an argument:
```bash
python visualizer.py my_map.txt

```

### Controls

* **Play/Pause**: Start or stop the animation.
* **Iteration >**: Move one iteration forward.
* **< Iteration**: Move one iteration backward.

## Configuration File Format

If you use the `-c` flag, the configuration file should contain 5 floating-point numbers separated by spaces:

```text
<w> <c1> <r1> <c2> <r2>

```

* **w**: Inertia weight (e.g., 0.5)
* **c1**: Cognitive coefficient (particle's memory)
* **r1**: Random factor for c1 (-1 for random generation [0..1])
* **c2**: Social coefficient (swarm's memory)
* **r2**: Random factor for c2 (-1 for random generation [0..1])

**Example `config.txt`:**

```text
0.7 1.4 -1 1.4 -1

```