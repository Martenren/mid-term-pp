import matplotlib.pyplot as plt
num_words = [10000, 100000, 1000000, 5000000, 10000000, 25000000, 50000000, 75000000, 100000000]
sequential_times = [0, 0.007, 0.068, 0.331, 0.708, 1.904, 4.339, 6.011, 8.995]
parallel_times = [0.007, 0.003, 0.031, 0.136, 0.296, 0.741, 1.676, 2.521, 4.821]
tick_locs = num_words
tick_labels = [f'{val // 1000000}M' if val >= 1000000 else val for val in num_words]
plt.xticks(tick_locs, tick_labels)
plt.plot(num_words, sequential_times, marker='o', label='Sequential')
plt.plot(num_words, parallel_times, marker='o', label='Parallel')
plt.xlabel('Number of words')
plt.ylabel('Time (seconds)')
plt.title('Parallel vs Sequential bigram generation')
plt.legend()
plt.grid(True)
plt.savefig('plot.png')
plt.show()
