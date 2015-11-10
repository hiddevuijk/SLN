import numpy as np
from matplotlib import pyplot as plt
from pylab import rcParams

h = np.genfromtxt('h.csv')
cost = np.genfromtxt('cost.csv')
costl = np.genfromtxt('costl.csv')
SLN = np.genfromtxt("SLN.csv",delimiter=';')
SLNpred = np.genfromtxt("SLNpredicted.csv",delimiter=';')


order = ["V1","V2","V4","DP","MT","8m",
		"5","8l","TEO","2","F1","STPc","7A","46d","10",
		"9/46v","9/46d","F5","TEpd","PBr","7m","7B","F2",
		"STPi","ProM","F7","8B","STPr","24c"]

hnorm = h/max(h)
hnorm_sort = sorted(hnorm)

sort_index = [0]*len(hnorm)
for i in range(len(hnorm)):
	for j in range(len(hnorm_sort)):
		if(hnorm[i] == hnorm_sort[j]):
			sort_index[i]=j

y_labels = []
for i in sort_index:
	y_labels.append(order[i])

grid_size =(6,5)

plt.subplot2grid(grid_size, (0,0),rowspan=2,colspan=3)
plt.plot(cost)
plt.title('cost')

plt.subplot2grid(grid_size, (2,0),rowspan=2,colspan=3)
plt.plot(costl)
plt.title('cost+logbarrier')


plt.subplot2grid(grid_size, (4,0),rowspan=2,colspan=3)
plt.plot(hnorm,'o')
plt.title("hierarchy values")
plt.xticks(range(29),order,rotation=90.)


plt.subplot2grid(grid_size, (0,3),rowspan=3,colspan=2)
for i in range(len(SLN)):
	for j in range(len(SLN[i])):
		plt.scatter(SLN[i][j],SLNpred[i][j])
plt.xlabel("observed SLN")
plt.ylabel("predicted SLN")

plt.subplot2grid(grid_size,(3,3), rowspan=3,colspan=2)
plt.plot(hnorm,sort_index,'o')
plt.yticks(range(29),y_labels)
plt.xlabel("hierarchy")


plt.tight_layout()
plt.show()


