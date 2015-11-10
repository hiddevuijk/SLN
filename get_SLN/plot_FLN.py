import numpy as np
import matplotlib.cm as cm
from matplotlib import pyplot as plt
from matplotlib.colors import LogNorm


with open("order.txt",'r') as area_file:
	areas = []
	for line in area_file:
		areas.append(line[0:-1])

FLN = np.genfromtxt("FLN.csv", delimiter=';')

my_cmap = cm.get_cmap('hot')
my_cmap.set_under('black')
my_cmap.set_bad('black')
plt.imshow(FLN,cmap=my_cmap,norm=LogNorm(vmin=1e-7,vmax=1),interpolation='nearest')
plt.xticks(range(29),areas,rotation=90.)
plt.yticks(range(29),areas)
plt.tick_params(axis='both',labelsize=9)

plt.colorbar()
plt.savefig("FLN.png",dpi=300)








