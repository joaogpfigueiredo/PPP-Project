#include <stdio.h>
#include <stdlib.h>
#include "list.h"


reserveList create(){
    reserveList aux;
    struct Reserve reserve = {"", 0, 0, {0, 0}, {0, 0, 0}};
    aux = (reserveList) malloc(sizeof (ReserveList));
    if (aux != NULL) {
        aux->reserve = reserve;
        aux->next = NULL;
    }
    return aux;
}


void searchByTime(reserveList list,  Hour hour, Date date, reserveList *previous, reserveList *current){
    *previous = list;
    *current = list->next;
    while ((*current) != NULL && (compareTimeDate((*current)->reserve.date, date, (*current)->reserve.hour, hour)==-1)) {
        *previous = *current;
        *current = (*current)->next;
    }
    if ((*current) != NULL && (compareTimeDate((*current)->reserve.date, date, (*current)->reserve.hour, hour)!=0))
        *current = NULL;
}

void insert(reserveList list, struct Reserve reserve) {
    reserveList no, previous, useless;
    no = (reserveList) malloc (sizeof (ReserveList));
    if (no != NULL) {
        no->reserve = reserve;
        searchByTime(list, reserve.hour, reserve.date, &previous, &useless);
        no->next = previous->next;
        previous->next = no;
    }
}

void insertBeginning(reserveList list, struct Reserve reserve ){
    reserveList no;
    no = (reserveList) malloc (sizeof (ReserveList));
    if (no != NULL) {
        no->reserve = reserve;
        no->next = list->next;
        list->next = no;
    }

}