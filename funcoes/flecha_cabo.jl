function flecha_cabo(MASSA, VAO, T0, PHI, VENTO_MED)
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

    FLECHA = (MASSA*(VAO^2))/(8*T0);

    FORCA_VENTO = (PHI/2)*(VENTO_MED)^2;            #% kgf
    BALANCO = atand(FORCA_VENTO/MASSA);             #% graus
    FORCA_EQUIV = ((MASSA^2)+(FORCA_VENTO^2))^(1/2); 
    FLECHA_VENTO = (FORCA_EQUIV*(VAO^2))/(8*T0);
    ESFORCO_LATERAL = ((FORCA_VENTO*VAO)/2);

    return FLECHA, FLECHA_VENTO, BALANCO, ESFORCO_LATERAL

end

