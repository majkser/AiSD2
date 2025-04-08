import matplotlib.pyplot as plt
import numpy as np
import os

# Read data from the file
def read_data(filename):
    # Get the directory of the current script
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    # Create path to the correct subdirectory
    if "setSimple" in filename:
        file_path = os.path.join(script_dir, "ZadanieA", filename)
    elif "setLinked" in filename:
        file_path = os.path.join(script_dir, "ZadanieB", filename)
    else:
        file_path = os.path.join(script_dir, filename)
    
    sizes = []
    times = []
    
    try:
        with open(file_path, 'r') as file:
            for line in file:
                parts = line.strip().split()
                if len(parts) == 2:
                    sizes.append(int(parts[0]))
                    times.append(float(parts[1]))
            
        print(f"Successfully loaded {len(sizes)} data points from {file_path}")
        return np.array(sizes), np.array(times)
    except FileNotFoundError:
        print(f"File not found: {file_path}")
        return np.array([]), np.array([])

# Plot the data from both implementations together
def plot_comparison(operation_name, xlabel, ylabel, output_filename):
    # Filenames for both implementations
    simple_file = f"time_complexity_results_{operation_name}_setSimple.txt"
    linked_file = f"time_complexity_results_{operation_name}_setLinked.txt"
    
    # Read data with implementation specified
    sizes_simple, times_simple = read_data(simple_file)
    sizes_linked, times_linked = read_data(linked_file)
    
    if len(sizes_simple) == 0 or len(sizes_linked) == 0:
        print(f"Skipping {operation_name} comparison due to missing data")
        return
    
    plt.figure(figsize=(12, 7))
    
    # Plot both implementations
    plt.scatter(sizes_simple, times_simple, color='red', s=30, alpha=0.7, label='Array-based (setSimple)')
    plt.plot(sizes_simple, times_simple, 'r-', alpha=0.5)
    
    plt.scatter(sizes_linked, times_linked, color='blue', s=30, alpha=0.7, label='Linked-list (setLinked)')
    plt.plot(sizes_linked, times_linked, 'b-', alpha=0.5)
    
    # Add labels and title
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(f'Time Complexity Comparison - {operation_name} Operation')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend()
    
    # Save and show the plot
    plt.savefig(output_filename)
    plt.show()

if __name__ == "__main__":
    operations = [
        ('union', 'Union'),
        ('Intersection', 'Intersection'),
        ('Diff', 'Difference'),
        ('Identity', 'Identity Check'),
        ('Add', 'Add Element'), 
        ('Remove', 'Remove Element'),
        ('Contains', 'Contains Check')
    ]
    
    for op_file, op_name in operations:
        plot_comparison(
            op_file,
            'Input Size (n)',
            'Execution Time (seconds)',
            f'comparison_plot_{op_file}.png'
        )