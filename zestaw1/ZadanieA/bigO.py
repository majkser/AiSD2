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
def plot_time_complexity():
    sizes, times = read_data('time_complexity_results.txt')
    
    plt.figure(figsize=(10, 6))
    
    # Plot the measured data points
    plt.scatter(sizes, times, color='blue', label='Measured times')
    plt.plot(sizes, times, 'b-', alpha=0.5)
    
    # Optional: Add trend lines to identify complexity
    # For O(n²)
    coef_quad = np.polyfit(sizes, times, 2)
    quad_fit = np.poly1d(coef_quad)
    plt.plot(sizes, quad_fit(sizes), 'r--', label=f'O(n²) fit')
    
    # For O(n)
    coef_lin = np.polyfit(sizes, times, 1)
    lin_fit = np.poly1d(coef_lin)
    plt.plot(sizes, lin_fit(sizes), 'g--', label=f'O(n) fit')
    
    # Add labels and title
    plt.xlabel('Input Size (n)')
    plt.ylabel('Execution Time (seconds)')
    plt.title('Time Complexity Analysis of setUnion Operation')
    plt.grid(True)
    plt.legend()
    
    # Optional: Annotate the complexity
    max_size = max(sizes)
    max_time = max(times)
    
    # Save the plot
    plt.savefig('time_complexity_plot.png')
    
    # Show the plot
    plt.show()

if __name__ == "__main__":
    plot_time_complexity()