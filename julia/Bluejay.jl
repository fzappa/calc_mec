#!/usr/bin/env julia
using Printf

include("funcoes/catenaria_cabo.jl")
include("funcoes/flecha_cabo.jl")

print("\n#### CABO BLUEJAY - NEXANS - CIRCUITO DE 765KV ####\n\n");

NCfeixe = 4            ; #Número de condutores por feixe
Dfeixe = 0.457         ; #Diâmetro do feixe (m)
VAO = 294.3              ; #Comprimento do vão
H=25                   ; #Altura de partida
DC = [-14.34;0;14.34]  ; #Distancia entre os feixes
EDS   = 20/100         ; #(percentual)
DX = 0.1               ; #Comprimento da divisão da catenaria(Tricamp)

# CABO BLUEJAY - CIRCUITO DE 765KV
# http://www.nexans.com.br/eservice/Brazil-pt_BR/fileLibrary/Download_540134436/Brazil/files/catalogo%20nus_maio%202013.pdf

SECAO = 603.09e-6      ; #(mm² -> m²)
PHI   = 31.96e-3       ; #(mm -> m) (Diâmetro do cabo)
MASSA = 1867.6e-3      ; #(kgf/km -> kgf/m)
T_RUP = 13526          ; #(kgf)

DL = VAO/2;

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

@printf("EDS = %.2f", EDS*100);
@printf("DL = %.2f m", DL);
#%%%%% COMPRIMENTO DO VÃO X FLECHA %%%%%%%
###########  Julia 1.0 ###########
#Para plotar o grafico
#julia> using Pkg
#julia> Pkg.add("PyCall")
#julia> Pkg.add("Conda")
#julia> using Conda
#julia> Conda.add("matplotlib")
############################
using PyCall
@pyimport matplotlib.pyplot as plt
#using PyPlot

#figure(1)
X,Y,LCABO = catenaria_cabo(C1,H,VAO,DX);

######################### CATENARIA #########################
#Dados da catenaria
@printf("Comprimento do cabo para o vão de %.2f m: %.2f m", VAO, LCABO);
@printf("H(max) = %.2f m",H);
@printf("H(min) = %.2f m\n\n", minimum(Y));

#Desenha a catenária
plt.figure(1);
display(plt.plot(X', Y', color="red",marker=false, label=string("Vão de ", VAO,"m")));
display(plt.title("Flexa x Comprimento do vão"));
plt.xlabel("Comprimento do vão [m]");
plt.ylabel("Flecha [m]");
plt.grid(true);
plt.legend(loc="lower right",fancybox=true);

#Controle dos eixos
ax = plt.gca();
ax[:set_xlim]([-DL;DL])
ax[:set_ylim]([0;H+(H*0.1)])

#plt.show(1);
######################## FIM CATENARIA ########################

######################### FEIXE #########################
ANGC = 360/NCfeixe; #Angulo entre os condutores
PC = collect(0:ANGC:359); #Posicao dos condutores no circulo
PX = cosd.(PC)*(Dfeixe/2); #Cria o array de posicoes dos condutores
PY = sind.(PC)*(Dfeixe/2);

plt.figure(2);
display(plt.scatter(PX,PY,s=PHI*1e4,alpha=0.5));
display(plt.title("Configuração do feixe"));
plt.xlabel("Largura [m]");
plt.ylabel("Altura [m]");
plt.grid(true);

#Distribucao dos feixes
Cx=[PX+DC[1]' PX+DC[2]' PX+DC[3]']; #Configuracao do circuito
Cy=[PY+H PY+H PY+H];

plt.figure(3);
display(plt.scatter(Cx,Cy,s=PHI*1e3,alpha=0.5));
display(plt.title("Disposição dos feixes"));
plt.xlabel("Largura [m]");
plt.ylabel("Altura [m]");
plt.grid(true);

#Controle dos eixos
ax = plt.gca();
ax[:set_xlim]([DC[1]+0.1*DC[1];DC[3]+0.1*DC[3]])
ax[:set_ylim]([0;H+0.1*H])


plt.show();
