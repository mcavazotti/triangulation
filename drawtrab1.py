#!/usr/bin/env python
# -*- coding: utf-8 -*-

# USO:
# Para desenhar um arquivo de saída do Trabalho 1, faça:
# $ python drawtrab1.py < arquivo


# tutorial completo em
# https://matplotlib.org/stable/tutorials/introductory/pyplot.html#sphx-glr-tutorials-introductory-pyplot-py

import sys
from matplotlib.pyplot import figure, show

# leitura de um polígono na forma
# n (número de vértices)
# x1 y1 (coordenadas dos vértices)
# ...
# xn yn
def le_poligono():
    global ax
    global ay
    global maxx
    global maxy
    global minx
    global miny

    n=int(sys.stdin.readline()) #
    for i in range(n):
        a=(sys.stdin.readline().split())
        x = int(a[0])
        y = int(a[1])
    
        ax.append(x)
        ay.append(y)
        if x > maxx:
            maxx = x
        if x < minx:
            minx = x
        if y > maxy:
            maxy = y
        if y < miny:
            miny = y
        ax.append(ax[0])
        ay.append(ay[0])

        print( ax)
        print( ay)

# leitura de um triângulo na forma
# n (número de vértices)
# x1 y1 (coordenadas dos vértices)
# ...
# xn yn
def le_triangulo():
    global ax
    global ay
    global x_triangulos
    global y_triangulos

    tx = []
    ty = []
    vf = []
    a=(sys.stdin.readline().split())
    for i in range(6):
        vf.append(int(a[i]))

    print( "triangulo: ", vf)
    for i in range(3):
        tx.append(ax[vf[i]-1])
        ty.append(ay[vf[i]-1])

    tx.append(ax[vf[0]-1])
    ty.append(ay[vf[0]-1])

    print( tx)
    print( ty)

    x_triangulos.append(tx)
    y_triangulos.append(ty)

# leitura da entrada
def le_entrada():
    global n_triangulos
    global x_triangulos
    global y_triangulos
    
    le_poligono()
    
    n_triangulos=int(sys.stdin.readline()) #

    for t in range(n_triangulos):
        le_triangulo()
        
maxx = -99999
maxy = -99999
minx = 99999
miny = 99999

ax = []
ay = []
x_triangulos = []
y_triangulos = []

le_entrada()

dx = maxx - minx +5
dy = maxy - miny +5
print( dx, dy)
    
for t in range(n_triangulos):
    print( "triangulo ", t, ":")
    print( x_triangulos[t])
    print( y_triangulos[t])


#dimensoes da figura num retangulo de 16 por 21
fig = figure(1,figsize=(dx,dy))
#em xlim e ylim coloca-se os limites da coisa nos respect eixos
desenho = fig.add_subplot(111, autoscale_on=False, xlim=(minx- 1,maxx+ 1), ylim=(miny-1,maxy+1))
desenho.set_aspect('equal', 'box')

# for t in range(len(ax)):
#     desenho.plot(ax[t],ay[t],lw=3, color='#000')

# #gravar na imagem os triangulos em vermelho
# for t in range(n_triangulos):
#     line, = desenho.plot(x_triangulos[t], y_triangulos[t], lw=3, color='#f00')

#gravar na imagem os poligonos em preto
line, = desenho.plot(ax, ay, lw=3, color='black')
print(ax,ay)

show()
