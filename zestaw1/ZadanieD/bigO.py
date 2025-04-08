import matplotlib.pyplot as plt
import numpy as np
import os

# Read data from the file
def read_data(filename):
    sizes = []
    times = []
    
    # Get the directory of the current script
    script_dir = os.path.dirname(os.path.abspath(__file__))
    # Create absolute path to the data file
    file_path = os.path.join(script_dir, filename)
    

    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) == 2:
                sizes.append(int(parts[0]))
                times.append(float(parts[1]))
        
    print(f"Successfully loaded {len(sizes)} data points from {file_path}")
    return np.array(sizes), np.array(times)

# Plot the data

def plot_data(dataFile, title, xlabel, ylabel, filename):
    sizes, times = read_data(dataFile)
    
    plt.figure(figsize=(10, 6))
    
    # Plot the measured data points
    plt.scatter(sizes, times, color='red', label='Measured times')
    plt.plot(sizes, times, 'r-', alpha=0.5)

    # Add labels and title
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.grid(True)
    plt.legend()
    
    # Save the plot
    plt.savefig(filename)
    
    # Show the plot
    plt.show()
    
if __name__ == "__main__":
    plot_data('time_complexity_results_Add_dictionarySimple.txt', 'Time Complexity Analysis of Add Operation', 'Input Size (n)', 'Execution Time (seconds)', 'plot_add_dictionarySimple.png')
    plot_data('time_complexity_results_Remove_dictionarySimple.txt', 'Time Complexity Analysis of Remove Operation', 'Input Size (n)', 'Execution Time (seconds)', 'plot_remove_dictionarySimple.png')
    plot_data('time_complexity_results_Contains_dictionarySimple.txt', 'Time Complexity Analysis of Contains Operation', 'Input Size (n)', 'Execution Time (seconds)', 'plot_contains_dictionarySimple.png')