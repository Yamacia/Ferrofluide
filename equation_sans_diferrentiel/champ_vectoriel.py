import numpy as np
import matplotlib.pyplot as plt

x, y = np.meshgrid(np.linspace(-5, 5, 10),
                   np.linspace(-5, 5, 10))

i=0.1

a=3*i*x*2/(4*np.sqrt(x**2+y**2)**3)
b=(i/(4*np.sqrt(x**2+y**2)))*(3*2/(np.sqrt(x**2+y**2)**2)-1)

u = -y/np.sqrt(x**2 + y**2)
v = x/(x**2 + y**2)

plt.quiver(x, y, u, v, color='g')
plt.title('Vector Field')

plt.xlim(-7, 7)
plt.ylim(-7, 7)

plt.grid()
plt.show()