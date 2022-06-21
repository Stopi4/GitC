// http://ekmair.ukma.edu.ua/bitstream/handle/123456789/18324/Haldetskyi_Zadacha_komivoiazhera_yak_zadacha_binarnoho_LP.pdf?sequence=1&isAllowed=y
// https://www.mathros.net.ua/znahodzhennja-rozvjazku-zadachi-komivojazhera-metodom-oserednenyh-koeficijentiv.html
// https://www.programiz.com/dsa/graph-adjacency-list
// 
// !!
// https://uchimatchast.ru/teoriya/algoritm-littla-primer-1/
// !! алгоритм Літтла

// Перетворити реалізацію задачі у функцію. 
// Замінити тип даних ваги на double (не обов'язково).
// Розбити функцію на такі функції:
// 1) Алгоритм Дейкстри для всіх вершин(повертає вказівник на двохмірний масив).
// 2) Підрахунок шляху(повертає адресу масиву з шляхом).
// 3) Підрахунок ваги шляху(повертає вагу шляху).
// Зробити підрахунок шляху.
// Дописати перевірку правильності введених даних.
// Створити функцію очищення даних.
// Створити функцію зчитування та перевірки даних з текстових файлів.
// Створити інші версії:
// 1) Масив із зазначеними індексами.
// 2) Масив підрахунку індексів.
// 3) Змінена реалізація способу задання графа.




#include <stdio.h>
#include <Windows.h>
#include <limits.h>
//#define NUMADJ 5
#define WEIGHT_INT sizeof(int)

typedef struct AdjacencyListOfVertices {
	int vertex; // Вершина.
	int weight;
	//char edge_turns_in; // 1 - True, 0 - False.
	AdjacencyListOfVertices* next;
	//graph* adr_graph;
} AdjList;

typedef struct {
	int number;
	AdjList* ListOfVertices;
} graph;

graph** firstvertex;


int CreateGraph(); // 
void PrintGraph(int);
int* PathForAllVertex() {

}


int main() {

	system("chcp 1251");

	int Graphnum = CreateGraph();
	PrintGraph(Graphnum);

	// V2 Алгоритм Літтла(Алгоритм Дейкстри для кожної вершини):
	AdjList* pList; // 

	int* Arrres = (int*)malloc(WEIGHT_INT * Graphnum);
	int** dArr = (int**)malloc(sizeof(int*) * Graphnum);
	for (int i = 0; i < Graphnum; i++) // <= може видати помилку.
		dArr[i] = (int*)malloc(WEIGHT_INT * Graphnum);

	for (int i = 0; i < Graphnum; i++) {
		pList = firstvertex[i]->ListOfVertices;
		for (int j = 0; j < Graphnum; j++) {
			dArr[i][j] = 0;
		}
		while (pList != NULL) {
			dArr[i][pList->vertex] = pList->weight;
			pList = pList->next;
		}
	}

	for (int indGr = 0; indGr < Graphnum; indGr++) {
		pList = firstvertex[indGr]->ListOfVertices;

		for (int i = 0; i < Graphnum; i++)
			Arrres[i] = INT_MAX;
		while (pList != NULL) {
			Arrres[pList->vertex] = pList->weight;
			pList = pList->next;
		}

		for (int fromv = 1 + indGr; fromv != indGr; fromv++) {
			if (fromv == Graphnum) {
				fromv = -1;
				continue;
			}
			for (int tov = 0; tov < Graphnum; tov++) {
				if (tov == indGr) // 
					continue;

				if (dArr[fromv][tov] != 0 && (long long int)dArr[fromv][tov] + (long long int)Arrres[fromv] < (long long int)Arrres[tov])
					Arrres[tov] = dArr[fromv][tov] + Arrres[fromv];
			}
		}
		for (int i = 0; i < Graphnum; i++)
			dArr[indGr][i] = Arrres[i];
	}


	// !!!!!!!!!!!!!!!!!!!!!--------------------------!!!!!!!!!!!!!!!!!!!!!
	int minel = INT_MAX;

	for (int i = 0; i < Graphnum; i++) {
		for (int j = 0; j < Graphnum; j++) {
			if (dArr[i][j] < minel)
				minel = dArr[i][j];
		}
		for (int j = 0; j < Graphnum; j++) { // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if (dArr[i][j] != INT_MAX) // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				dArr[i][j] -= minel; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}
		minel = INT_MAX;
	}

	for (int i = 0; i < Graphnum; i++) { // 
		for (int j = 0; j < Graphnum && i < Graphnum; j++) {
			if (dArr[j][i] == 0) {
				i++; j = -1;
				minel = INT_MAX;
				continue;
			}
			if (dArr[j][i] < minel)
				minel = dArr[j][i];
		}
		for (int j = 0; j < Graphnum && minel != INT_MAX; j++) {
			if (dArr[j][i] != INT_MAX) // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				dArr[j][i] -= minel; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}
		minel = INT_MAX;
	} // 



	// !!!!!!!!!!!!!!!!!!!!!--------------------------!!!!!!!!!!!!!!!!!!!!!
	int minel_i = INT_MAX, minel_j = INT_MAX;
	int ind_i, ind_j;
	int max_of_sum = 0;

	// !!!!!!!!!!!!!!!!!!!!!--------------------------!!!!!!!!!!!!!!!!!!!!!
	int* path = (int*)malloc(WEIGHT_INT), * path_copy;

	for (int ind_of_path = 0; ind_of_path < Graphnum - 2; ind_of_path++) { //

		for (int i = 0; i < Graphnum; i++) {
			for (int j = 0; j < Graphnum; j++) {
				if (dArr[i][j] == -1)
					continue;
				if (dArr[i][j] == 0) {
					for (int k = 0; k < Graphnum; k++) {
						if (dArr[i][k] < minel_i && k != j && dArr[i][k] != -1) //
							minel_i = dArr[i][k];
					}
					for (int g = 0; g < Graphnum; g++) {
						if (dArr[g][j] < minel_j && g != i && dArr[g][j] != -1) //
							minel_j = dArr[g][j];
					}
					if (minel_i + minel_j > max_of_sum) {
						max_of_sum = minel_i + minel_j;
						ind_i = i; ind_j = j;
					}
				}
				minel_i = INT_MAX; minel_j = INT_MAX;
			}
		}
		max_of_sum = 0;

		path_copy = (int*)malloc(WEIGHT_INT * 2 * (ind_of_path + 1));
		for (int i = 0; i < 2 * ind_of_path; i++)
			path_copy[i] = path[i];
		path_copy[2 * ind_of_path] = ind_i;
		path_copy[2 * ind_of_path + 1] = ind_j;
		free(path);
		path = path_copy;


		for (int j = 0; j < Graphnum; j++)
			dArr[ind_i][j] = -1;
		for (int i = 0; i < Graphnum; i++)
			dArr[i][ind_j] = -1;

		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		int k, j, i;
		for (int i = 0; i < Graphnum; i++) {
			for (k = 0; k < Graphnum; k++) {
				if (dArr[i][k] == -1)
					continue;
				k = 0;
				break;
			}
			if (k != 0)
				continue;
			for (j = 0; j < Graphnum; j++) {
				if (dArr[i][j] == INT_MAX) {
					j = -1;
					break;
				}
			}
			if (j != -1) {
				ind_i = i;
				break;
			}
		}
		for (int j = 0; j < Graphnum; j++) {
			for (k = 0; k < Graphnum; k++) {
				if (dArr[k][j] == -1)
					continue;
				k = 0;
				break;
			}
			if (k != 0)
				continue;
			for (i = 0; i < Graphnum; i++) {
				if (dArr[i][j] == INT_MAX) {
					i = -1;
					break;
				}
			}
			if (i != -1) {
				ind_j = j;
				break;
			}
		}
		dArr[ind_i][ind_j] = INT_MAX;
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	for (int i = 0; i < Graphnum; i++) {
		for (int j = 0; j < Graphnum; j++) {
			if (dArr[i][j] == -1 || dArr[i][j] == INT_MAX)
				continue;
			ind_i = i;
			ind_j = j;
			break;
		}
	}
	dArr[ind_i][ind_j] = -1;
	path_copy = (int*)malloc(WEIGHT_INT * 2 * (Graphnum));
	for (int i = 0; i < 2 * Graphnum; i++)
		path_copy[i] = path[i];
	path_copy[2 * Graphnum - 4] = ind_i;
	path_copy[2 * Graphnum - 3] = ind_j;
	free(path);
	path = path_copy;
	for (int i = 0; i < Graphnum; i++) {
		for (int j = 0; j < Graphnum; j++) {
			if (dArr[i][j] == -1 || dArr[i][j] == INT_MAX)
				continue;
			ind_i = i;
			ind_j = j;
			break;
		}
	}
	path[2 * Graphnum - 2] = ind_i;
	path[2 * Graphnum - 1] = ind_j;



	
	//
	puts("\n");
	for (int i = 0; i < 2 * (Graphnum);) {
		printf(" %d - %d \n", path[i], path[i + 1]);
		i += 2;
	}
	//
}




int CreateGraph() {
	int Graphnum;
	AdjList* last_el, * pList; //
	graph** pVertex = firstvertex; //
	int numAdjGraph, weightGraph;

	firstvertex = (graph**)malloc(sizeof(graph**)); //
	if (firstvertex == NULL) {
		printf("Недостатньо вільної пам'яті!\n");
		return 0;
	}
	*firstvertex = NULL;

	for (Graphnum = 0; ; Graphnum++) {
		if (*firstvertex != NULL) {
			firstvertex = (graph**)malloc(sizeof(graph**) * (Graphnum + 1));  //
			if (firstvertex == NULL) {
				printf("Недостатньо вільної пам'яті!\n");
				return 0;
			}
			for (int i = 0; i < Graphnum; i++)
				firstvertex[i] = pVertex[i];
			free(pVertex);
		}
		pVertex = firstvertex;

		pVertex[Graphnum] = (graph*)malloc(sizeof(graph));
		if (pVertex[Graphnum] == NULL) {
			printf("Недостатньо вільної пам'яті!\n");
			return 0;
		}
		pVertex[Graphnum]->number = Graphnum;

		printf("Введіть номери вершин, до яких ідуть ребра з вершини #%d: \n\t(-1 - завершення введення даних про вершину, якщо вершина пуста, то завершується введення графа) \n", Graphnum);
		pList = (AdjList*)malloc(sizeof(AdjList));

		printf(" Номер: "); // *
		scanf_s("%d", &numAdjGraph);
		if (numAdjGraph == -1) {
			free(pList);
			free(pVertex[Graphnum]);
			pVertex[Graphnum] = NULL; //
			break;
		}
		pList->vertex = numAdjGraph;

		while (true) {
			printf(" Вага ребра між вершинами %d та %d: ", Graphnum, numAdjGraph);
			scanf_s("%d", &weightGraph);
			if (weightGraph < 1) {
				printf("Вага графа не може бути меншою ідиниці!\n");
				continue;
			}
			break;
		}
		pList->weight = weightGraph;

		last_el = pList; // *
		while (true) {
			printf(" Номер: ");
			scanf_s("%d", &numAdjGraph);
			if (numAdjGraph == -1) {
				last_el->next = NULL;
				break;
			}
			last_el->next = (AdjList*)malloc(sizeof(AdjList));
			last_el = last_el->next;
			last_el->vertex = numAdjGraph;
			while (true) {
				printf(" Вага ребра між вершинами %d та %d: ", Graphnum, numAdjGraph);
				scanf_s("%d", &numAdjGraph);
				if (numAdjGraph < 1) {
					printf("Вага графа не може бути меншою ідиниці!\n");
					continue;
				}
				break;
			}
			last_el->weight = numAdjGraph;
		}
		pVertex[Graphnum]->ListOfVertices = pList;
	}

	return Graphnum;
}
void PrintGraph(int Graphnum) {
	AdjList* pList;

	puts("");
	for (int i = 0; i < Graphnum; i++) {
		pList = firstvertex[i]->ListOfVertices;
		printf(" Вершина - #%d: \n", firstvertex[i]->number);
		while (pList != NULL) {
			printf("\t Суміжна вершина - %d \n\t Вага ребра, яке йде до цієї вершини - %d\n", pList->vertex, pList->weight);
			pList = pList->next;
		}
	}
}

