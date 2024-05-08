# Complexity Plot for Naive Approach v/s Dynamic Programming Approach (Knapsack Problem ) 

import matplotlib.pyplot as plt
import numpy as np

# Define the range for the number of items
item_counts = np.arange(1, 21)  # From 1 to 20 items
naive_complexities = [2**n for n in item_counts]  # Exponential growth for naive approach
dp_complexities = [n*20 for n in item_counts]  # Linear growth in 'n' for DP with constant W=20

plt.figure(figsize=(10, 6))
plt.plot(item_counts, naive_complexities, label='Naive Recursive (Exponential)', marker='o')
plt.plot(item_counts, dp_complexities, label='Dynamic Programming (Polynomial)', marker='x')
plt.yscale('log')  # Using logarithmic scale to better visualize exponential growth
plt.xlabel('Number of Items')
plt.ylabel('Computational Complexity (log scale)')
plt.title('Complexity Comparison: Naive vs. Dynamic Programming Approaches')
plt.legend()
plt.grid(True)
plt.show()
