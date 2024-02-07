import time
import numpy as np
import matplotlib.pyplot as plt

# Function definition for the given algorithm
def algorithm_runtime(n):
    x = 1
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            x = x + 1
    return x

# Generate values of n and measure execution times
n_values = np.arange(1, 1000)
execution_times = np.zeros_like(n_values, dtype=float)

for index, n in enumerate(n_values):
    start_time = time.time()
    algorithm_runtime(n)
    execution_times[index] = time.time() - start_time

# Plotting the graph for Algorithm runtime of time vs n
plt.plot(n_values, execution_times, 'g-', label='Measured Data')
fit_coefficients = np.polyfit(n_values, execution_times, 2)
fitted_curve = np.polyval(fit_coefficients, n_values)
plt.plot(n_values, fitted_curve, 'b--', linewidth=2, label='Fitted Curve')

# Specifying upper and lower bounds
upper_bound = 1.1 * np.polyval(fit_coefficients, n_values)
lower_bound = 0.5 * np.polyval(fit_coefficients, n_values)

# Printing Big-O and Big-Omega
print("Upper Bound (Big-O):", upper_bound)
print("Lower Bound (Big-Omega):", lower_bound)

# Plotting upper and lower bounds of the curve
plt.plot(n_values, upper_bound, 'r-.', linewidth=1.5, label='Upper Bound')
plt.plot(n_values, lower_bound, 'm:', linewidth=1.5, label='Lower Bound')

# Zooming in on n_0 on the plot
n_0 = 100

# Indicating the location of n_0 on plot using scatter plot
plt.scatter(n_0, np.polyval(fit_coefficients, n_0), s=150, c='orange', marker='s',
            label=r'$n_0$')
plt.text(n_0, np.polyval(fit_coefficients, n_0), r'$n_0$', ha='right', va='bottom')

plt.xlabel('Values of n')
plt.ylabel('Execution Time (s)')
plt.title('Algorithm Runtime Analysis with Upper and Lower Bounds')
plt.grid(True)
plt.legend()
plt.show()
