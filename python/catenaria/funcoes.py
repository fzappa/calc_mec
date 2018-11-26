import numpy as np

def catenariaCabo(C1, H, L, DX):
    
	X = np.arange(-L/2,DX+L/2,DX)
	Ytemp = H - (C1 * (np.cosh(X/C1) - 1))
	Y = H - (Ytemp - min(Ytemp))
	LCABO = 2*C1*np.sinh(L/(2*C1))

	return X, Y, LCABO


def flecha_cabo(MASSA, VAO, T0, PHI, VENTO_MED):

	#%
	#% Função que calcula a flecha de um cabo
	#% Autor: Alan Franco
	#%
	#%   Utilização:
	#% 
	#%   [FLECHA FLECHA_VENTO BALANCO ESFORCO_LATERAL] = flecha_cabo(MASSA, VAO, T0, PHI, VENTO_MED)
	#%

	#%%%%%%%%%%%%%%%%%%%%%% Equações %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	#%%% (Livro: Projetos Mecânicos das Linhas Aéreas de Transmissão) 
	#%%% Labegalini, Fuchs, Almeida. Pg 21, 2ª edição  
	#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    FLECHA = (MASSA*(VAO**2))/(8*T0);

    FORCA_VENTO = (PHI/2)*(VENTO_MED)**2;            #% kgf
    BALANCO = np.arctan(FORCA_VENTO/MASSA);             #% graus
    FORCA_EQUIV = ((MASSA**2)+(FORCA_VENTO**2))**(1/2); 
    FLECHA_VENTO = (FORCA_EQUIV*(VAO**2))/(8*T0);
    ESFORCO_LATERAL = ((FORCA_VENTO*VAO)/2);

    return FLECHA, FLECHA_VENTO, BALANCO, ESFORCO_LATERAL
