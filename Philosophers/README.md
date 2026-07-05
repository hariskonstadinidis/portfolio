*This project has been created as part of the 42 curriculum by <hkonstan>*

## Description

The Dining Philosophers problem is a classic synchronization issue in concurrent programming. This project implements a solution using POSIX threads (pthreads) and mutexes in C.

**The Problem:**
Each philosopher sits at a round table, alternating between thinking, eating, and sleeping. To eat, a philosopher must acquire both their left and right forks. If a philosopher doesn't eat within a specified time limit, they die. The goal is to implement a simulation where all philosophers can eat and survive, or detect when someone dies.

**Key Concepts:**
- Thread synchronization using mutexes
- Deadlock prevention and detection
- State management in concurrent systems

## Instructions

### Requirements
- GCC/Clang compiler
- POSIX-compliant system (Linux/macOS)
- `make` utility

### Compilation

make        # Compile the program
make clean  # Remove object files
make fclean # Remove all generated files
make re     # Recompile from scratch

### Execution

./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

**Parameters:**
- `number_of_philosophers`: Number of philosophers at the table
- `time_to_die`: Maximum milliseconds a philosopher can go without eating before dying
- `time_to_eat`: Milliseconds it takes for a philosopher to eat (philosopher must hold both forks)
- `time_to_sleep`: Milliseconds a philosopher sleeps after eating
- `number_of_times_each_philosopher_must_eat`: (Optional) Simulation stops when all philosophers have eaten this many times

**Examples:**

```bash
./philo 5 800 200 200
./philo 4 410 200 200 10
```

## Resources

### Classic References
- [Dijkstra's Solution to the Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
