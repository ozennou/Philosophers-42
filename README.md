# Philosophers

This repository contains a C language implementation of the Dining Philosophers problem, along with a bonus part that extends the basic functionality. The Dining Philosophers problem is a classic synchronization problem often used to illustrate the challenges of deadlock and resource allocation in concurrent systems.

## Mandatory Part

The mandatory part of the project implements the Dining Philosophers problem according to the following rules:

- Global variables are forbidden.
- The program takes the following arguments:
  - `number_of_philosophers`: The number of philosophers and forks.
  - `time_to_die`: Time in milliseconds before a philosopher dies if they haven't eaten.
  - `time_to_eat`: Time in milliseconds it takes for a philosopher to eat.
  - `time_to_sleep`: Time in milliseconds a philosopher spends sleeping.
  - `[number_of_times_each_philosopher_must_eat]` (optional): Number of times each philosopher must eat before the simulation stops.
- Each philosopher is numbered from 1 to `number_of_philosophers`.
- Philosopher 1 sits next to philosopher `number_of_philosophers`. Any other philosopher `N` sits between philosopher `N - 1` and philosopher `N + 1`.

The program outputs the state changes of each philosopher with formatted timestamps, including when they take a fork, eat, sleep, think, or die.

## Bonus Part

The bonus part extends the functionality of the program by implementing additional features while complying with the requirements of the Global rules chapter. 

The program of the bonus part takes the same arguments as the mandatory program. It has to comply with the requirements of the Global rules chapter.

The specific rules for the bonus part are:

- All the forks are put in the middle of the table.
- They have no states in memory but the number of available forks is represented by a semaphore.
- Each philosopher should be a process. But the main process should not be a philosopher.

This extended version of the program introduces a more complex synchronization mechanism using semaphores and processes to represent the philosophers and forks. By having each philosopher as a separate process, the program can better simulate concurrent dining philosophers while ensuring compliance with the specified rules.
