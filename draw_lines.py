# Feito por Matheus de Moraes Cavazotti (github.com/mcavazotti)

# USO:
# Para desenhar um arquivo de saída do Trabalho 1, faça:
# $ python3 draw.py < arquivo

import matplotlib
import matplotlib.pyplot as plt
from random import random

if __name__ == "__main__":
    print('matplotlib version: {}'.format(matplotlib.__version__))

    fig, ax = plt.subplots()

    # Ler número de faces
    numFaces = int(input())
    print(numFaces)
    pointList = []
    for f in range(numFaces):
        numPoints = int(input())
        print(numPoints)
        pointList.clear()
        for p in range(numPoints):
            x1,y1 = map(float, input().split())
            print(x1,y1)
            pointList.append((x1,y1))
        ax.fill(list(map(lambda p: p[0], pointList)), list(
            map(lambda p: p[1], pointList)), (random(), random(), random()))


    # Ler número de pontos
    numPoints = int(input())
    pointList = []

    for p in range(numPoints):
        # Ler coordenadas dos pontos
        x1, y1, x2, y2, t, a = map(float, input().split())
        if a == 0:
            c = "#000"
        else:
            c = "#f00"
        ax.plot([x1, x2], [y1, y2], color=c, lw=1)
        if t == 0:
            ax.scatter(x1, y1, color="#000", marker="D")
        if t == 1:
            ax.scatter(x1, y1, color="#000", marker="s")
        if t == 2:
            ax.scatter(x1, y1, color="#000", marker="o")
        if t == 3:
            ax.scatter(x1, y1, color="#000", marker="^")
        if t == 4:
            ax.scatter(x1, y1, color="#000", marker="v")

    # Ajustar a escala para não ter distorção
    plt.axis('scaled')

    # Mostrar figura
    plt.show()
