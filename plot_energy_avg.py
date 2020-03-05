#!/bin/python

import sys
import math
import matplotlib.pyplot as plot

fig, ax = plot.subplots()

ax.set_xlim(-1, 101)
Y_max=101
ax.set_ylim(-1, Y_max)
ax.set_xlabel('Utilization %')
ax.set_ylabel('Avg. Normalised Energy Consumption %')
ax.grid(True)

if len(sys.argv) != 2:
	print("usage: plot_energy.py <plot-data>")
	sys.exit(1)

plot_dat = []
with open(sys.argv[1]) as plot_data:
	for line in plot_data:
		vals = tuple(map(float, line.split(' ')))
		plot_dat.append(vals)
plot_dat = sorted(plot_dat)

utl = []
ltf = []
ltf_us = []
i = 0
while i < len(plot_dat):
	curr = plot_dat[i][0]
	Sltf = 0.0
	Sltf_us = 0.0
	count = 0
	while i < len(plot_dat) and plot_dat[i][0] == curr:
		if plot_dat[i][1] != math.inf and plot_dat[i][2] != math.inf:
			Sltf    += plot_dat[i][1]
			Sltf_us += plot_dat[i][2]
			count += 1
		i += 1
	utl.append(curr)
	ltf.append(Sltf/count)
	ltf_us.append(Sltf_us/count)

e_max = max(max(ltf), max(ltf_us))
for i in range(len(utl)):
	ltf[i] = ltf[i]/e_max * 100.0
	ltf_us[i] = ltf_us[i]/e_max * 100.0

ltf_line = ax.plot(utl, ltf, '.-', linewidth=0.2, markersize=3.0, color="red", label="LTF")
ltf_us_line = ax.plot(utl, ltf_us, '.-', linewidth=0.2, markersize=3.0, color="green", label="LTF US")

# fig.suptitle(f'Energy: {round(energy, 4)} mJ     Finish Time: {round(max(max1, max2), 4)} ms', fontsize=16)
fig.legend(markerscale=4, fontsize=10)
plot.show()
