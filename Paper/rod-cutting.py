
# Complexity Plot for Naive Approach v/s Dynamic Programming Approach ( Rod - cutting):

import matplotlib.pyplot as plt
import numpy as np

# Define lengths of the rod
rod_lengths = np.arange(1, 21)  # Rod lengths from 1 to 20
naive_times = [2**n for n in rod_lengths]  # Exponential growth for naive approach
dp_times = [n**2 for n in rod_lengths]  # Quadratic growth for DP approach

plt.figure(figsize=(10, 6))
plt.plot(rod_lengths, naive_times, label='Naive Recursive (Exponential)', marker='o')
plt.plot(rod_lengths, dp_times, label='Dynamic Programming (Quadratic)', marker='x')
plt.yscale('log')  # Log scale to better visualize the exponential growth
plt.xlabel('Length of the Rod')
plt.ylabel('Computational Complexity (log scale)')
plt.title('Complexity Comparison: Naive vs. Dynamic Programming Approaches')
plt.legend()
plt.grid(True)
plt.show()
