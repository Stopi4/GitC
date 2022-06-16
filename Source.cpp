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


int CreateGraph();
void PrintGraph(int);


int main() {

		system("chcp 1251");

	int Graphnum = CreateGraph();
	PrintGraph(Graphnum);








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













	//
	puts("\n");
	for (int i = 0; i < Graphnum; i++) {
		for (int j = 0; j < Graphnum; j++)
			printf("%d  ", dArr[i][j]);
		puts("\n");
	}
	//








	// !!!!!!!!!!!!!!!!!!!!!--------------------------!!!!!!!!!!!!!!!!!!!!!
	int minel = INT_MAX;

	for (int i = 0; i < Graphnum; i++) {
		for (int j = 0; j < Graphnum; j++) {
			if (dArr[i][j] < minel)
				minel = dArr[i][j];
		}
		for (int j = 0; j < Graphnum; j++) 
			dArr[i][j] -= minel;
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
		for (int j = 0; j < Graphnum && minel != INT_MAX; j++)
			dArr[j][i] -= minel;
		minel = INT_MAX;
	} // 


	
	// !!!!!!!!!!!!!!!!!!!!!--------------------------!!!!!!!!!!!!!!!!!!!!!
	int minel_i = INT_MAX, minel_j = INT_MAX;
	int ind_i, ind_j;
	int max_of_sum = 0;
	//int **dArr_copy;
	
	//
	puts("\n");
	for (int i = 0; i < Graphnum; i++) {
		for (int j = 0; j < Graphnum; j++)
			printf("%d  ", dArr[i][j]);
		puts("\n");
	}
	//





	// !!!!!!!!!!!!!!!!!!!!!--------------------------!!!!!!!!!!!!!!!!!!!!!
	//int** pArr = dArr, *ppArr;
	//int Graphnum_copy = Graphnum;
	int* path = (int*)malloc(WEIGHT_INT), * path_copy;

	int last_el_i, last_el_j;
	int prelast_el_i, prelast_el_j;

	for (int ind_of_path = 0; ind_of_path < Graphnum - 1; ind_of_path++) { //

		for (int i = 0; i < Graphnum; i++) {
			//if (*dArr[i] == -1)
				//continue;
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
			}
			minel_i = INT_MAX; minel_j = INT_MAX;
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








		//dArr_copy = (int**)malloc(WEIGHT_INT * --Graphnum_copy); // 
		//for (int i = 0; i <= Graphnum_copy; i++)
		//	dArr_copy[i] = (int*)malloc(WEIGHT_INT * Graphnum_copy);


		//pArr = dArr;
		//for (int i = 0; i < Graphnum_copy; i++, pArr++) { // 
		//	if (i == ind_i)
		//		pArr++;
		//	ppArr = *pArr;
		//	for (int j = 0; j < Graphnum_copy; j++, ppArr++) { //
		//		if (j == ind_j)
		//			ppArr++;
		//		dArr_copy[i][j] = *ppArr;
		//	}
		//}
		//for (int i = 0; i < Graphnum_copy + 1; i++) {
		//	free(dArr[i]);
		//}
		//free(dArr);
		//dArr = dArr_copy;




		//
		puts("\n");
		for (int i = 0; i < Graphnum; i++) {
			for (int j = 0; j < Graphnum; j++)
				printf("%d  ", dArr[i][j]);
			puts("\n");
		}
		//
		//
		puts("\n");
		for (int i = 0; i < 2*(ind_of_path + 1);) {
			printf(" %d - %d \n", path[i], path[i + 1]);
			i += 2;
		}
		//






		// !!!!
		/*
		last_el_i = last_el_j = prelast_el_i = prelast_el_j = INT_MAX;
		for (int i = 0; i < Graphnum; i++) { // !!!!

			for (int j = 0; j < Graphnum; j++) { // !!!!
				if (dArr[i][j] == -1)
					continue;
				if (last_el_i == INT_MAX) {
					if (prelast_el_i == INT_MAX) {
						prelast_el_i = i;
						prelast_el_j = j;
					}
					else {
						last_el_i = i;
						last_el_j = j;
					}
				}
				else {
					last_el_i = last_el_j = prelast_el_i = prelast_el_j = INT_MAX;
					i = Graphnum;
					break;
				}
			}
		}
		if (last_el_i != INT_MAX)
			break;
		*/
		// !!!!
	}
	for (int i = 0; i < Graphnum; i++) {
		for (int j = 0; j < Graphnum; j++) {
			if (dArr[i][j] == -1)
				continue;
			ind_i = i;
			ind_j = j;
		}
	}
	path_copy = (int*)malloc(WEIGHT_INT * 2 * (Graphnum));
	for (int i = 0; i < 2 * Graphnum; i++)
		path_copy[i] = path[i];
	path_copy[2 * Graphnum - 2] = ind_i;
	path_copy[2 * Graphnum - 1] = ind_j;
	free(path);
	path = path_copy;




	//
	puts("\n");
	for (int i = 0; i < Graphnum; i++) {
		for (int j = 0; j < Graphnum; j++)
			printf("%d  ", dArr[i][j]);
		puts("\n");
	}
	//
	//
	puts("\n");
	for (int i = 0; i < 2 * (Graphnum);) {
		printf(" %d - %d \n", path[i], path[i + 1]);
		i += 2;
	}
	//
}





/*
// !!!!!!!!!!!!!!!!!!!!!--------------------------!!!!!!!!!!!!!!!!!!!!!
int minel_i = INT_MAX, minel_j = INT_MAX;
int ind_i, ind_j;
int max_of_sum = 0;
int** dArr_copy;

//
puts("\n");
for (int i = 0; i < Graphnum; i++) {
	for (int j = 0; j < Graphnum; j++)
		printf("%d  ", dArr[i][j]);
	puts("\n");
}
//





// !!!!!!!!!!!!!!!!!!!!!--------------------------!!!!!!!!!!!!!!!!!!!!!
int** pArr = dArr, * ppArr;
int Graphnum_copy = Graphnum;
int* path = (int*)malloc(WEIGHT_INT), * path_copy;

for (int ind_of_path = 0; ind_of_path < Graphnum; ind_of_path++) { //

	for (int i = 0; i < Graphnum_copy; i++) {
		for (int j = 0; j < Graphnum_copy; j++) {
			if (dArr[i][j] == 0) {
				for (int k = 0; k < Graphnum_copy; k++) {
					if (dArr[i][k] < minel_i && k != j)
						minel_i = dArr[i][k];
				}
				for (int g = 0; g < Graphnum_copy; g++) {
					if (dArr[g][j] < minel_j && g != i)
						minel_j = dArr[g][j];
				}
				if (minel_i + minel_j > max_of_sum) {
					max_of_sum = minel_i + minel_j;
					ind_i = i; ind_j = j;
				}
			}
		}
		minel_i = INT_MAX; minel_j = INT_MAX;
	}



	path_copy = (int*)malloc(WEIGHT_INT * 2 * (ind_of_path + 1));
	for (int i = 0; i < 2 * ind_of_path; i++)
		path_copy[i] = path[i];
	path_copy[2 * ind_of_path] = ind_i;
	path_copy[2 * ind_of_path + 1] = ind_j;
	free(path);
	path = path_copy;


	dArr_copy = (int**)malloc(WEIGHT_INT * --Graphnum_copy); // 
	for (int i = 0; i <= Graphnum_copy; i++)
		dArr_copy[i] = (int*)malloc(WEIGHT_INT * Graphnum_copy);


	pArr = dArr;
	for (int i = 0; i < Graphnum_copy; i++, pArr++) { // 
		if (i == ind_i)
			pArr++;
		ppArr = *pArr;
		for (int j = 0; j < Graphnum_copy; j++, ppArr++) { //
			if (j == ind_j)
				ppArr++;
			dArr_copy[i][j] = *ppArr;
		}
	}
	for (int i = 0; i < Graphnum_copy + 1; i++) {
		free(dArr[i]);
	}
	free(dArr);
	dArr = dArr_copy;




	//
	puts("\n");
	for (int i = 0; i < Graphnum_copy; i++) {
		for (int j = 0; j < Graphnum_copy; j++)
			printf("%d  ", dArr[i][j]);
		puts("\n");
	}
	//
}
*/


int CreateGraph() {
	//int Graphnum, NUMADJ_ind = 1;
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
/*
int CreateGraph() {
	//int Graphnum, NUMADJ_ind = 1;
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
		last_el = pList; // *
		while (true) {
			printf(" Номер: ");
			scanf_s("%d", &numAdjGraph);
			if (numAdjGraph == -1) {

				break;
			}

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
			last_el->next = (AdjList*)malloc(sizeof(AdjList));
			last_el = last_el->next;
		}
		if (last_el == pList) {
			free(pList);
			free(pVertex[Graphnum]);
			pVertex[Graphnum] = NULL; //
			return Graphnum;
		}
		//free(last_el);
		last_el = NULL;
		pVertex[Graphnum]->ListOfVertices = pList;
	}

	//return Graphnum;
}
*/
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


