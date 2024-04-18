#ifndef PROJECT_LIST_H
#define PROJECT_LIST_H
#include "structs.h"
#include "funcs.h"

typedef struct ReserveList{
    struct Reserve reserve;
    struct ReserveList *next;
} ReserveList;

typedef ReserveList *reserveList;

reserveList create();
void insert(reserveList list, struct Reserve reserve);
void insertBeginning(reserveList list, struct Reserve reserve);
void searchByTime(reserveList list,  Hour hour, Date date, reserveList *previous, reserveList *current);
int checkReserveCollision(struct Reserve newReserve, reserveList list);
void printReservesByDate(reserveList list);
void printReservesByClient(reserveList list);
void TimeSkip(reserveList Relist, reserveList PreRelist);
void addReservation(reserveList Relist, reserveList PreRelist);
void CancelReserveByDate(reserveList Relist, reserveList PreRelist);
void CancelPreReserve(reserveList PreRelist);
void saveReservations(reserveList Relist, reserveList PreRelist);
void uploadReservations(reserveList Relist, reserveList PreRelist);
void clearInputBuffer();

#endif
