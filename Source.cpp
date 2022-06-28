// http://ekmair.ukma.edu.ua/bitstream/handle/123456789/18324/Haldetskyi_Zadacha_komivoiazhera_yak_zadacha_binarnoho_LP.pdf?sequence=1&isAllowed=y
// https://www.mathros.net.ua/znahodzhennja-rozvjazku-zadachi-komivojazhera-metodom-oserednenyh-koeficijentiv.html
// https://www.programiz.com/dsa/graph-adjacency-list
// 
// !!
// https://uchimatchast.ru/teoriya/algoritm-littla-primer-1/
// !! �������� ˳����


// ������� ��� ����� ���� �� double (�� ����'������).
// �������� ���� ����:
// 1) ����� �� ����������� ���������.
// 2) ����� ��������� �������.
// 3) ������ ��������� ������� ������� �����.
// 


// ���������:
// �������� �������� ����������� �������� �����.
//
// ���������� ������� �� ������. ������� �������� � �������.


// �������:
// ������ ������������ ������ �� �������(�������� � Java).
// �� ������������ �����:
// FullPath �� DetailPath. FullPathBetweenTwoVertex �� DetailPathForVertex. TravellingSalesmanProblem �� FullPathForGraph.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <limits.h>
#include <math.h>
//#define NUMADJ 5
#define WEIGHT_INT sizeof(int)
#define NUM_CHAR_INT 10
#define SIZE 200

typedef struct AdjacencyListOfVertices {
	int vertex; // �������.
	int weight; // ���� �� ���� �������.
	AdjacencyListOfVertices* next;
} AdjList;

typedef struct {
	int number;
	AdjList* ListOfVertices;
} graph;

graph** firstvertex;
int Graphnum;



FILE* OpenFile(char* fname);
AdjList* FillVertexFromConsole();
AdjList* FillVertexFromFile(FILE* fp);
int CreateGraph();
void PrintGraph();
void PrintGraphMatr();

int** DijkstrasAlgorithmForAllVertex(); // �������� ��������.
int* LittlesAlgorithm(int** dArr); // �������� ˳����.
int* SortPathOfLittlesAlgorithm(int*);

int* FullPathBetweenTwoVertex(int, int**);
int* SortFullPathBetweenTwoVertex(int, int, int*);
int AddFullPath(int*&, int*, int);

int TravellingSalesmanProblem(int*&);
void PrintPath(int*, int);

void DeleteList(AdjList*);
void DeleteGraph();

















// V2
/*
int CreateGraph() { // FillGraph
	AdjList* first_el, *last_el, * pList; //
	graph** pVertex = NULL; //
	int numAdjGraph, weightGraph;


	for (Graphnum = 0; ; Graphnum++) {

		firstvertex = (graph**)malloc(sizeof(graph**) * (Graphnum + 1));  //
		if (firstvertex == NULL) {
			printf("����������� ����� ���'��!\n");
			return 0;
		}
		if (pVertex != NULL) {
			for (int i = 0; i < Graphnum; i++)
				firstvertex[i] = pVertex[i];
			free(pVertex);
		}

		pVertex = firstvertex;

		pVertex[Graphnum] = (graph*)malloc(sizeof(graph));
		if (pVertex[Graphnum] == NULL) {
			printf("����������� ����� ���'��!\n");
			return 0;
		}
		pVertex[Graphnum]->number = Graphnum;


		printf("������ ������ ������, �� ���� ����� ����� � ������� #%d: \n\t(-1 - ���������� �������� ����� ��� �������, ���� ������� �����, �� ����������� �������� �����) \n", Graphnum);
		first_el = (AdjList*)malloc(sizeof(AdjList));


		pList = first_el;
		last_el = first_el; // *

		while (true) {
			printf(" �����: ");
			scanf_s("%d", &numAdjGraph);
			if (numAdjGraph == -1) {
				if (last_el == first_el) {
					free(first_el);
					free(pVertex[Graphnum]);
					pVertex[Graphnum] = NULL; //
					return Graphnum;
				}
				free(last_el);
				pList->next = NULL;
				break;
			}
			last_el->vertex = numAdjGraph;


			while (true) {
				printf(" ���� ����� �� ��������� %d �� %d: ", Graphnum, numAdjGraph);
				scanf_s("%d", &numAdjGraph);
				if (numAdjGraph < 1) {
					printf("���� ����� �� ���� ���� ������ �������!\n");
					continue;
				}
				break;
			}
			last_el->weight = numAdjGraph;
			pList = last_el;
			last_el->next = (AdjList*)malloc(sizeof(AdjList));
			last_el = last_el->next;
		}
		pVertex[Graphnum]->ListOfVertices = first_el;
	}

	return Graphnum;
}
*/






/*

int CheckTheGraph() {
	graph** pVertex = firstvertex;
	AdjList* pList;
	//int* noFromVarr = (int*)malloc(WEIGHT_INT * Graphnum);
	int* noToVarr = (int*)malloc(WEIGHT_INT * Graphnum);
	for (int i = 0; i < Graphnum; i++){
		//noFromVarr[i] = -1;
		noToVarr[i] = -1;
	}

	while (*pVertex != NULL) {
		pList = (*pVertex)->ListOfVertices;

		while (pList != NULL) {
			if (pList->vertex > Graphnum) {
				printf(" ����������� ���������� ����! ����� ���� �� �������� �������! \n");
				return -1;
			}
			if (pList->vertex == (*pVertex)->number) {
				printf(" ������� �� ���� ���� ����� ���� � �����!");
				return -1;
			}
			//noToVarr[(*pVertex)->number] = 1;
			noToVarr[pList->vertex] = 1;
		}
	}
}

*/













int main() {
	system("chcp 1251");

	if (CreateGraph() == 0)
		return 0;
	PrintGraph();
	PrintGraphMatr();
	int** matrshrtw = DijkstrasAlgorithmForAllVertex(); // MatrixWeightOfShortestPaths. ��������� ��� ����������� ������ �� ���� ���������.
	int* path = LittlesAlgorithm(matrshrtw); // ��������� ������, ���� ������ ����������� ����, �� ��������� ����� �� �������, �� ����������� � ���������. 
	// ��������� ��� ���� ������ ������� ����������� �����, � ���� ����������� Graphnum �����, �� ����� ������ ���� �� �������. ����� ������� ����� ������ ���� �� �������.

	int Weight_Of_The_Path = 0;
	for (int i = 0; i < 2 * Graphnum; ) {
		Weight_Of_The_Path += matrshrtw[path[i]][path[i + 1]];
		i += 2;
	}
	printf("\n Path = %d \n", Weight_Of_The_Path);

	path = SortPathOfLittlesAlgorithm(path);
	int size_of_path = TravellingSalesmanProblem(path);

	PrintPath(path, size_of_path);

	DeleteGraph();
	for (int i = 0; i < Graphnum; i++)
		free(matrshrtw[i]);
	free(path);

	return 0;
}
















FILE* OpenFile(char* fname) {
	FILE* fp;
	const char* fnameBasic = "C:\\Stopa. ���������\\�����������\\(1)������ ����\\(2)������ �������\\������������� �� �������������\\����� ��������� ��������.txt";

	if ((fp = fopen(fname, "rt")) == NULL) {
		printf(" ���� %s �� ��������!\n ³�������� ���� �� �������������!\n", fname);
		if ((fp = fopen(fnameBasic, "rt")) == NULL) {
			printf(" ����� ��\'� ����� - %s \n", fnameBasic); // ��������� ����  ��� �������, ���'������ � ������ �� ������� fname_r.
			return NULL;
		}
	}

	return fp;
}
AdjList* FillVertexFromConsole() {
	int weightAdjVertex, numAdjVertex;
	printf("������ ������ ������, �� ���� ����� ����� � ������� #%d: \n\t(-1 - ���������� �������� ����� ��� �������, ���� ������� �����, �� ����������� �������� �����) \n", Graphnum);
	while (true) {
		printf(" �����: ");
		scanf_s("%d", &numAdjVertex);
		if (numAdjVertex >= 0 || numAdjVertex == -1)
			break;
		printf(" ����� ������� �� ���� ���� ��'�����, ���� '-1' - ���������� ��������.\n �������� ������: ");
	}
	if (numAdjVertex == -1)
		return NULL;
	AdjList* pList = (AdjList*)malloc(sizeof(AdjList));
	AdjList* last_el = pList;
	pList->vertex = numAdjVertex;

	while (true) {
		while (true) {
			printf(" ���� ����� �� ��������� %d �� %d: ", Graphnum, numAdjVertex);
			scanf_s("%d", &weightAdjVertex);
			if (weightAdjVertex < 1) {
				printf(" ���� ����� �� ���� ���� ������ �������!\n �������� ������: ");
				continue;
			}
			break;
		}
		last_el->weight = weightAdjVertex;

		while (true) {
			printf(" �����: ");
			scanf_s("%d", &numAdjVertex);
			if (numAdjVertex >= 0 || numAdjVertex == -1)
				break;
			printf(" ����� ������� �� ���� ���� ��'�����, ���� '-1' - ���������� ��������.\n �������� ������: ");
		}
		if (numAdjVertex == -1) {
			last_el->next = NULL;
			break;
		}
		last_el->next = (AdjList*)malloc(sizeof(AdjList));
		last_el = last_el->next;
		last_el->vertex = numAdjVertex;
	}

	return pList;
}
AdjList* FillVertexFromFile(FILE* fp) { //
	int weightAdjVertex, numAdjVertex;
	char* str = (char*)malloc(WEIGHT_INT * (NUM_CHAR_INT + 1));
	char* pn = str;

	if (fgets(str, NUM_CHAR_INT + 1, fp) == NULL)
		return NULL;
	*(strchr(str, '\n')) = 0;
	numAdjVertex = atoi(str); // !!!!!!!
	if (numAdjVertex == -1)
		return NULL;
	if (numAdjVertex == 0) {
		while (*pn == ' ') // ��������, �� ������� ������ �������, �� ������� ������� �� ������� 0.
			pn++;
		if (*pn != '0') {
			printf(" ������������ ������ ������ ���������� �����! \n");
			return NULL;
		}
	}

	AdjList* pList = (AdjList*)malloc(sizeof(AdjList));
	AdjList* last_el = pList;
	pList->vertex = numAdjVertex;
	while (true) {
		if (fgets(str, NUM_CHAR_INT + 1, fp) == NULL)
			break;
		*(strchr(str, '\n')) = 0;
		weightAdjVertex = atoi(str);
		if (weightAdjVertex <= 0)
			break;
		last_el->weight = weightAdjVertex;

		if (fgets(str, NUM_CHAR_INT + 1, fp) == NULL)
			break;
		pn = str;
		*(strchr(str, '\n')) = 0;
		numAdjVertex = atoi(str);
		while (*pn == ' ') // 
			pn++;
		if (numAdjVertex == 0) {
			while (*pn == ' ') // ��������, �� ������� ������ �������, �� ������� ������� �� ������� 0.
				pn++;
			if (*pn != '0') {
				break;
			}
		}
		else if (numAdjVertex == -1) {
			last_el->next = NULL;
			free(str);
			return pList;
		}
		last_el->next = (AdjList*)malloc(sizeof(AdjList));
		last_el = last_el->next;
		last_el->vertex = numAdjVertex;
	}

	printf(" ������������ ������ ������ ���������� �����! \n");
	last_el->next = NULL;
	DeleteList(pList);
	free(str);

	return NULL;
}
int CreateGraph() {
	graph** pVertex = NULL;
	int mode;
	FILE* fp = NULL;

	while (true) {
		printf(" ������� ����� ��������( 1 - � �������, 2 - � ����� ): ");
		scanf("%d", &mode);
		if (mode != 1 && mode != 2)
			puts("���������� �������!...");
		else
			break;
	}

	if (mode == 2) {
		char fname[SIZE];
		gets_s(fname, SIZE);
		if ((fp = OpenFile(fname)) == NULL) //
			return 0;
	}

	for (Graphnum = 0; ; Graphnum++) {
		firstvertex = (graph**)malloc(sizeof(graph**) * (Graphnum + 1));
		if (firstvertex == NULL) {
			printf("����������� ����� ���'��!\n");
			return 0;
		}
		if (pVertex != NULL) {
			for (int i = 0; i < Graphnum; i++)
				firstvertex[i] = pVertex[i];
			free(pVertex);
		}
		pVertex = firstvertex;

		pVertex[Graphnum] = (graph*)malloc(sizeof(graph));
		if (pVertex[Graphnum] == NULL) {
			printf("����������� ����� ���'��!\n");
			return 0;
		}
		pVertex[Graphnum]->number = Graphnum;

		if (mode == 1) {
			if ((pVertex[Graphnum]->ListOfVertices = FillVertexFromConsole()) == NULL) {
				free(pVertex[Graphnum]);
				pVertex[Graphnum] = NULL;
				return Graphnum;
			}
		}
		else {
			if ((pVertex[Graphnum]->ListOfVertices = FillVertexFromFile(fp)) == NULL) {
				fclose(fp);
				free(pVertex[Graphnum]);
				pVertex[Graphnum] = NULL;
				return Graphnum;
			}
		}
	}
}
/*int CreateGraph() {
	AdjList* last_el, * pList; //
	graph** pVertex = firstvertex; //
	int numAdjGraph, weightGraph;

	firstvertex = (graph**)malloc(sizeof(graph**)); //
	if (firstvertex == NULL) {
		printf("����������� ����� ���'��!\n");
		return 0;
	}
	*firstvertex = NULL;

	for (Graphnum = 0; ; Graphnum++) {
		if (*firstvertex != NULL) { // !!!!!!!!!!!!!!!!!!!!!!!!
			firstvertex = (graph**)malloc(sizeof(graph**) * (Graphnum + 1));  //
			if (firstvertex == NULL) {
				printf("����������� ����� ���'��!\n");
				return 0;
			}
			for (int i = 0; i < Graphnum; i++)
				firstvertex[i] = pVertex[i];
			free(pVertex);
		} // !!!!!!!!!!!!!!!!!!!!!!!!!!
		pVertex = firstvertex;

		pVertex[Graphnum] = (graph*)malloc(sizeof(graph));
		if (pVertex[Graphnum] == NULL) {
			printf("����������� ����� ���'��!\n");
			return 0;
		}
		pVertex[Graphnum]->number = Graphnum;

		printf("������ ������ ������, �� ���� ����� ����� � ������� #%d: \n\t(-1 - ���������� �������� ����� ��� �������, ���� ������� �����, �� ����������� �������� �����) \n", Graphnum);
		pList = (AdjList*)malloc(sizeof(AdjList));

		printf(" �����: "); // *
		scanf_s("%d", &numAdjGraph);
		if (numAdjGraph == -1) {
			free(pList);
			free(pVertex[Graphnum]);
			pVertex[Graphnum] = NULL; //
			break;
		}
		pList->vertex = numAdjGraph;

		while (true) {
			printf(" ���� ����� �� ��������� %d �� %d: ", Graphnum, numAdjGraph);
			scanf_s("%d", &weightGraph);
			if (weightGraph < 1) {
				printf("���� ����� �� ���� ���� ������ �������!\n");
				continue;
			}
			break;
		}
		pList->weight = weightGraph;

		last_el = pList; // *
		while (true) {
			printf(" �����: ");
			scanf_s("%d", &numAdjGraph);
			if (numAdjGraph == -1) {
				last_el->next = NULL;
				break;
			}
			last_el->next = (AdjList*)malloc(sizeof(AdjList));
			last_el = last_el->next;
			last_el->vertex = numAdjGraph;
			while (true) {
				printf(" ���� ����� �� ��������� %d �� %d: ", Graphnum, numAdjGraph);
				scanf_s("%d", &numAdjGraph);
				if (numAdjGraph < 1) {
					printf("���� ����� �� ���� ���� ������ �������!\n");
					continue;
				}
				break;
			}
			last_el->weight = numAdjGraph;
		}
		pVertex[Graphnum]->ListOfVertices = pList;
	}

	return Graphnum;
}*/
void PrintGraph() {
	AdjList* pList;

	puts("");
	for (int i = 0; i < Graphnum; i++) {
		pList = firstvertex[i]->ListOfVertices;
		printf(" ������� - #%d: \n", firstvertex[i]->number);
		while (pList != NULL) {
			printf("\t ������ ������� - %d \n\t ���� �����, ��� ��� �� ���� ������� - %d\n", pList->vertex, pList->weight);
			pList = pList->next;
		}
	}
}
void PrintGraphMatr() {
	AdjList* pList;
	int** matrshrtw = (int**)malloc(sizeof(int*) * Graphnum);
	for (int i = 0; i < Graphnum; i++)
		matrshrtw[i] = (int*)malloc(WEIGHT_INT * Graphnum);

	puts("");
	for (int i = 0; i < Graphnum; i++) {
		pList = firstvertex[i]->ListOfVertices;
		for (int j = 0; j < Graphnum; j++)
			matrshrtw[i][j] = 0;
		while (pList != NULL) {
			matrshrtw[i][pList->vertex] = pList->weight;
			pList = pList->next;
		}
		for (int j = 0; j < Graphnum; j++)
			printf(" %5d", matrshrtw[i][j]);
		puts("\n");
	}
	puts("");
}

int** DijkstrasAlgorithmForAllVertex() {
	AdjList* pList; // 

	int* weightOfPath = (int*)malloc(WEIGHT_INT * Graphnum);
	int** matrshrtw = (int**)malloc(sizeof(int*) * Graphnum);
	for (int i = 0; i < Graphnum; i++)
		matrshrtw[i] = (int*)malloc(WEIGHT_INT * Graphnum);

	for (int i = 0; i < Graphnum; i++) {
		pList = firstvertex[i]->ListOfVertices;
		for (int j = 0; j < Graphnum; j++)
			matrshrtw[i][j] = 0;
		while (pList != NULL) {
			matrshrtw[i][pList->vertex] = pList->weight;
			pList = pList->next;
		}
	}


	for (int i = 0; i < sqrt(Graphnum) - 1; i++) { // ���� �������� ��� ����������, �� ����� ����������� ������ ����������� �� ����.
		for (int indGr = 0; indGr < Graphnum; indGr++) {
			pList = firstvertex[indGr]->ListOfVertices;

			for (int i = 0; i < Graphnum; i++)
				weightOfPath[i] = INT_MAX;
			while (pList != NULL) {
				weightOfPath[pList->vertex] = pList->weight;
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

					if (matrshrtw[fromv][tov] != 0 && (long long int)matrshrtw[fromv][tov] + (long long int)weightOfPath[fromv] < (long long int)weightOfPath[tov])
						weightOfPath[tov] = matrshrtw[fromv][tov] + weightOfPath[fromv];
				}
			}
			for (int i = 0; i < Graphnum; i++)
				matrshrtw[indGr][i] = weightOfPath[i];
		}
	}
	free(weightOfPath);

	return matrshrtw;
}
int* LittlesAlgorithm(int** matrshrtw) {
	int minel = INT_MAX;
	int** matrshrtw_copy = (int**)malloc(sizeof(int*) * Graphnum); // ������� ���������� �����.
	for (int i = 0; i < Graphnum; i++) {
		matrshrtw_copy[i] = (int*)malloc(WEIGHT_INT * Graphnum);
		for (int j = 0; j < Graphnum; j++)
			matrshrtw_copy[i][j] = matrshrtw[i][j];
	}

	for (int i = 0; i < Graphnum; i++) { // ³������ ��������� ������� ����� �� �������� �����.
		for (int j = 0; j < Graphnum; j++) {
			if (matrshrtw_copy[i][j] < minel)
				minel = matrshrtw_copy[i][j];
		}
		for (int j = 0; j < Graphnum; j++) {
			if (matrshrtw_copy[i][j] != INT_MAX)
				matrshrtw_copy[i][j] -= minel;
		}
		minel = INT_MAX;
	}
	for (int i = 0; i < Graphnum; i++) { // �� ��������� ������� ������� �� �������� �������.
		for (int j = 0; j < Graphnum && i < Graphnum; j++) {
			if (matrshrtw_copy[j][i] == 0) {
				i++; j = -1;
				minel = INT_MAX;
				continue;
			}
			if (matrshrtw_copy[j][i] < minel)
				minel = matrshrtw_copy[j][i];
		}
		for (int j = 0; j < Graphnum && minel != INT_MAX; j++) {
			if (matrshrtw_copy[j][i] != INT_MAX)
				matrshrtw_copy[j][i] -= minel;
		}
		minel = INT_MAX;
	}

	int minel_i = INT_MAX, minel_j = INT_MAX;
	int ind_i, ind_j;
	int max_of_sum = 0;
	int* path = (int*)malloc(WEIGHT_INT * 2 * (Graphnum));
	int k, j, i;

	for (int ind_of_path = 0; ind_of_path < Graphnum - 2; ind_of_path++) {
		for (int i = 0; i < Graphnum; i++) { // ��������� ��������� ������� ����� �� ��������, � ��������� ���� � '0', ��� ����� ����.
			for (int j = 0; j < Graphnum; j++) { // �� �����'������� �������, �� � �������� ���� ��������� ��������.
				if (matrshrtw_copy[i][j] == -1)
					continue;
				if (matrshrtw_copy[i][j] == 0) {
					for (int k = 0; k < Graphnum; k++) {
						if (matrshrtw_copy[i][k] < minel_i && k != j && matrshrtw_copy[i][k] != -1)
							minel_i = matrshrtw_copy[i][k];
					}
					for (int g = 0; g < Graphnum; g++) {
						if (matrshrtw_copy[g][j] < minel_j && g != i && matrshrtw_copy[g][j] != -1)
							minel_j = matrshrtw_copy[g][j];
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

		path[2 * ind_of_path] = ind_i; // ������������ ���� �� ��������� �����
		path[2 * ind_of_path + 1] = ind_j; // �� �������.

		for (int j = 0; j < Graphnum; j++) // "���������" ����� �� �������� �� ���� ���������.
			matrshrtw_copy[ind_i][j] = -1;
		for (int i = 0; i < Graphnum; i++)
			matrshrtw_copy[i][ind_j] = -1;


		for (int i = 0; i < Graphnum; i++) { // ������ � ���� ������ �� �������� ���� ������������.
			for (k = 0; k < Graphnum; k++) { // ������ �� �������, �� �� ����� ���� �������� ������������, ��� INT_MAX.
				if (matrshrtw_copy[i][k] == -1)
					continue;
				k = 0;
				break;
			}
			if (k != 0)
				continue;
			for (j = 0; j < Graphnum; j++) {
				if (matrshrtw_copy[i][j] == INT_MAX) {
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
				if (matrshrtw_copy[k][j] == -1)
					continue;
				k = 0;
				break;
			}
			if (k != 0)
				continue;
			for (i = 0; i < Graphnum; i++) {
				if (matrshrtw_copy[i][j] == INT_MAX) {
					i = -1;
					break;
				}
			}
			if (i != -1) {
				ind_j = j;
				break;
			}
		}
		matrshrtw_copy[ind_i][ind_j] = INT_MAX; // �������� ������������.
	}
	for (int i = 0; i < Graphnum; i++) { // ��������� ���� ��� ���� ��������, �� ����������.
		for (int j = 0; j < Graphnum; j++) {
			if (matrshrtw_copy[i][j] == -1 || matrshrtw_copy[i][j] == INT_MAX)
				continue;
			ind_i = i;
			ind_j = j;
			break;
		}
	}
	matrshrtw_copy[ind_i][ind_j] = -1;
	path[2 * Graphnum - 4] = ind_i;
	path[2 * Graphnum - 3] = ind_j;
	for (int i = 0; i < Graphnum; i++) {
		for (int j = 0; j < Graphnum; j++) {
			if (matrshrtw_copy[i][j] == -1 || matrshrtw_copy[i][j] == INT_MAX)
				continue;
			ind_i = i;
			ind_j = j;
			break;
		}
	}
	path[2 * Graphnum - 2] = ind_i;
	path[2 * Graphnum - 1] = ind_j;
	for (int i = 0; i < Graphnum; i++)
		free(matrshrtw_copy[i]);
	free(matrshrtw_copy);

	return path; // ��������� ����.
}
int* SortPathOfLittlesAlgorithm(int* path) {
	int* sorted_path = (int*)malloc(WEIGHT_INT * Graphnum * 2);
	int* ptrpath = path;
	int initial_vertex;

	while (true) {
		printf(" ������ �������, � ��� ������� ������ ����: ");
		scanf("%d", &initial_vertex);
		if (initial_vertex < Graphnum && initial_vertex >= 0)
			break;
		printf(" ������� ����������� ��������! �������� ������! \n");
	}
	while (*ptrpath != initial_vertex)
		ptrpath += 2;

	int indV = 0;
	sorted_path[indV++] = *ptrpath++; // 
	sorted_path[indV] = *ptrpath;

	for (; indV < Graphnum * 2 - 1; ) { // ������� ������������ ����, ���������� ��������� �������, ��� ����� ����������.
		ptrpath = path;
		while (*ptrpath != sorted_path[indV])
			ptrpath += 2;
		sorted_path[++indV] = *ptrpath++;
		sorted_path[++indV] = *ptrpath;
	}
	free(path);
	path = sorted_path;

	return path;
}



int* FullPathBetweenTwoVertex(int fromGivenV, int** matrw) {
	int* weightOfPath = (int*)malloc(WEIGHT_INT * Graphnum);
	AdjList* pList = firstvertex[fromGivenV]->ListOfVertices;
	int* fullPathFromV = (int*)malloc(WEIGHT_INT * Graphnum);
	int* ptrfullPathFromV;

	for (int i = 0; i < Graphnum; i++)
		weightOfPath[i] = INT_MAX;
	while (pList != NULL) {
		weightOfPath[pList->vertex] = pList->weight;
		pList = pList->next;
	}

	ptrfullPathFromV = fullPathFromV;
	while (ptrfullPathFromV < fullPathFromV + Graphnum)
		*ptrfullPathFromV++ = -1;

	for (int i = 0; i < Graphnum - 1; i++) { // �������� �������� ����������, ��� �������� �� �����.
		for (int fromv = 1 + fromGivenV; fromv != fromGivenV; fromv++) { // ������ ������ ����������� ���� �� ���� ������� �� ���.
			if (fromv == Graphnum) {
				fromv = -1;
				continue;
			}
			for (int tov = 0; tov < Graphnum; tov++) {
				if (tov == fromGivenV)
					continue;
				if (matrw[fromv][tov] != 0 && (long long int)matrw[fromv][tov] + (long long int)weightOfPath[fromv] < (long long int)weightOfPath[tov]) {
					weightOfPath[tov] = matrw[fromv][tov] + weightOfPath[fromv];
					fullPathFromV[fromv] = tov; // �������� ���� �� ������� fromGivenV, �� ����� ������.
				}
			}
		}
		for (int i = 0; i < Graphnum; i++)
			matrw[fromGivenV][i] = weightOfPath[i];

	}
	pList = firstvertex[fromGivenV]->ListOfVertices;
	for (int j = 0; j < Graphnum; j++)
		matrw[fromGivenV][j] = 0;
	while (pList != NULL) {
		matrw[fromGivenV][pList->vertex] = pList->weight;
		pList = pList->next;
	}
	free(weightOfPath);
	return fullPathFromV;
}
int* SortFullPathBetweenTwoVertex(int fromGivenV, int toGivenV, int* fullPathFromV) { // !!!!!!!!!! fullPathtoV
	int* sorted_fullPathFromV = (int*)malloc(WEIGHT_INT * Graphnum);
	AdjList* pList = firstvertex[fromGivenV]->ListOfVertices;
	int* ptrpath;

	while (pList != NULL) { // ������� ��������� ������ ����.
		int i;
		*sorted_fullPathFromV = pList->vertex;
		for (i = 1; i < Graphnum; i++) {
			if (fullPathFromV[sorted_fullPathFromV[i - 1]] == -1) {
				i = Graphnum;
				break;
			}
			sorted_fullPathFromV[i] = fullPathFromV[sorted_fullPathFromV[i - 1]];
			if (sorted_fullPathFromV[i] == toGivenV)
				break;
		}
		if (i != Graphnum) {
			ptrpath = sorted_fullPathFromV + i + 1;
			while (ptrpath < sorted_fullPathFromV + Graphnum)
				*ptrpath++ = -1;
			break;
		}
		pList = pList->next;
	}
	free(fullPathFromV);
	fullPathFromV = sorted_fullPathFromV;

	return fullPathFromV;
}
int AddFullPath(int*& path, int* fullPathFromV, int indGr) {
	static int size_of_path = Graphnum * 2;
	int* ptrfPathFromV = fullPathFromV;
	int size_of_detail_path;
	int* ptrpath = path;

	while (*ptrfPathFromV != -1)
		ptrfPathFromV++;

	size_of_detail_path = 2 * (ptrfPathFromV - fullPathFromV - 1);
	int* path_copy = (int*)malloc(WEIGHT_INT * (size_of_path + size_of_detail_path));

	ptrpath = path_copy;
	ptrfPathFromV = fullPathFromV;
	for (int i = 0; i < size_of_path; ) { // ��������� ����� ����, ���� ���������� ������ ���� �� ������� fullPathtoV[indGr * 2]
		if (i == indGr * 2) {
			*ptrpath++ = path[i++];
			*ptrpath++ = *ptrfPathFromV++;
			while (ptrfPathFromV < fullPathFromV + size_of_detail_path / 2 + 1) {
				*ptrpath = *(ptrpath - 1);
				ptrpath++;
				*ptrpath++ = *ptrfPathFromV++;
			}
			i++;
			continue;
		}
		*ptrpath++ = path[i++];
		*ptrpath++ = path[i++];
	}
	free(path);
	path = path_copy;
	size_of_path += size_of_detail_path;

	return size_of_path;
}
int TravellingSalesmanProblem(int*& path) {
	AdjList* pList;
	int* fullPathFromV;
	int size_of_path = Graphnum * 2;
	int** matrw = (int**)malloc(sizeof(int*) * Graphnum);
	for (int i = 0; i < Graphnum; i++)
		matrw[i] = (int*)malloc(WEIGHT_INT * Graphnum);

	for (int i = 0; i < Graphnum; i++) {
		pList = firstvertex[i]->ListOfVertices;
		for (int j = 0; j < Graphnum; j++)
			matrw[i][j] = 0;
		while (pList != NULL) {
			matrw[i][pList->vertex] = pList->weight;
			pList = pList->next;
		}
	}

	for (int indGr = 0; indGr < Graphnum; ) { // !!!!
		pList = firstvertex[path[indGr * 2]]->ListOfVertices;
		while (pList != NULL) {
			if (pList->vertex == path[indGr * 2 + 1])
				break;
			pList = pList->next;
		}
		if (pList != NULL) {
			indGr++;
			continue;
		}

		fullPathFromV = FullPathBetweenTwoVertex(path[indGr * 2], matrw);
		fullPathFromV = SortFullPathBetweenTwoVertex(path[indGr * 2], path[indGr * 2 + 1], fullPathFromV);
		size_of_path = AddFullPath(path, fullPathFromV, indGr);
	}
	for (int i = 0; i < Graphnum; i++)
		free(matrw[i]);
	free(matrw);

	return size_of_path;
}
void PrintPath(int* path, int size_of_path) {
	puts("\n");
	for (int i = 0; i < size_of_path;) {
		printf(" %d - %d \n", path[i], path[i + 1]);
		i += 2;
	}
	puts("\n");
}

void DeleteList(AdjList* pList) {
	AdjList* pList_next;

	while (pList != NULL) {
		pList_next = pList->next;
		free(pList);
		pList = pList_next;
	}
}
void DeleteGraph() {
	graph** pVertex = firstvertex;
	while (*pVertex != NULL) {
		DeleteList((*pVertex)->ListOfVertices);
		free(*pVertex++);
	}
	free(firstvertex);
}

