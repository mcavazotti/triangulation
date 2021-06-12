# Feito por Matheus de Moraes Cavazotti (github.com/mcavazotti)

# USO:
# Para desenhar um arquivo de saída do Trabalho 1, faça:
# $ python3 draw.py < arquivo

import matplotlib
import matplotlib.pyplot as plt

# Definição de Ponto
class Point:
    def __init__(self, x: float = 0, y: float = 0) -> None:
        self.x = x
        self.y = y

    def __str__(self) -> str:
        return "({},{})".format(self.x, self.y)

    def __repr__(self) -> str:
        return self.__str__()


# Definição de Triângulo
class Triangle:
    def __init__(self, p1: Point, p2: Point, p3: Point) -> None:
        self.points = []
        self.points.append(p1)
        self.points.append(p2)
        self.points.append(p3)
        # Adicionar o primeiro ponto no fim da lista para fechar o triângulo
        self.points.append(p1)

    def __str__(self) -> str:
        return str(self.points[0:3])

    def __repr__(self) -> str:
        return self.__str__()


if __name__ == "__main__":
    print('matplotlib version: {}'.format(matplotlib.__version__))

    # Ler número de pontos
    numPoints = int(input())
    pointList = []

    for p in range(numPoints):
        # Ler coordenadas dos pontos
        x, y = map(float, input().split())
        pointList.append(Point(x, y))

    # Adicionar o primeiro ponto no fim da lista para fechar o polígono
    pointList.append(pointList[0])
    print("Pontos: ", pointList[0:len(pointList)-1])

    # Ler número de triângulos
    numTris = int(input())
    trisList = []

    for t in range(numTris):
        # Ler o índice dos pontos e ignorar o resto (não é necessário para plotar a figura)
        p1, p2, p3, *rest = map(int, input().split())
        trisList.append(
            Triangle(pointList[p1 - 1], pointList[p2 - 1], pointList[p3 - 1]))

    print("Triangulos: ", trisList)

    # Inicializar figura
    fig, ax = plt.subplots()

    # Plotar triângulos em vermelho
    for t in trisList:
        ax.plot(list(map(lambda p: p.x, t.points)), list(
            map(lambda p: p.y, t.points)), color='#f00', lw=1)

    # Plotar polígono em cinza
    ax.plot(list(map(lambda p: p.x, pointList)), list(
        map(lambda p: p.y, pointList)), color='#777', lw=3)

    # Plotar pontos em preto
    ax.plot(list(map(lambda p: p.x, pointList)), list(
        map(lambda p: p.y, pointList)),'o', color='#000', lw=3)

    # Ajustar a escala para não ter distorção
    plt.axis('scaled')

    # Mostrar figura
    plt.show()
