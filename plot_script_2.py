from matplotlib import colormaps
import matplotlib.pyplot as plt
num_words = [10000, 100000, 1000000, 5000000, 10000000, 25000000, 50000000, 75000000, 100000000]
times = {1: 8.696,2: 5.604,3: 4.635,4: 3.936,5: 3.696,6: 3.776,7: 3.688,8: 3.806,9: 3.652,10: 3.553,11: 3.563,12: 3.398}
color_map = colormaps['Set2']
plt.xticks(list(times.keys()))
plt.bar(list(times.keys()), list(times.values()), color=color_map.colors)
plt.xlabel('Number of cores')
plt.ylabel('Time taken (s)')
plt.savefig('bar_plot.png')
