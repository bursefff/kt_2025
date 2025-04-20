import matplotlib
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np

from diffractio import degrees, plt, um, np
from diffractio.scalar_masks_XY import Scalar_mask_XY
from diffractio.scalar_sources_XY import Scalar_source_XY

num_pixels = 512

length = 5000*um
x0 = np.linspace(-length/2, length/2, num_pixels)
y0 = np.linspace(-length/2, length/2, num_pixels)
wavelength = 0.6238*um

u1 = Scalar_source_XY(x=x0, y=y0, wavelength=wavelength)
u1.gauss_beam(r0=(0*um, 0*um), w0=(1000*um, 1000*um), z0=0*um,
    A=1, theta=0*degrees, phi=0*degrees)


t1 = Scalar_mask_XY(x=x0, y=y0, wavelength=wavelength)
t1.image(filename="fork1200.png", invert=False)

u2 = u1 * t1

u3 = u2.RS(z=300000*um, new_field=True)
u3.draw(kind="intensity")
plt.savefig('res1200.png')
