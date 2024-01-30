import matplotlib.pyplot as plt
num_words = [10000, 100000, 1000000, 5000000, 10000000, 25000000, 50000000, 75000000, 100000000]
sequential_times = [0, 0, 0, 0, 0, 1, 3, 5, 8]
parallel_times = [0, 0, 0, 0, 0, 0, 1, 2, 3]
plt.plot(num_words, sequential_times, marker='o', label='Sequential')
plt.plot(num_words, parallel_times, marker='o', label='Parallel')
plt.xlabel('Number of Words')
plt.ylabel('Time (seconds)')
plt.title('Parallel vs Sequential bigram generation')
plt.legend()
plt.grid(True)
plt.savefig('plot.png')
plt.show()
