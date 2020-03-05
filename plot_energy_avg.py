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
tbls = []
tbls_us = []
i = 0
while i < len(plot_dat):
	curr = plot_dat[i][0]
	Sltf = 0.0
	Sltf_us = 0.0
	Stbls = 0.0
	Stbls_us = 0.0
	count = 0
	while i < len(plot_dat) and plot_dat[i][0] == curr:
		inf_present = False
		for j in range(1, 5):
			if plot_dat[i][j] == math.inf:
				inf_present = True
				break
		if not inf_present:
			Sltf     += plot_dat[i][1]
			Sltf_us  += plot_dat[i][2]
			Stbls    += plot_dat[i][3]
			Stbls_us += plot_dat[i][4]
			count += 1
		i += 1
	utl.append(curr)
	ltf.append(Sltf/count)
	ltf_us.append(Sltf_us/count)
	tbls.append(Stbls/count)
	tbls_us.append(Stbls_us/count)

e_max = max(max(ltf), max(ltf_us), max(tbls), max(tbls_us))
for i in range(len(utl)):
	ltf[i] = ltf[i]/e_max * 100.0
	ltf_us[i] = ltf_us[i]/e_max * 100.0
	tbls[i] = tbls[i]/e_max * 100.0
	tbls_us[i] = tbls_us[i]/e_max * 100.0

ltf_line = ax.plot(utl, ltf, '.-', linewidth=0.2, markersize=3.0, color="red", label="LTF")
ltf_us_line = ax.plot(utl, ltf_us, '.-', linewidth=0.2, markersize=3.0, color="orange", label="LTF US")
tbls_line = ax.plot(utl, tbls, '.-', linewidth=0.2, markersize=3.0, color="blue", label="TBLS")
tbls_us_line = ax.plot(utl, tbls_us, '.-', linewidth=0.2, markersize=3.0, color="purple", label="TBLS US")

# fig.suptitle(f'Energy: {round(energy, 4)} mJ     Finish Time: {round(max(max1, max2), 4)} ms', fontsize=16)
fig.legend(markerscale=4, fontsize=10)
plot.show()
