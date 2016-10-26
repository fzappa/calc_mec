#!/usr/bin/julia

include("funcoes/catenaria_cabo.jl")
include("funcoes/flecha_cabo.jl")

print("\n#### CABO RAIL - NEXANS - CIRCUITO DE 765KV ####\n\n");

DIST_CONDUTORES = [14.34;0;-14.34];
DX = 5;              #Comprimento da divisão da catenaria
DL = 250;

# CABO RAIL - CIRCUITO DE 765KV
# http://www.nexans.com.br/eservice/Brazil-pt_BR/fileLibrary/Download_540134436/Brazil/files/catalogo%20nus_maio%202013.pdf
# Corrente máxima = 1120A
# Bobina = 190/100
# Fios = 45/7


SECAO = 516.75e-6      ; #(mm² -> m²)
PHI   = 29.59e-3       ; #(mm -> m) (Diâmetro do cabo)
MASSA = 1600.2e-3      ; #(kgf/km -> kgf/m)
T_RUP = 11768          ; #(kgf)

VAO = 500; # Comprimento do vão [m]
H   = 35 ; # Altura de partida [m]

EDS   = 20/100         ; #(percentual)

println(@sprintf "EDS = %5.2f %%" EDS*100);
println(@sprintf "DL = %5.2f m" DL);
ALPHA_FINAL = 20.9e-6  ; # ºCe-1
ELAST_FINAL = 6679e6   ;
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
@pyimport matplotlib.pyplot as plt
#using PyPlot

#figure(1)
X,Y,LCABO = catenaria_cabo(C1,H,VAO,DX);

println(@sprintf "Comprimento do cabo para o vão de %dm: %5.2f m" VAO LCABO);
println(@sprintf "H = %5.2f m\n\n" minimum(Y));

display(plt.plot(X', Y', color="red",marker="None", label=string(VAO,"m")));
display(plt.title("Flexa x Comprimento do vão"));
plt.xlabel("Comprimento do vão [m]");
plt.ylabel("Flecha [m]");
plt.grid("on");
plt.legend(loc="lower right",fancybox="true");

#Controle dos eixos
ax = plt.gca();
ax[:set_xlim]([-VAO/2;VAO/2])
ax[:set_ylim]([0;H+5])


plt.show(1);


#%%%%% FIM VÃO X FLECHA %%%%%%%


