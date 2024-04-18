#include <stdio.h>
#include <stdlib.h>
#include "main.h"


int main(){
    reserveList Relist;
    reserveList PreRelist;


    char *selection;
    int prot = 0;
    selection = (char *) malloc(sizeof(char));
    do {
        printf("-------------------- Chose what you want to do --------------------\n"
               "1- Make a reservation;\n"
               "2- Cancel a reservation or pre-reservation;\n"
               "3- List reservations or pre-reservation;\n"
               "4- Save and load reservation infos;\n"
               "5- Time Skip;\n"
               "6- Exit program.\n\n"
               "> ");
        *selection = getc(stdin);
        system("clear");
        clearInputBuffer();
        if(*selection < '1' || *selection > '6'){ // tabela ascii menor que 1 e maior que 4
            printf("Invalid choice, try again!\n");
            continue;
        }
        switch(*selection) {
            case '1':
                addReservation(Relist, PreRelist);
                break;
            case '2':
                printf("-------------------- Chose what you want to do --------------------\n"
                       "1- Cancel a Reservation;\n"
                       "2- Cancel a Pre-Reservation;\n"
                       "3- Back to Menu.\n\n"
                       "> ");
                scanf("%c", selection);
                system("clear");
                clearInputBuffer();
                if(*selection == '1'){
                    CancelReserveByDate(Relist, PreRelist);
                    continue;
                }else if(*selection == '2'){
                    CancelPreReserve(PreRelist);
                    continue;
                }else if(*selection == '3'){
                    break;
                }else {
                    printf("Invalid choice, try again!\n");
                    continue;
                }
            case '3':
                printf("-------------------- Chose what you want to do --------------------\n"
                       "1- List all reservations;\n"
                       "2- List all reservations for a customer;\n"
                       "3- List all pre-reservations;\n"
                       "4- List all pre-reservations for a customer;\n"
                       "5- Back to Menu.\n\n"
                       "> ");
                scanf("%c", selection);
                system("clear");
                clearInputBuffer();
                if(*selection == '1'){
                    printReservesByDate(Relist);
                    continue;
                }else if(*selection == '2'){
                    printReservesByClient(Relist);
                    continue;
                }else if(*selection == '3'){
                    printReservesByDate(PreRelist);
                    continue;
                }else if(*selection == '4'){
                    printReservesByClient(PreRelist);
                    continue;
                }else if(*selection == '5'){
                    break;
                }else {
                    printf("Invalid choice, try again!\n");
                    continue;
                }
            case '4':
                printf("-------------------- Chose what you want to do --------------------\n"
                       "1- Save reservations infos;\n"
                       "2- Load reservations infos;\n"
                       "3- Back to Menu.\n\n"
                       "> ");
                scanf("%c", selection);
                system("clear");
                clearInputBuffer();
                if(*selection == '1'){
                    saveReservations(Relist, PreRelist);
                    continue;
                }else if(*selection == '2'){
                    if (!prot) {
                    uploadReservations(Relist, PreRelist);
                    prot++;
                    }else {
                        printf("You can only upload files once!\n");
                    }
                    continue;
                }else {
                    printf("Invalid choice, try again!\n");
                    continue;
                }
            case '5':
                if(Relist->next != NULL){
                    TimeSkip(Relist, PreRelist);
                    break;
                }else{
                    printf("There is no reservations available.\nReturning to main menu.\n");
                    break;
                }
            case '6':
                exit(1);
            default:
                printf("Invalid choice, try again!\n");
                break;
        }
    }while(1);
    free(selection);
}