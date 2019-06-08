import numpy as np

def catenariaCabo(C1, H, L, DX):
    
	X = np.arange(-L/2,DX+L/2,DX)
	Ytemp = H - (C1 * (np.cosh(X/C1) - 1))
	Y = H - (Ytemp - min(Ytemp))
	LCABO = 2*C1*np.sinh(L/(2*C1))

	return X, Y, LCABO