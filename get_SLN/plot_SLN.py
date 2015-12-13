import numpy as np
import matplotlib.cm as cm
from matplotlib import pyplot as plt
from matplotlib.colors import LogNorm
from matplotlib import mpl

with open("order.txt",'r') as area_file:
	areas = []
	for line in area_file:
		areas.append(line[0:-1])

SLN = np.genfromtxt("SLN.csv", delimiter=';')
FLN = np.genfromtxt("FLN.csv", delimiter=';')



for i in range(len(SLN)):
	for j in range(len(SLN[i])):	
		if FLN[i][j] ==0:
			SLN[i][j] =-1

my_cmap = mpl.colors.LinearSegmentedColormap.from_list("my_colormap",['blue','black','red'],256)


my_cmap.set_under('0.7')

plt.imshow(SLN,cmap=my_cmap,interpolation='nearest',vmin=0,vmax=1)
plt.xticks(range(29),areas,rotation=90.)
plt.yticks(range(29),areas)
plt.tick_params(axis='both',labelsize=9)

plt.colorbar()
plt.savefig("SLN.png",dpi=300)








