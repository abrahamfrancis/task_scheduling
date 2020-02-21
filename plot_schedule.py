#!/bin/python

import matplotlib.pyplot as plot

fig, ax = plot.subplots()

ax.set_xlim(-20, 120)
ax.set_ylim(0, 5)
ax.set_xlabel('Time')
ax.set_yticks([0.5, 2.5])
ax.set_yticklabels(['LP', 'HP'])
ax.grid(True)

energy = 0.0

def plot_bars(y, li, ids, freq):
	for i in range(len(li)):
		if ids[i][-1] != "'":
			ax.broken_barh([li[i]], (y, freq[i]), facecolors=((153/255, 178/255, 203/255)), edgecolor='black')
		else:
			ax.broken_barh([li[i]], (y, freq[i]), facecolors=((208/255, 221/255, 234/255)), edgecolor='black', hatch='X')

	for i in range(0, len(li)):
		ax.text(li[i][0] + li[i][1]/2 - 0.05, y + 0.05 + freq[i], str(ids[i]))

def extract(line):
	line_data = line.split(' ')
	ids = []
	li = []
	freq = []
	for i in range(0, len(line_data), 4):
		ids.append(line_data[i])
		bar_data = (float(line_data[i + 1]), float(line_data[i + 2]))
		freq.append(float(line_data[i + 3]))
		li.append(bar_data)
	return li, ids, freq

line = input('')
li, ids, freq = extract(line)
plot_bars(2.5, li, ids, freq)
max1 = li[-1][0] + li[-1][1]

line = input('')
li, ids, freq = extract(line)
plot_bars(0.5, li, ids, freq)
max2 = li[-1][0] + li[-1][1]

energy = float(input(''))

fig.suptitle(f'Energy: {energy} mJ     Total Time: {max(max1, max2)} ms', fontsize=16)

plot.show()
