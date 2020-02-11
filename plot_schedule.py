import matplotlib.pyplot as plot

fig, ax = plot.subplots()

ax.set_xlim(0, 200)
ax.set_ylim(0, 5)
ax.set_xlabel('Time')
ax.set_yticks([0.5, 2.5])
ax.set_yticklabels(['LP', 'HP'])
ax.grid(True)

energy = 0.0

def plot_bars(y, li, ids, freq, colors):
	clen = len(colors)
	for i in range(len(li)):
		ax.broken_barh([li[i]], (y, freq[i]), facecolors=(colors[i%clen]), edgecolor='black')

	for i in range(0, len(li)):
		ax.text(li[i][0] + li[i][1]/2 - 0.05, y + 0.05 + freq[i], str(ids[i]))

def extract(line):
	line_data = line.split(' ')
	ids = []
	li = []
	freq = []
	for i in range(0, len(line_data), 4):
		id_no = int(line_data[i])
		if id_no < 0:
			line_data[i] = str(-id_no) + '\''
		ids.append(line_data[i])
		bar_data = (float(line_data[i + 1]), float(line_data[i + 2]))
		freq.append(float(line_data[i + 3]))
		li.append(bar_data)
	return li, ids, freq

line = input('')
li, ids, freq = extract(line)
plot_bars(2.5, li, ids, freq, ('tab:red', 'tab:orange'))
max1 = li[-1][0] + li[-1][1]

line = input('')
li, ids, freq = extract(line)
plot_bars(0.5, li, ids, freq, ('tab:blue', 'tab:green'))
max2 = li[-1][0] + li[-1][1]

energy = float(input(''))

fig.suptitle(f'Energy: {energy} mJ     Total Time: {max(max1, max2)} ms', fontsize=16)

plot.show()
