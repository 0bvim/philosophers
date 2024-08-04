# Dining Philosophers Problem

This repository contains an implementation of the Dining Philosophers Problem in C, using pthreads (POSIX threads) for concurrency management.

## Table of Contents
- [Introduction](#introduction)
- [Problem Description](#problem-description)
- [Implementation Details](#implementation-details)
- [How to Use](#how-to-use)
- [License](./LICENSE)

---

## Introduction

The Dining Philosophers Problem is a classic synchronization problem in computer science, designed to illustrate the challenges of concurrent programming. In this scenario, a number of philosophers sit around a dining table, each with a plate of spaghetti and a fork between each pair of adjacent philosophers. The philosophers spend their time either eating or thinking. To eat, a philosopher must acquire two forks—one from their left and one from their right. The challenge lies in preventing deadlocks and resource contention, ensuring that each philosopher can eat without causing conflicts with their neighbors.

This implementation provides a solution to the Dining Philosophers Problem using C and pthreads. It aims to demonstrate a practical approach to concurrency management in a multithreaded environment.

## Problem Description

The Dining Philosophers Problem can be summarized as follows:

- There are N philosophers sitting around a circular dining table.
- Each philosopher alternates between thinking and eating.
- To eat, a philosopher must pick up two forks—one from their left and one from their right.
- The challenge is to devise a strategy that allows each philosopher to eat without leading to deadlocks or resource contention.

## Implementation Details

- The solution is implemented in C programming language.
- POSIX threads (pthreads) are used for managing concurrency.
- A mutex lock is employed to ensure exclusive access to shared resources (forks).
- Each philosopher is represented by a separate thread.
- The program ensures that no two adjacent philosophers can simultaneously hold the same fork.

## How to Use

To run the program, follow these steps:

1. Clone this repository to your local machine.
2. Navigate to the directory containing the source code.
3. Compile the program using `make` and then `./philo <number_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> (optional)<times_to_eat>`
