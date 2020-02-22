#!/bin/python

import sys
import matplotlib.pyplot as plot

fig, ax = plot.subplots()

ax.set_xlim(0, 100)
Y_max=50
ax.set_ylim(0, Y_max)
ax.set_xlabel('Time')
ax.set_ylabel('Energy (mJ)')
ax.grid(True)

if len(sys.argv) != 2:
	print("usage: plot_energy.py <plot-data>")
	sys.exit(1)

plot_dat = []
with open(sys.argv[1]) as plot_data:
	for line in plot_data:
		vals = tuple(map(float, line.split(' ')))
		plot_dat.append(vals)
		# print(vals[0], vals[1], vals[2])
plot_dat = sorted(plot_dat)

utl = []
ltf = []
ltf_us = []
for pts in plot_dat:
	utl.append(pts[0])
	ltf.append(pts[1])
	ltf_us.append(pts[2])

ax.plot(utl, ltf, 'ro-.')
ax.plot(utl, ltf_us, 'bo-.')

# fig.suptitle(f'Energy: {round(energy, 4)} mJ     Finish Time: {round(max(max1, max2), 4)} ms', fontsize=16)

plot.show()
