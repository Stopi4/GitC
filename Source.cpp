// http://ekmair.ukma.edu.ua/bitstream/handle/123456789/18324/Haldetskyi_Zadacha_komivoiazhera_yak_zadacha_binarnoho_LP.pdf?sequence=1&isAllowed=y
// https://www.mathros.net.ua/znahodzhennja-rozvjazku-zadachi-komivojazhera-metodom-oserednenyh-koeficijentiv.html
// https://www.programiz.com/dsa/graph-adjacency-list
// 
// !!
// https://uchimatchast.ru/teoriya/algoritm-littla-primer-1/
// !! алгоритм Літтла

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

int main() {
	system("chcp 1251");

	// CreateGraph();
	int Graphnum, NUMADJ_ind = 1;
	AdjList* last_el, * pList; //
	graph** pVertex = firstvertex; //
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
		//else
		//	firstvertex = (graph**)malloc(sizeof(graph**)*(Graphnum + 1)); //
		pVertex = firstvertex;



		pVertex[Graphnum] = (graph*)malloc(sizeof(graph));
		if (pVertex[Graphnum] == NULL) {
			printf("Недостатньо вільної пам'яті!\n");
			return 0;
		}
		pVertex[Graphnum]->number = Graphnum;

		printf("Введіть номери вершин, до яких ідуть ребра з вершини #%d: \n\t(-1 - завершення введення даних про вершину, якщо вершина пуста, то завершується введення графа) \n", Graphnum);
		pList = (AdjList*)malloc(sizeof(AdjList));

		int numAdjGraph, weightGraph;
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

	// PrintGraph();
	puts("");
	for (int i = 0; i < Graphnum; i++) {
		pList = firstvertex[i]->ListOfVertices;
		printf(" Вершина - #%d: \n", firstvertex[i]->number);
		while (pList != NULL) {
			printf("\t Суміжна вершина - %d \n\t Вага ребра, яке йде до цієї вершини - %d\n", pList->vertex, pList->weight);
			pList = pList->next;
		}
	}


	printf("%d\t%d\t%d\n", sizeof(long int), sizeof(int), sizeof(long long int));
	// Задача комівояжера:

	/*
	int key; // Костиль.

	int MinWeight, res = 0, mres = INT_MAX;
	int* dArr = (int*)malloc(WEIGHT_INT * Graphnum);
	AdjList* pListMin;
	pList = firstvertex[0]->ListOfVertices;
	for (int i = 0; i < Graphnum; i++)
		dArr[i] = 0;
	(*dArr)++;
	while (true) {
		while (true) {
			//MinWeight = pList->weight;
			pListMin = pList;
			pList = pList->next;
			while (pList != NULL) {
				if (dArr[pListMin->vertex] > dArr[pList->vertex]) {
					pListMin = pList;
				}
				else if (pListMin->weight > pList->weight && dArr[pListMin->vertex] == dArr[pList->vertex]) {
					pListMin = pList;
					//MinWeight = pList->weight;
				}
				pList = pList->next;
			}
			res += pListMin->weight;
			pList = firstvertex[pListMin->vertex]->ListOfVertices;
			dArr[pListMin->vertex]++;





			if (pListMin->vertex == 0) {
				key = 1;
				for (int i = 0; i < Graphnum; i++) {
					if (dArr[i] == 0)
						key = 0;
				}
				if (key == 1)
					break;
			}
		}
		if (mres > res)
			mres = res;
		res = 0;
	}
	*/

	// V2 Алгоритм Літтла(Алгоритм Дейкстри для кожної вершини):

	// firstvertex, Graphnum, pVertex, pList.

	int* Arrres = (int*)malloc(WEIGHT_INT * Graphnum);
	int** dArr = (int**)malloc(WEIGHT_INT * Graphnum);
	for (int i = 0; i <= Graphnum; i++)
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

		// *
		for (int i = 0; i < Graphnum; i++) {
			
				for (int j = 0; j < Graphnum; j++)
					printf("%d  ", dArr[i][j]);
			puts("\n");
		}
		// *

		for (int fromv = 1; fromv < Graphnum + 1; fromv++) { // !!!
			// *
			for (int j = 0; j < Graphnum; j++)
				printf("%d  ", Arrres[j]);
			puts("\n");
			// *

			if (fromv - 1 == indGr)
				continue;
			for (int tov = 1; tov < Graphnum + 1; tov++) {
				if (tov - 1 == indGr)
					continue;
				if (dArr[fromv - 1][tov - 1] != 0 && (long long int)dArr[fromv - 1][tov - 1] + (long long int)Arrres[fromv - 1] < (long long int)Arrres[tov - 1])
					Arrres[tov - 1] = dArr[fromv - 1][tov - 1] + Arrres[fromv - 1];
			}
		}



		// *]
		/*
		for (int i = 0; i < Graphnum; i++){
			if (Arrres[i] == INT_MAX)
				Arrres[i] = 0;
		}
		*/
		// *
		for (int i = 0; i < Graphnum; i++) // ! 
			dArr[indGr][i] = Arrres[i];
	}

	for (int i = 0; i < Graphnum; i++) {
		for (int j = 0; j < Graphnum; j++)
			printf("%d  ", dArr[i][j]);
		puts("\n");
	}



	/*pList = (*firstvertex)->ListOfVertices;
	for (int i = 2; i < Graphnum; i++) {
		while (pList->vertex < Graphnum) {
			pList = firstvertex[pList->vertex]->ListOfVertices;
			if (pList->weight + Arrres[pList->vertex] <
		}
	}*/



}