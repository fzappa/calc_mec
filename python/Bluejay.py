#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
sys.path.insert(0,'catenaria/funcoes.py')

import numpy as np
import matplotlib.pyplot as plt

import catenaria.funcoes as eq

print("\n#### CALCULO MECANICO ####")
print("\n#### CABO BLUEJAY - NEXANS - CIRCUITO DE 765KV ####\n\n")

NCfeixe = 4            #Número de condutores por feixe
Dfeixe = 0.457         #Diâmetro do feixe (m)
VAO = 294.3            #Comprimento do vão
H=25.0                   #Altura de partida
DC = [-14.34,0.0,14.34]    #Distancia entre os feixes
EDS   = 20.0/100.0         #(percentual)
DX = 0.1               #Comprimento da divisão da catenaria(Tricamp)

# CABO BLUEJAY - CIRCUITO DE 765KV
# http://www.nexans.com.br/eservice/Brazil-pt_BR/fileLibrary/Download_540134436/Brazil/files/catalogo%20nus_maio%202013.pdf

SECAO = 603.09e-6       #(mm² -> m²)
PHI   = 31.96e-3        #(mm -> m) (Diâmetro do cabo)
MASSA = 1867.6e-3       #(kgf/km -> kgf/m)
T_RUP = 13526.0           #(kgf)

DL = VAO/2.0

ALPHA_FINAL = 20.9e-6   # ºCe-1
ELAST_FINAL = 6628e6   
PMINIMO = 76.0            # percentual
PMAXIMO = 108.0           # percentual

TCop   = 75.0             #Temperatura operação (ºC)
T_AMB  = 25.0             #Temperatura ambiente (ºC)
T_MAX  = 39.2           #Temperatura operação (ºC)
T_MIN  = -0.3           #Temperatura operação (ºC)
VENTO_MED = 0.822       #km/h -> m/s

T0 = T_RUP*EDS         
p = MASSA               #C1 = p
C1 = T0/p	       

print("EDS = {0:4,.2f} %".format(EDS*100))
print("DL = {0:4,.2f} m".format(DL))

#%%%%% COMPRIMENTO DO VÃO X FLECHA %%%%%%%

X,Y,LCABO = eq.catenariaCabo(C1,H,VAO,DX)

######################### CATENARIA #########################



#Dados da catenaria
print("Comprimento do cabo para o vão de {0:4,.2f}m: {1:4,.2f}m".format(VAO,LCABO))
print("H(max) = {0:4,.2f} m".format(H))
print("H(min) = {0:4,.2f} m".format(np.min(Y)))

#Desenha a catenária
plt.figure(1)
plt.plot(X,Y, color="red")
plt.title("Flexa x Comprimento do vão - {0:4,.2f} m".format(VAO))
plt.xlabel("Comprimento do vão [m]")
plt.ylabel("Flecha [m]")
plt.grid(True)
plt.ylim(0,H+H*0.1)
plt.xlim(-DL,DL)

#plt.text(0, np.min(Y) + 3, r'$\mu=100,\ \sigma=15$')

# ######################## FIM CATENARIA ########################

# ######################### FEIXE #########################
ANGC = 360/NCfeixe #Angulo entre os condutores
PC = np.arange(0,360,ANGC) #Posicao dos condutores no circulo
PX = np.cos(np.deg2rad(PC))*(Dfeixe/2.0) #Cria o array de posicoes dos condutores
PY = np.sin(np.deg2rad(PC))*(Dfeixe/2.0)

plt.figure(2)
plt.scatter(PX,PY,s=PHI*1e4,alpha=0.5)
plt.title("Configuração do feixe")
plt.xlabel("Largura [m]")
plt.ylabel("Altura [m]")
plt.grid(True)

#Distribucao dos feixes
Cx=[PX+DC[0], PX+DC[1], PX+DC[2]] #Configuracao do circuito
Cy=[PY+H, PY+H, PY+H]

plt.figure(3)
plt.scatter(Cx,Cy,s=PHI*1e3,alpha=0.5)
plt.title("Disposição dos feixes")
plt.xlabel("Largura [m]")
plt.ylabel("Altura [m]")
plt.grid(True)

plt.ylim(0,H+0.1*H)
#plt.xlim(-DL,DL)



plt.show()
