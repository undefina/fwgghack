from __future__ import print_function
import torch
import numpy as np


def get_error_value(b, k, points) -> float:
    total_error = 0.0
    for i in range(0, len(points)):
        x = points[i, 0]
        y = points[i, 1]
        total_error += (y - (k * x + b)) ** 2
    return total_error / float(len(points))


def step_gradient(b_current, k_current, points, learning_rate):
    b_gradient = 0.0
    k_gradient = 0.0
    n = float(len(points))
    for i in range(0, len(points)):
        x = points[i, 0]
        y = points[i, 1]
        b_gradient += (2.0 / n) * (y - (k_current * x + b_current))
        k_gradient += (2.0 / n) * x * (y - (k_current * x + b_current))

    b_new = b_current + learning_rate * b_gradient
    k_new = k_current + learning_rate * k_gradient
    return [b_new, k_new]


def gradient_loop(points, b_start, k_start, learning_rate, iteration_times):
    b = b_start
    k = k_start
    for i in range(iteration_times):
        b, k = step_gradient(b, k, np.array(points), learning_rate)
    return [b, k]


def run():
    points = np.loadtxt('points.csv', dtype=float, delimiter=' ')
    print(len(points))
    learning_rate = 0.000003
    b_initial = 0.0
    k_initial = 0.0
    iteration_times = 10000
    print("At first, b is {0}, k is {1} , and error value is {2}".format(b_initial, k_initial,
                                                                         get_error_value(b_initial, k_initial, points)))
    b, k = gradient_loop(points, b_initial, k_initial, learning_rate, iteration_times)
    print("After {0} iterations, b is {1}, k is {2} ,"
          "and error value is {3}".format(iteration_times, b, k, get_error_value(b, k, points)))


if __name__ == '__main__':
    run()
