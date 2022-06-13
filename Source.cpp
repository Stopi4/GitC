#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <string.h>

#define SIZE 20
#define LEN 200


typedef struct inform {
    int index;
    char date[SIZE];
} INFORM;
typedef struct list_two_queue_element {
    struct list_two_queue_element* previous;
    INFORM inform;
    struct list_two_queue_element* next;
} LSTQ;

typedef struct list_single_stec_element {
    INFORM inform;
    struct list_single_stec_element* next;
} LSTSTC;

LSTQ* listQueue;
LSTSTC* listStack;


void MakeList();
int NumDayOfYearByDate(char*);
int MakeStcListFromQ(LSTQ*);
LSTQ* RemoveElementOfList(LSTQ*);
void TextDynamicArrOfString();

int main() {
    system("chcp 1251");

    int tst;
    printf("Виберіть спосіб задання інформації(Зчитування з текстового файлу - 1    Зчитування з консолі - 2): \n");
    while (true) {
        scanf("%d", &tst);
        if (tst == 1)
            TextDynamicArrOfString();
        else if (tst == 2)
            MakeList();
        else {
            printf("Введене неправильне значення! Повторіть спробу: ");
            continue;
        }
        break;
    }

    LSTQ* pListOper = listQueue;
    printf("\n\tДані елементів введеного списку: \n");
    while (pListOper != NULL) {
        printf("\tІндекс - %d \t Дата: ", pListOper->inform.index);
        puts(pListOper->inform.date);
        pListOper = pListOper->next;
    }

    if (MakeStcListFromQ(listQueue) == 0) {
        return 0;
    }


    LSTSTC* pListOperStack = listStack;
    printf("\n\tДані елементів створеного списку: \n");
    while (pListOperStack != NULL) {
        printf("\tІндекс - %d \t Дата: ", pListOperStack->inform.index);
        puts(pListOperStack->inform.date);
        pListOperStack = pListOperStack->next;
    }
    pListOper = listQueue;
    printf("\n\tДані елементів скороченого початкового списку: \n");
    while (pListOper != NULL) {
        printf("\tІндекс - %d \t Дата: ", pListOper->inform.index);
        puts(pListOper->inform.date);
        pListOper = pListOper->next;
    }

    pListOper = listQueue;
    while (listQueue != NULL) {
        listQueue = listQueue->next;
        free(pListOper);
        pListOper = listQueue;
    }
    pListOperStack = listStack;
    while(listStack != NULL){
        listStack = listStack->next;
        free(pListOperStack);
        pListOperStack = listStack;
    }
    return 0;
}

void MakeList() {
    static int num = 1;
    LSTQ* pListOper;

    pListOper = (LSTQ*)malloc(sizeof(LSTQ));
    if (pListOper == NULL) {
        puts("\n Недостатньо пам'яті! \n Формування списку завершено!\n");
        return;
    }
    printf("\n #%d елемент: індекс - ", num);
    scanf_s("%d", &pListOper->inform.index);
    if (pListOper->inform.index == 0) {
        free(pListOper);
        return;
    }
    num++;

    rewind(stdin);
    printf("Введіть дату у форматі дд.мм або дд місяць(21.02 або 21 лютого): \n\t");
    gets_s(pListOper->inform.date, SIZE);
    pListOper->next = NULL;
    pListOper->previous = NULL;
    listQueue = pListOper;

    LSTQ* last_el = listQueue;
    while (1) {
        pListOper = (LSTQ*)malloc(sizeof(LSTQ));
        if (pListOper == NULL) {
            puts(" Недостатньо пам'яті! \n Формування списку завершено!\n");
            return;
        }
        printf(" #%d елемент: індекс - ", num);
        scanf_s("%d", &pListOper->inform.index);
        if (pListOper->inform.index == 0) {
            free(pListOper);
            last_el = NULL;
            return;
        }
        num++;

        rewind(stdin);
        printf("Введіть дату у форматі дд.мм або дд місяць(21.02 або 21 лютого): \n\t");
        gets_s(pListOper->inform.date, SIZE);
        pListOper->next = NULL;
        last_el->next = pListOper;
        pListOper->previous = last_el;
        last_el = pListOper;
    }
}

void TextDynamicArrOfString() {
    FILE* fp_r;
    LSTQ* pListOperQ,
        * last_el;
    char buf[SIZE], fnamescan[LEN], * pOper;
    const char* fname = "C:\\Stopa. Політехніка\\Labs\\(1)Перший курс\\(2)Другий семестр\\Алгоритмізація та програмування\\Лабораторна 9\\Новий текстовий документ.txt";
    int index;

    printf("\nВведіть розташування текстового документа з реченнями(пустий рядок - текстовий документ за замовчуванням): \n");
    rewind(stdin);
    gets_s(fnamescan, LEN);
    if ((fp_r = fopen(fnamescan, "rt")) != NULL) // Створюємо потік  для читання, пов'язаний з файлом за адресою fname.
        fname = fnamescan;
    else {
        if ((fp_r = fopen(fname, "rt")) != NULL) {
            printf("Хибне ім\'я файлу - %s \n", fname); // Створюємо потік  для читання, пов'язаний з файлом за адресою fname_r.
            return;
        }
    }

    pListOperQ = (LSTQ*)malloc(sizeof(LSTQ));
    if (pListOperQ == NULL) {
        puts("\n Недостатньо пам'яті! \n Формування списку завершено!\n");
        return;
    }
    if ((fscanf(fp_r, "%d", &pListOperQ->inform.index) == 1)) {
        if (pListOperQ->inform.index == 0)
            return;

        fseek(fp_r, 2L, SEEK_CUR);
        pOper = buf;
        while (fscanf(fp_r, "%c", pOper) == 1) {
            if (*pOper == '\n')
                break;
            pOper++;
        }
        *pOper = '\0';

        strcpy(pListOperQ->inform.date, buf);
    }

    pListOperQ->next = NULL;
    pListOperQ->previous = NULL;
    listQueue = pListOperQ;
    last_el = listQueue;
    while ((fscanf(fp_r, "%d", &index) == 1)) {
        pListOperQ = (LSTQ*)malloc(sizeof(LSTQ));
        if (pListOperQ == NULL) {
            puts("\n Недостатньо пам'яті! \n Формування списку завершено!\n");
            return;
        }
        if (index == 0)
            break;

        pListOperQ->inform.index = index;
        pOper = buf;

        fseek(fp_r, 2L, SEEK_CUR);
        while (fscanf(fp_r, "%c", pOper) == 1) {
            if (*pOper == '\n')
                break;
            pOper++;
        }
        *pOper = '\0';

        strcpy(pListOperQ->inform.date, buf);

        last_el->next = pListOperQ;
        pListOperQ->previous = last_el;
        pListOperQ->next = NULL;
        last_el = pListOperQ;
    }
    fclose(fp_r);
}

int NumDayOfYearByDate(char* pstr) {
    const char* months_str[12] = { "січня", "лютого", "березня", "квітня", "травня", "червня",
                                   "липня", "серпня", "вересня", "жовтня", "листопада", "грудня" },
        limits[] = " ./,\'\"\\";
    int months_days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 },
        daysOfYear, daysOfYearCopy, monthOfYear, k;
    char* pOper;

    while (*pstr == ' ')
        pstr++;
    if (*pstr > '9' || *pstr < '0') {
        printf(" Неправильний формат введення дати - %s. \n", pstr);
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
        printf(" Неправильний формат введення дати - %s. \n", pstr);
        return 0;
    }
    pstr++;

    if (pOper == NULL) {
        daysOfYearCopy = daysOfYear;
        if (!(*pstr >= '0' && *pstr <= '9')) {
            printf(" Неправильний формат введення дати - %s. \n", pstr);
            return 0;
        }
        monthOfYear = *pstr++ - 48;
        if (*pstr >= '0' && *pstr <= '9') {
            monthOfYear *= 10;
            monthOfYear += *pstr++ - 48;
        }
        if (monthOfYear > 12 || monthOfYear < 1) {
            puts("Місяць введено неправильно!");
            return 0;
        }
        for (k = 0; k < monthOfYear - 1; k++) {
            daysOfYearCopy += months_days[k];
        }

    }
    if (daysOfYear > months_days[k] || daysOfYear < 1) {
        puts("День введено неправильно!");
        return 0;
    }

    return daysOfYearCopy;
}

int MakeStcListFromQ(LSTQ* ElementOfQList) {
    char date1[SIZE], date2[SIZE];
    int numDaysFir, numDaysSec, ValueOper, k;
    rewind(stdin);
    printf("\nВведіть першу дату: ");
    gets_s(date1);
    rewind(stdin);
    printf("Введіть другу дату: ");
    gets_s(date2);
    numDaysFir = NumDayOfYearByDate(date1);
    numDaysSec = NumDayOfYearByDate(date2);
    if (numDaysFir == 0 || numDaysSec == 0) 
        return 0;
    if (numDaysFir > numDaysSec) {
        ValueOper = numDaysFir;
        numDaysFir = numDaysSec;
        numDaysSec = ValueOper;
    }
    LSTSTC* pListOper;
    while (ElementOfQList != NULL) {
        ValueOper = NumDayOfYearByDate(ElementOfQList->inform.date);
        if (ValueOper == 0)
            return 0;
        if (ValueOper > numDaysFir && ValueOper < numDaysSec) {
            pListOper = (LSTSTC*)malloc(sizeof(LSTSTC));
            if (pListOper == NULL) {
                puts("\n Недостатньо пам'яті! \n Формування списку завершено!\n");
                return 0;
            }
            for (k = 0; ElementOfQList->inform.date[k] != '\0'; k++) {
                pListOper->inform.date[k] = ElementOfQList->inform.date[k];
            }
            pListOper->inform.date[k] = '\0';
            pListOper->inform.index = ElementOfQList->inform.index;
            pListOper->next = listStack;
            listStack = pListOper;
            ElementOfQList = RemoveElementOfList(ElementOfQList);
        }
        else
            ElementOfQList = ElementOfQList->next;
    }
    return 1;
}

LSTQ* RemoveElementOfList(LSTQ* ElementOfQList) {
    LSTQ* ElementPrevious = ElementOfQList->previous,
        * ElementNext = ElementOfQList->next;
    free(ElementOfQList);
    if (ElementPrevious == NULL) {
        ElementNext->previous = NULL;
        listQueue = ElementNext;
    }
    else if (ElementNext == NULL) {
        ElementPrevious->next = NULL;
    }
    else {
        ElementPrevious->next = ElementNext;
        ElementNext->previous = ElementPrevious;
    }
    return ElementNext;
}

