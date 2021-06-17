# Feito por Matheus de Moraes Cavazotti (github.com/mcavazotti)

# USO:
# Para desenhar um arquivo de saída do Trabalho 1, faça:
# $ python3 draw.py < arquivo

import matplotlib
import matplotlib.pyplot as plt

if __name__ == "__main__":
    print('matplotlib version: {}'.format(matplotlib.__version__))

    fig, ax = plt.subplots()

    # Ler número de pontos
    numPoints = int(input())
    pointList = []

    for p in range(numPoints):
        # Ler coordenadas dos pontos
        x1, y1, x2, y2, t = map(float, input().split())
        ax.plot([x1, x2], [y1, y2], color="#000", lw=1)
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