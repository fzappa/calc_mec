#!/usr/bin/julia

using Pkg

print("\n#### Instalando dependências ####\n\n");

print("Atualizando base...\n");
Pkg.update();

print("Instalando PyCall (Julia)...\n");
Pkg.add("PyCall");

print("Instalando Matplotlib (Python)...\n");
print("# pacman -S python-pip (Arch Linux) \n");
run(`sudo pip install matplotlib`);

print("Instalar o pacote tk \n");
print("# pacman -S tk (Arch Linux) \n");
print("# apt install tk (Ubuntu) \n");