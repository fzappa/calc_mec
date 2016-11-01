#!/usr/bin/julia

include("Funcoes.jl")

print("\n#### CABO BLUEJAY - NEXANS - CIRCUITO DE 765KV ####\n\n");

DIST_CONDUTORES = [14.34;0;-14.34];
DX = 10;              #Comprimento da divisão da catenaria
DL = 250;

# CABO BLUEJAY - CIRCUITO DE 765KV
# http://www.nexans.com.br/eservice/Brazil-pt_BR/fileLibrary/Download_540134436/Brazil/files/catalogo%20nus_maio%202013.pdf

SECAO = 603.09e-6      ; #(mm² -> m²)
PHI   = 31.96e-3       ; #(mm -> m) (Diâmetro do cabo)
MASSA = 1867.6e-3      ; #(kgf/km -> kgf/m)
T_RUP = 13526          ; #(kgf)

VAO_1 = 300; H1=51.3   ; #(m)
VAO_2 = 500; H2=51.3   ; #(m)
VAO_3 = 1000; H3=51.3  ; #(m)

EDS   = 20/100         ; #(percentual)

println(@sprintf "EDS = %5.2f m" EDS*100);
println(@sprintf "DL = %5.2f m" DL);
ALPHA_FINAL = 20.9e-6  ; # ºCe-1
ELAST_FINAL = 6628e6   ;
PMINIMO = 76           ; # percentual
PMAXIMO = 108          ; # percentual

TCop   = 75            ; #Temperatura operação (ºC)
T_AMB  = 25            ; #Temperatura ambiente (ºC)
T_MAX  = 39.2          ; #Temperatura operação (ºC)
T_MIN  = -0.3          ; #Temperatura operação (ºC)

VENTO_MED = 0.822      ; #km/h -> m/s


T0 = T_RUP*EDS         ;
p = MASSA              ; #C1 = p
C1 = T0/p	       ;


#%%%%% COMPRIMENTO DO VÃO X FLECHA %%%%%%%

#Para plotar o grafico
using PyCall
#@pyimport matplotlib.pyplot as plt
using PyPlot

#figure(1)
X1,Y1,LCABO1 = catenaria_cabo(C1,H1,VAO_1,DX);
X2,Y2,LCABO2 = catenaria_cabo(C1,H2,VAO_2,DX);
X3,Y3,LCABO3 = catenaria_cabo(C1,H3,VAO_3,DX);

println(@sprintf "Comprimento do cabo para o vão de 500m: %5.2f m" LCABO2);


display(plot(X1', Y1', color="red", label="300m"));
display(plot(X2', Y2', color="green",label="500m"));
display(plot(X3', Y3', color="blue",label="1000m"));

display(title("Flexa x Comprimento do vão"));
xlabel("Comprimento do vão [m]");
ylabel("Flecha [m]");
grid("on");
legend(loc="lower right",fancybox="true"); 
show(1);


#%%%%% FIM VÃO X FLECHA %%%%%%%

FLECHA_300,FLECHA_VENTO_300,BALANCO_300,ESFORCO_LATERAL_300 = flecha_cabo(MASSA, VAO_1, T0, PHI, VENTO_MED);
FLECHA_500,FLECHA_VENTO_500,BALANCO_500,ESFORCO_LATERAL_500 = flecha_cabo(MASSA, VAO_2, T0, PHI, VENTO_MED);
FLECHA_1000,FLECHA_VENTO_1000,BALANCO_1000,ESFORCO_LATERAL_1000 = flecha_cabo(MASSA, VAO_3, T0, PHI, VENTO_MED);




#% % Gera Eletrodos do feixe - Tricamp
#% % Catenária
#% %
#% for i=1:3;
#%     gera_eletrodos_feixe(1,i+1,1,20,0.032,X2,Y2,0.457,DIST_CONDUTORES(i));
#% end;



#XM = [-DL/2;0;DL/2];
#YM = [min(Y2);min(Y2);min(Y2)];

println(@sprintf "H = %5.2f m" minimum(Y2));


#% Gera Eletrodos do feixe - Tricamp
#% Cabo aproximado
#% 
#for i=1:3;
#    gera_eletrodos_feixe(1,i+1,1,20,0.032,XM,YM,0.457,DIST_CONDUTORES(i));
#end;


readline(STDIN)

gc();


#M = zeros(length(X2),1);
#D = 0.457/2; 

#X=X2';
#Y=M - D + DIST_CONDUTORES[2];
#Z=(Y2+D)'; 

#using Plots

#plot3d(X,Y,Z);



