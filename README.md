
# Assembly Line Scheduling Problem (ALSP) - Optimized Scheduling Algorithm

## Overview

This repository presents a solution to the **Assembly Line Scheduling Problem (ALSP)**, focusing on optimizing the scheduling of jobs across multiple assembly lines in a manufacturing setting. The goal is to minimize the makespan (total production time), improve resource utilization, and handle real-world constraints such as worker availability, machine downtime, job dependencies, and setup times.

The project implements a **Greedy Scheduling Algorithm** to allocate jobs to assembly lines efficiently. Additionally, it considers worker skills, job dependencies, and maintenance windows in its optimization process.

## Key Features

- **Greedy Scheduling Algorithm**: Efficient allocation of jobs to assembly lines, minimizing total production time.
- **Job Dependency Handling**: Accounts for precedence constraints between jobs.
- **Worker & Assembly Line Utilization**: Balances workloads across workers and assembly lines, ensuring optimal resource usage.
- **Maintenance Scheduling**: Incorporates machine downtime and maintenance windows into the scheduling process.
- **Visualization**: Generates Gantt charts for visual representation of the schedule.
- **Performance Metrics**: Evaluates the algorithm's performance based on makespan, worker utilization, and setup time.

## Problem Statement

A manufacturing company has multiple assembly lines, each with different processing speeds and downtime schedules. The goal is to schedule jobs efficiently across these lines while minimizing total production time (makespan), considering:

- **Job Dependencies**: Some jobs must be completed before others can start.
- **Worker Availability**: Different workers have varying skill levels and may not be available for all tasks.
- **Setup Time**: Switching between job types requires setup time.
- **Machine Downtime**: Assembly lines may be unavailable due to scheduled maintenance.

## Setup and Installation

### Prerequisites

To run this project, you'll need a C++ development environment. This project is compatible with any modern C++ compiler (e.g., GCC, Clang).

- **C++ Compiler** (GCC, Clang, or equivalent)
- **C++ IDE** (Visual Studio, CLion, Code::Blocks, etc.)


## Algorithm Details

The scheduling algorithm follows a **Greedy Approach** designed to minimize the makespan and improve resource utilization. The key steps are:

1. **Job Sorting**: Jobs are sorted based on processing time (longest processing time first).
2. **Job Allocation**: Jobs are assigned to assembly lines based on availability and efficiency.
3. **Worker Assignment**: Workers are assigned to jobs based on their skill level and availability.
4. **Makespan Calculation**: Tracks the total time to complete all jobs, aiming to minimize this time.

### Greedy Approach Justification

The greedy algorithm is selected due to its simplicity and effective performance in scheduling moderately complex job assignments. By prioritizing jobs with the longest processing times and considering worker availability, the algorithm aims to minimize idle time and ensure a balanced workload across all resources.

## Testing

The algorithm is tested using a representative dataset: **Copper Wire Production Line Dataset** (`e-Dataset.csv`). This dataset simulates a variety of job dependencies, worker profiles, assembly line speeds, and machine maintenance schedules.

### Sample Test Case

```cpp
createTestScenario(jobs, lines, workers);
```

* **Input**: A set of jobs, workers with varying skill levels, assembly lines with different speeds, and a maintenance window.
* **Expected Output**: A detailed schedule including job assignments, worker utilization, makespan, and a Gantt chart visualizing the entire process.

### Performance Metrics

The performance of the algorithm is evaluated based on:

* **Makespan**: The total time required to complete all jobs.
* **Worker Utilization**: The percentage of time each worker is actively working.
* **Assembly Line Utilization**: The percentage of time each assembly line is being used.
* **Setup Time**: The time spent switching between jobs of different types.

## Comparative Analysis

The algorithm's performance is compared with other traditional scheduling algorithms such as **First-Come, First-Served (FCFS)** and **Shortest Job First (SJF)**. The greedy approach consistently demonstrates a better balance between job completion time and resource utilization.

## Future Enhancements

* **Advanced Optimization**: Implementing more advanced techniques like **Genetic Algorithms** or **Simulated Annealing** to handle more complex and dynamic scheduling scenarios.
* **Real-Time Scheduling**: Adapt the algorithm to support real-time scheduling adjustments as jobs arrive unpredictably.
* **Additional Constraints**: Incorporate more real-world constraints, such as energy consumption and dynamic job prioritization.

## Contributing

We welcome contributions to improve and expand the functionality of this project. If you'd like to contribute, please fork the repository, create a new branch, and submit a pull request. Ensure your changes are well-documented and include relevant test cases.

### How to Contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-name`).
3. Make your changes.
4. Push to the branch (`git push origin feature-name`).
5. Submit a pull request.

Please ensure your code adheres to the following guidelines:

* Consistent coding style.
* Proper inline documentation.
* Detailed commit messages.

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for more details.``
