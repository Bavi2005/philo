*This project has been created as part of the 42 curriculum by bpichyal.*

## Description

The Philosophers project is a classic synchronization problem that explores the challenges of concurrent programming. It simulates philosophers sitting at a round table who must alternate between eating, thinking, and sleeping. Each philosopher needs two forks to eat, but there are only as many forks as there are philosophers, creating a resource sharing challenge.

This implementation uses threads and mutexes to ensure that:
- Philosophers don't starve
- No deadlocks occur
- State changes are properly logged with timestamps
- The simulation stops when a philosopher dies or all have eaten enough

## Instructions

### Compilation

To compile the project, navigate to the `philo/` directory and run:

```bash
cd philo
make
```

This will create the `philo` executable with the following flags: `-Wall -Wextra -Werror -pthread`

### Usage

Run the program with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Arguments:**
- `number_of_philosophers`: Number of philosophers and forks
- `time_to_die`: Time in milliseconds before a philosopher dies without eating
- `time_to_eat`: Time in milliseconds it takes to eat
- `time_to_sleep`: Time in milliseconds spent sleeping
- `number_of_times_each_philosopher_must_eat` (optional): Simulation stops when all philosophers have eaten this many times

**Examples:**

```bash
./philo 5 800 200 200        # 5 philosophers, no one should die
./philo 5 800 200 200 7      # Stop after each philosopher eats 7 times
./philo 4 410 200 200        # 4 philosophers, no one should die
./philo 4 310 200 100        # A philosopher should die
./philo 1 800 200 200        # One philosopher should die (can't eat with one fork)
```

### Cleaning

To remove object files:
```bash
make clean
```

To remove object files and the executable:
```bash
make fclean
```

To recompile everything:
```bash
make re
```

## Resources

- [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/)
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Thread Synchronization](https://www.cs.cmu.edu/~410-s05/lectures/L31_LockFree.pdf)
- [Mutex Documentation](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
