

#include <stdio.h>
#include <Windows.h>
#include <string.h>

#define SIZE 20

// ������� ������ � ����� ������ ��� �� �����.

typedef struct inform {
    int index;
    char date[SIZE];
} INFORM;
typedef struct list_two_element {
    struct list_two_element* previous;
    INFORM inform;
    struct list_two_element* next;
} LST;

typedef struct list_single_stec_element {
    INFORM inform;
    struct list_single_stec_element* next;
} LSTSTC;

LST* list;
LSTSTC* listStc;

void MakeList() {
    static int num = 1;
    LST* pListOper;

    pListOper = (LST*)malloc(sizeof(LST));
    if (pListOper == NULL)
        puts("\n ����������� ���'��! \n ���������� ������ ���������!\n");
    printf("\n #%d �������: ������ - ", num);
    scanf_s("%d", &pListOper->inform.index);
    if (pListOper->inform.index == 0) {
        free(pListOper);
        //list = NULL; // ----------------
        return;
    }
    num++;

    rewind(stdin);
    printf("������ ���� � ������ ��.�� ��� �� �����(21.02 ��� 21 ������): \n\t");
    gets_s(pListOper->inform.date, SIZE);
    pListOper->next = NULL;
    pListOper->previous = NULL;
    list = pListOper;

    LST* last_el = list;
    while (1) {
        pListOper = (LST*)malloc(sizeof(LST));
        if (pListOper == NULL) {
            puts(" ����������� ���'��! \n ���������� ������ ���������!\n");
            return;
        }
        printf("\n #%d �������: ������ - ", num);
        scanf_s("%d", &pListOper->inform.index);
        if (pListOper->inform.index == 0) {
            free(pListOper);
            last_el = NULL;
            return;
        }
        num++;

        rewind(stdin);
        printf("������ ���� � ������ ��.�� ��� �� �����(21.02 ��� 21 ������): \n\t");
        gets_s(pListOper->inform.date, SIZE);
        pListOper->next = NULL;
        last_el->next = pListOper;
        pListOper->previous = last_el;
        last_el = pListOper;
    }
}

int NumDayOfYearByDate(char *pstr) {
    //LST* pListOper = list;
    const char* months_str[12] = { "����", "������", "�������", "�����", "������", "������",
                                   "�����", "������", "�������", "������", "���������", "������" }, // ---------&&&&&&&&&&
        limits[] = " ./,\'\"\\";
    int months_days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 },
        daysOfYear, daysOfYearCopy, monthOfYear, k;
    //char* pstr = pListOper->inform.date, 
    char* pOper;

    //while (!(*pstr >= '0' && *pstr <= '9') && *pstr != '\0')
    while (*pstr == ' ')
        pstr++;
    //if (*pstr == '\0') {
    if (*pstr > '9' || *pstr < '0') {
        //printf(" ������������ ������ �������� ���� - %s. \n", pListOper->inform.date);
        printf(" ������������ ������ �������� ���� - %s. \n", pstr);
        return 0;
    }
    daysOfYear = *pstr++ - 48;
    if (*pstr >= '0' && *pstr <= '9') {
        daysOfYear *= 10;
        daysOfYear += *pstr++ - 48;
    }

    daysOfYearCopy = daysOfYear;
    for (k = 0; ((pOper = strstr(pstr, months_str[k])) == NULL) && k != 11; k++)
        daysOfYearCopy += months_days[k];
    if (strchr(limits, *pstr) == NULL || pOper != pstr + 1 && pOper != NULL) {
        //printf(" ������������ ������ �������� ���� - %s. \n", pListOper->inform.date);
        printf(" ������������ ������ �������� ���� - %s. \n", pstr);
        return 0;
    }
    pstr++;

    if (pOper == NULL) {
        daysOfYearCopy = daysOfYear;
        if (!(*pstr >= '0' && *pstr <= '9')) {
            //printf(" ������������ ������ �������� ���� - %s. \n", pListOper->inform.date);
            printf(" ������������ ������ �������� ���� - %s. \n", pstr);
            return 0;
        }
        monthOfYear = *pstr++ - 48;
        if (*pstr >= '0' && *pstr <= '9') {
            monthOfYear *= 10;
            monthOfYear += *pstr++ - 48;
        }
        if (monthOfYear > 12 && monthOfYear < 1) {
            puts("̳���� ������� �����������!");
            return 0;
        }
        for (k = 0; k < monthOfYear - 1; k++) {
            daysOfYearCopy += months_days[k];
        }

    }
    if (daysOfYear > months_days[k] || daysOfYear < 1) {
        puts("���� ������� �����������!");
        return 0;
    }

    return daysOfYearCopy;
}


void RemoveElementOfList(LST* ElementOfList) {
    LST * ElementPrevious = ElementOfList->previous,
        * ElementNext = ElementOfList->next;
    free(ElementOfList);
    if (ElementPrevious == NULL) {
        ElementNext->previous = NULL;
        list = ElementNext;
    }
    else if (ElementNext == NULL) {
        ElementPrevious->next = NULL;
    }
    else {
        ElementPrevious->next = ElementNext;
        ElementNext->previous = ElementPrevious;
    }
}

int main() {
    system("chcp 1251");

    MakeList();

    //PrintList()
    LST* pListOper = list;
    while (pListOper != NULL) {
        puts(pListOper->inform.date);
        pListOper = pListOper->next;
    }




    //XzNePridumav()
    char date1[SIZE], date2[SIZE];
    int numDaysFir, numDaysSec, ValueOper;
    printf("������ ����� ����: ");
    gets_s(date1);
    rewind(stdin);
    printf("������ ����� ����: ");
    gets_s(date2);
    numDaysFir = NumDayOfYearByDate(date1);
    numDaysSec = NumDayOfYearByDate(date2);
    if (numDaysFir > numDaysSec) {
        ValueOper = numDaysFir;
        numDaysFir = numDaysSec;
        numDaysSec = ValueOper;
    }
    
    while (pListOper != NULL) {
        ValueOper = NumDayOfYearByDate(pListOper->inform.date);
        if (ValueOper > numDaysFir && ValueOper < numDaysSec) { // �������� ���'��� ��� lsitStr, ���������� ���� ����������, ���������� pListOper NULL, ����� ���������� � RemoveElemen() ��� ��������� �� NULL, ��� ������ ������.
            listStc->inform.date = pListOper->inform.date;
            listStc->inform.index = pListOper->inform.index;
        }
    }



    //printf("ʳ������ ��� - %d", NumDayOfYearByDate());

    return 0;
}
