#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <Windows.h>


void generateAdjacencyMatrix(int n);
int countEdges(int** adjacencyMatrix, int n);
void findVertices(int** adjacencyMatrix, int n);
void generateIncidenceMatrix(int n, int** adjacencyMatrix);
void findVerticesByIncidenceMatrix(int n, int** incidenceMatrix, int edgeCount);



void generateAdjacencyMatrix(int n) {
    int** adjacencyMatrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        adjacencyMatrix[i] = (int*)malloc(n * sizeof(int));
    }

    // Инициализация матрицы нулями
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }

    // Заполнение матрицы смежности
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int edge = rand() % 2;
            adjacencyMatrix[i][j] = edge;
            adjacencyMatrix[j][i] = edge; // Для неориентированного графа
        }
    }

    // Вывод матрицы на экран
    printf("Матрица смежности для неориентированного графа:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }

    // Подсчет рёбер
    int edgeCount = countEdges(adjacencyMatrix, n);
    printf("Количество рёбер в графе: %d\n", edgeCount);

    // Нахождение вершин
    findVertices(adjacencyMatrix, n);

    generateIncidenceMatrix(n, adjacencyMatrix);

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(adjacencyMatrix[i]);
    }
    free(adjacencyMatrix);
}

int countEdges(int** adjacencyMatrix, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            count += adjacencyMatrix[i][j];
        }
    }
    return count;
}


void findVertices(int** adjacencyMatrix, int n) {
    int* isolated = (int*)malloc(n * sizeof(int));
    int* terminal = (int*)malloc(n * sizeof(int));
    int* dominating = (int*)malloc(n * sizeof(int));
    int isolatedCount = 0, terminalCount = 0, dominatingCount = 0;

    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            degree += adjacencyMatrix[i][j];
        }

        if (degree == 0) {
            isolated[isolatedCount++] = i; // Изолированная вершина
        }
        else if (degree == 1) {
            terminal[terminalCount++] = i; // Концевая вершина
        }

        // Проверка на доминирующую вершину
        int isDominating = 1; // Предполагаем, что вершина доминирующая
        for (int j = 0; j < n; j++) {
            if (i != j && adjacencyMatrix[i][j] == 0) {
                isDominating = 0; // Если есть хотя бы одна не смежная вершина
                break;
            }
        }
        if (isDominating) {
            dominating[dominatingCount++] = i; // Доминирующая вершина
        }
    }

    // Вывод результатов
    printf("Изолированные вершины: ");
    for (int i = 0; i < isolatedCount; i++) {
        printf("%d ", isolated[i] + 1);
    }
    printf("\n");

    printf("Концевые вершины: ");
    for (int i = 0; i < terminalCount; i++) {
        printf("%d ", terminal[i] + 1);
    }
    printf("\n");

    printf("Доминирующие вершины: ");
    for (int i = 0; i < dominatingCount; i++) {
        printf("%d ", dominating[i] + 1);
    }
    printf("\n");

    // Освобождение памяти
    free(isolated);
    free(terminal);
    free(dominating);
}

void findVerticesByIncidenceMatrix(int n, int** incidenceMatrix, int edgeCount) {
    int* isolated = (int*)malloc(n * sizeof(int));
    int* terminal = (int*)malloc(n * sizeof(int));
    int* dominating = (int*)malloc(n * sizeof(int));
    int isolatedCount = 0, terminalCount = 0, dominatingCount = 0;

    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < edgeCount; j++) {
            degree += incidenceMatrix[i][j];
        }

        if (degree == 0) {
            isolated[isolatedCount++] = i; // Изолированная вершина
        }
        else if (degree == 1) {
            terminal[terminalCount++] = i; // Концевая вершина
        }

        // Проверка на доминирующую вершину
        int isDominating = 1; // Предполагаем, что вершина доминирующая
        for (int j = 0; j < n; j++) {
            if (i != j && incidenceMatrix[j][0] == 0) {
                isDominating = 0; // Если есть хотя бы одна не смежная вершина
                break;
            }
        }
        if (isDominating) {
            dominating[dominatingCount++] = i; // Доминирующая вершина
        }
    }

    // Вывод результатов
    printf("Изолированные вершины: ");
    for (int i = 0; i < isolatedCount; i++) {
        printf("%d ", isolated[i] + 1);
    }
    printf("\n");

    printf("Концевые вершины: ");
    for (int i = 0; i < terminalCount; i++) {
        printf("%d ", terminal[i] + 1);
    }
    printf("\n");

    printf("Доминирующие вершины: ");
    for (int i = 0; i < dominatingCount; i++) {
        printf("%d ", dominating[i] + 1);
    }
    printf("\n");

    // Освобождение памяти
    free(isolated);
    free(terminal);
    free(dominating);
}




void generateIncidenceMatrix(int n, int** adjacencyMatrix) {
    int edgeCount = countEdges(adjacencyMatrix, n);
    // Создание матрицы инцидентности с количеством вершин в строках и количеством рёбер в столбцах
    int** incidenceMatrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        incidenceMatrix[i] = (int*)malloc(edgeCount * sizeof(int));
        for (int j = 0; j < edgeCount; j++) {
            incidenceMatrix[i][j] = 0; // Инициализация нулями
        }
    }

    int edgeIndex = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                incidenceMatrix[i][edgeIndex] = 1; // Инцидентность вершины i
                incidenceMatrix[j][edgeIndex] = 1; // Инцидентность вершины j
                edgeIndex++;
            }
        }
    }

    // Вывод матрицы инцидентности, теперь рёбра в столбцах
    printf("Матрица инцидентности:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < edgeCount; j++) {
            printf("%d ", incidenceMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\nРазмер графа определяется количеством столбов в матрице инцинтентности. \nРазмер графа: %d\n", edgeCount);

    findVerticesByIncidenceMatrix(n, incidenceMatrix, edgeCount);

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(incidenceMatrix[i]);
    }
    free(incidenceMatrix);
}



int main() {
    setlocale(LC_ALL, "");
    srand((unsigned int)time(0)); // Инициализация генератора случайных чисел

    int n;
    printf("Введите количество вершин графа: ");
    scanf("%d", &n);

    generateAdjacencyMatrix(n);
    return 0;
}