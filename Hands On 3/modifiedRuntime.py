import time
import numpy as np
import matplotlib.pyplot as plt

# Definition of the algorithmic function
def modified_algorithm(n):
    # Initialize variables
    x = 1
    y = 1
    
    # Nested loops simulating the algorithmic process
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            x = x + 1
            y = i + j
    
    # Return the result
    return x, y

# Generate values of n and measure execution times
input_sizes = np.arange(1, 1000)
execution_times = np.zeros_like(input_sizes, dtype=float)

for index, n in enumerate(input_sizes):
    start_time = time.time()
    modified_algorithm(n)
    execution_times[index] = time.time() - start_time

# Plotting the graph for the runtime analysis
plt.plot(input_sizes, execution_times, 'g-', label='Actual Data')
fit_coefficients = np.polyfit(input_sizes, execution_times, 2)
fitted_curve = np.polyval(fit_coefficients, input_sizes)
plt.plot(input_sizes, fitted_curve, 'b--', linewidth=2, label='Fitted Curve')

# Specifying upper and lower bounds based on the fitted curve
upper_bound = 1.1 * np.polyval(fit_coefficients, input_sizes)
lower_bound = 0.5 * np.polyval(fit_coefficients, input_sizes)

# Printing Big-O and Big-Omega
print("Upper Bound (Big-O):", upper_bound)
print("Lower Bound (Big-Omega):", lower_bound)

# Plotting upper and lower bounds with distinct line styles
plt.plot(input_sizes, upper_bound, 'r-.', linewidth=1.5, label='Upper Bound')
plt.plot(input_sizes, lower_bound, 'm:', linewidth=1.5, label='Lower Bound')

# Zooming in on a critical point, denoted as n_0, on the plot
critical_point = 100

# Indicating the location of n_0 using a scatter plot
plt.scatter(critical_point, np.polyval(fit_coefficients, critical_point), s=150, c='orange', marker='s',
            label=r'$n_0$')
plt.text(critical_point, np.polyval(fit_coefficients, critical_point), r'$n_0$', ha='right', va='bottom')

plt.xlabel('Input Sizes (n)')
plt.ylabel('Execution Time (s)')
plt.title('Modified Algorithm Runtime with Upper and Lower Bounds')
plt.grid(True)
plt.legend()
plt.show()
