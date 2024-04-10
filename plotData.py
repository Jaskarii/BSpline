import os
import numpy as np
import matplotlib.pyplot as plt

def read_points_from_file(file_path):
    with open(file_path, 'r') as file:
        points = np.array([list(map(float, line.strip().split(','))) for line in file])
    return points

def plot_points(original_file, interpolated_file):
    # Read points from files
    original_points = read_points_from_file(original_file)
    interpolated_points = read_points_from_file(interpolated_file)

    # Plotting
    plt.figure(figsize=(10, 6))
    plt.scatter(original_points[:, 0], original_points[:, 1], color='blue', label='Original Points')
    plt.scatter(interpolated_points[:, 0], interpolated_points[:, 1], color='red', label='Interpolated Points')
    plt.title('Original vs Interpolated Points')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    script_dir = os.path.dirname(__file__)  # Get the directory where the script is located
    original_file_path = os.path.join(script_dir, 'points.txt')  # Construct the full path to the file
    interpolated_file_path = os.path.join(script_dir, 'interpolated_points.txt')  # Construct the full path to the file
    plot_points(original_file_path, interpolated_file_path)
