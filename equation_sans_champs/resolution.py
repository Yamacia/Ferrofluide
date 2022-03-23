import numpy as np

# Définition des paramètres du système
g=9.81
ro1=1.2
ro2=1000
gam=0.018
A=1/gam*(ro1-ro2)

# Définition des conditions initiales
x0 = 0.01
y0 = 1.73

def f(Y, t) :
    u, v = Y # On extrait u et v de Y, voir système différentiel asssocié
    return [ u, -A*u ]

T = [ 0.1*i for i in range(110) ]#resolution entre 0 et 11
Y0 = [ 3.0, 4.0 ]

from scipy.integrate import odeint
Y = odeint(f, Y0, T)

from matplotlib.pyplot import plot, legend, show
plot(T, Y[:, 0], 'r--', label="y0(t)")
plot(T, Y[:, 1], 'b', label="y1(t)")
legend(loc="upper left")
show()
