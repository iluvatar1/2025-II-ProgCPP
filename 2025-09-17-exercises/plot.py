import numpy as np 
import matplotlib.pyplot as plt 

# read data
x, y = np.loadtxt("data.txt", unpack = True)

# plot data
fig, ax = plt.subplots()
ax.plot(x, y, '-o', label="data")
ax.legend()
ax.set_xlabel('n')
ax.set_ylabel('h')
#plt.show()
fig.savefig('fig2.pdf')
