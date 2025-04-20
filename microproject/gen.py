import numpy as np
import matplotlib.pyplot as plt
dpi = 1200 #dots per inch
size = 5000 #microns
m = 4 #topological charge
npixels = int(dpi *  size / 10000 /2.5)
d = 100 #grating period
x = np.linspace(-size/2, size/2, npixels)
y = np.linspace(-size/2, size/2, npixels)
t = [[0 for j in range(npixels)] for i in range(npixels)]
for i in range(npixels):
    for j in range(npixels):
        ans = 0.5 * (1 + np.cos(2 * np.pi/d * y[j] - m * np.arctan2(y[j], x[i])))
        t[i][j] = ans
        # if ans < 0.5:
        #     t[i][j] = 0
        # else:
        #     t[i][j] = 1
plt.imshow(t, interpolation='none', cmap="Greys")
plt.axis('off')
plt.savefig('fork1200.png', bbox_inches='tight')