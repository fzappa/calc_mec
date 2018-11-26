using PyCall
@pyimport numpy as np

function catenaria_cabo(C1, H, L, DX)

    X = np.arange(-L/2,DX+L/2,DX)'
    Ytemp = H .- (C1 * (cosh.(X/C1) .- 1)) 
    Y = H .- (Ytemp .- minimum(Ytemp))
    LCABO = 2*C1*sinh.(L/(2*C1))

    return X, Y, LCABO
	
end

