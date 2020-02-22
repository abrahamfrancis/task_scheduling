#!/bin/python

import sys
import matplotlib.pyplot as plot

fig, ax = plot.subplots()

ax.set_xlim(0, 200)
Y_max=75
ax.set_ylim(0, Y_max)
ax.set_xlabel('Time (ms)')
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
	# ax.plot([pts[0], pts[0]], [pts[1], pts[2]], '-', color="blue", linewidth=0.01)

ltf_line = ax.plot(utl, ltf, '.', markersize=0.5, color="red", label="LTF")
ltf_us_line = ax.plot(utl, ltf_us, '.', markersize=0.5, color="green", label="LTF US")

# fig.suptitle(f'Energy: {round(energy, 4)} mJ     Finish Time: {round(max(max1, max2), 4)} ms', fontsize=16)
fig.legend(markerscale=32.0, fontsize=10)
plot.show()
