import numpy as np
import random


def run():
    points_size = 1000
    points = np.zeros((points_size,2))
    for i in range(points_size):
        points[i][0] = i + random.uniform(-0.1, 0.1)
        points[i][1] = i + 5 + random.uniform(-0.1, 0.1)

    print(points)
    np.savetxt('points.csv', points, delimiter=' ')


if __name__ == '__main__':
    run()