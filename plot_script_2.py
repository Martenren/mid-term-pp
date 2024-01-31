from matplotlib import colormaps
import matplotlib.pyplot as plt
num_words = [10000, 100000, 1000000, 5000000, 10000000, 25000000, 50000000, 75000000, 100000000]
times = {1: 9.585,2: 5.831,3: 4.824,4: 3.993,5: 3.804,6: 3.92,7: 3.753,8: 3.512,9: 3.376,10: 3.47,11: 3.272,12: 3.216}
color_map = colormaps['Set2']
plt.xticks(list(times.keys()))
plt.bar(list(times.keys()), list(times.values()), color=color_map.colors)
plt.xlabel('Number of threads')
plt.ylabel('Time taken (s)')
plt.savefig('bar_plot.png')
