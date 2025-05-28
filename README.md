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

### Installation Steps

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/assembly-line-scheduling.git
   cd assembly-line-scheduling
