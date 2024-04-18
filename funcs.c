#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "funcs.h"

// Função para imprimir as reservas ordenadas por data (as mais antigas primeiro)
void printReservesByDate(reserveList list) {
    reserveList aux = create();

    list = list->next;
 // inserção nos elementos, sempre no inicio para obter assim a ordem pedida
    while(list) {
        insertBeginning(aux,list->reserve);
        list = list->next;
    }

    aux = aux->next; //para saltar o primeiro elemento que é nulo
    while (aux) {
        printf("Name: %s\n", aux->reserve.name);
        printf("Number: %ld\n", aux->reserve.number);
        printf("Type: %d\n", aux->reserve.type);
        printf("Hour: %02d:%02d\n", aux->reserve.hour.hours, aux->reserve.hour.minutes);
        printf("Date: %02d-%02d-%04d\n", aux->reserve.date.day, aux->reserve.date.month, aux->reserve.date.year);
        printf("\n");
        aux = aux->next;
    }
}

// Função para imprimir as reservas ou pre reservas de um cliente ordenadas por data.
void printReservesByClient(reserveList list) {
    struct Reserve Reserve;

    printf("What is the client phone number: ");
    scanf("%ld", &Reserve.number);
    clearInputBuffer();

    list = list->next;
    while(list){
        if (list->reserve.number == Reserve.number) {
            printf("Name: %s\n", list->reserve.name);
            printf("Type: %d\n", list->reserve.type);
            printf("Hour: %02d:%02d\n", list->reserve.hour.hours, list->reserve.hour.minutes);
            printf("Date: %02d-%02d-%04d\n", list->reserve.date.day, list->reserve.date.month, list->reserve.date.year);
            printf("\n");
        }
        list = list->next;
    }
}

void TimeSkip(reserveList Relist, reserveList PreRelist) {
    // Variáveis de iteração para a lista Relist
    reserveList current = Relist->next;
    reserveList prev = Relist;
    
    // Variáveis de iteração para a lista PreRelist
    reserveList currentpr = PreRelist->next;
    reserveList prevpr = PreRelist;

    // Obtém a data e a hora da primeira reserva de todas
    Date date = current->reserve.date;
    Hour hour = current->reserve.hour;

    // Variável para a seleção do usuário
    char *selection;
    selection = (char *) malloc(sizeof(char));

    // Exibe as opções para o usuário
    printf("-------------------- Chose what you want to do --------------------\n"
           "1- Skip 30 Minutes;\n"
           "2- Skip 1 Hour;\n"
           "3- Leave Skip Time.\n"
           "> ");

    // Lê a seleção do usuário
    *selection = getc(stdin);
    system("clear");
    clearInputBuffer();

    // Realiza uma ação com base na seleção do usuário
    switch (*selection) {
        case '1':
            // Verifica se adicionar 30 minutos ultrapassa os limites
            if ((hour.minutes + 30) > 59) {
                hour.minutes = 60 - (hour.minutes + 30);
                if (((hour.hours + 1) == 18 && hour.minutes > 0) || (hour.hours + 1) > 18) {
                    hour.hours = 8;
                    // Verifica se é possível avançar para o próximo dia/mês/ano
                    if (isValidDate((date.day + 1), date.month, date.year)) {
                        date.day++;
                    } else if (isValidDate(1, (date.month + 1), date.year)) {
                        date.day = 1;
                        date.month++;
                    } else {
                        date.day = 1;
                        date.month = 1;
                        date.year++;
                    }
                } else {
                    hour.hours++;
                }
            } else {
                hour.minutes += 30;
            }

            // Remove as reservas anteriores à nova data/hora
            while (current) {
                if (compareTimeDate(current->reserve.date, date, current->reserve.hour, hour) == -1) {
                    prev->next = current->next;
                    free(current->reserve.name);
                    free(current);
                    current = prev->next;
                } else {
                    prev = current;
                    current = current->next;
                }
            }

            // Remove as pre reservas anteriores à nova data/hora
            while (currentpr) {
                if (compareTimeDate(currentpr->reserve.date, date, currentpr->reserve.hour, hour) == -1) {
                    prevpr->next = currentpr->next;
                    free(currentpr->reserve.name);
                    free(currentpr);
                    currentpr = prevpr->next;
                } else {
                    prevpr = currentpr;
                    currentpr = currentpr->next;
                }
            }

            break;

        case '2':
            // Verifica se adicionar 1 hora ultrapassa os limites
            if (((hour.hours + 1) == 18 && hour.minutes > 0) || (hour.hours + 1) > 18) {
                hour.hours = 8;
                // Verifica se é preciso avançar para o próximo dia/mês/ano
                if (isValidDate((date.day + 1), date.month, date.year)) {
                    date.day++;
                } else if (isValidDate(1, (date.month + 1), date.year)) {
                    date.day = 1;
                    date.month++;
                } else {
                    date.day = 1;
                    date.month = 1;
                    date.year++;
                }
            } else {
                hour.hours++;
            }

            // Remove as reservas anteriores à nova data/hora
            while (current) {
                if (compareTimeDate(current->reserve.date, date, current->reserve.hour, hour) == -1) {
                    prev->next = current->next;
                    free(current->reserve.name);
                    free(current);
                    current = prev->next;
                } else {
                    prev = current;
                    current = current->next;
                }
            }

            // Remove as pre reservas anteriores à nova data/hora
            while (currentpr) {
                if (compareTimeDate(currentpr->reserve.date, date, currentpr->reserve.hour, hour) == -1) {
                    prevpr->next = currentpr->next;
                    free(currentpr->reserve.name);
                    free(currentpr);
                    currentpr = prevpr->next;
                } else {
                    prevpr = currentpr;
                    currentpr = currentpr->next;
                }
            }

            break;

        case '3':
            // Caso o usuário escolha sair, não é feito nada
            break;

        default:
            // Mensagem exibida caso a seleção seja inválida
            printf("Invalid choice, try again!\n");
            break;
    }
}

int compareDates(Date date1, Date date2) {
    if (date1.year < date2.year) {
        return -1;
    }else if(date1.year > date2.year){
        return 1;
    }else {
        if (date1.month < date2.month){
            return -1;
        }else if (date1.month > date2.month){
            return 1;
        } else{
            if (date1.day < date2.day){
                return -1;
            } else if (date1.day > date2.day ){
                return 1;
            }else
                return 0;
        }
    }
}

int compareHour(int hour1, int hour2){
    if (hour1 > hour2) {
        return 1;
    }else if (hour1 < hour2 ) {
        return -1;
    }else {
        return 0;
    }
}


int compareminute(int minute1, int minute2){
    if (minute1 > minute2) {
        return 1;
    }else if (minute1 < minute2 ) {
        return -1;
    }else {
        return 0;
    }
}

int compareTime(Hour time1 , Hour time2){
    int compare = compareHour(time1.hours, time2.hours);
    if (compare == 0 ) {
        compare = compareminute(time1.minutes,time2.minutes);
    }
    return compare;
}
int compareTimeDate(Date date1, Date date2, Hour time1 , Hour time2){
    int compare = compareDates(date1, date2);
    if (compare == 0 ) {
        compare = compareTime(time1,time2);
    }
    return compare;
}

Hour finalHour(struct Reserve reserve){
    Hour hourini = reserve.hour;
    Hour hourfin;

    hourfin.minutes = 0;
 // se for manutenção a hora final é a hora inicial mais 1 hora e se for uma lavagem adicionamos apenas 30 minutos
    if(reserve.type == 1){
        hourfin.hours = hourini.hours + 1;
        hourfin.minutes = hourini.minutes;
    }else{
        if(hourini.minutes >= 30){
            hourfin.minutes = hourini.minutes - 30;
            hourfin.hours = hourini.hours + 1;
        }
        else {
            hourfin.minutes += 30;
            hourfin.hours = hourini.hours;
        }
    }
    return hourfin;
}


int checkReserveCollision(struct Reserve newReserve, reserveList list) {
   reserveList current = list;
   Date new_reserve_date = newReserve.date;
   Hour new_reserve_hour = newReserve.hour;
   Hour new_reserve_Endhour = finalHour(newReserve);

    while (current != NULL) {
        Date toCompare_Date = current->reserve.date ;
        if (compareDates(new_reserve_date, toCompare_Date) == 0){
            Hour toCompareHour = current->reserve.hour;
            Hour toCompareEndHour = finalHour(current->reserve);
// vamos comparar a hora final da nova reserva com a da reserva a commparar e compararmos a hora final da reserva presente no current, com a hora inicial da nossa nova reserva pois, esta condição  é geral para sabermos se existe uma colisao de horarios
            if((compareTime(new_reserve_Endhour, toCompareHour) > 0 && compareTime(toCompareEndHour, new_reserve_hour) > 0)
            || new_reserve_hour.hours < 8 || new_reserve_Endhour.hours > 18 // verificar se a nossa nova reserva nao colide com "bordas" do horario de trabalho neste caso 08:00 e as 18:00
            || (new_reserve_Endhour.hours == 18 && new_reserve_Endhour.minutes > 0))
                return 1; //colisão
        }
       current = current->next;
    }
    return 0; // Não há colisão de horários
}

int isValidName(char *str) {

    for (int i = 0, length = strlen(str); i < length; i++) {
        if (!isalpha(str[i])) {
            return 0; // Contém um caractere que não é uma letra
        }
    }
    return 1; // Contém apenas letras
}

int isValidDate(int day, int month, int year) {
    if(year < 1807) {
        return 0; // Visto que o primeiro carro a motor foi criado neste exato ano;
    }

    if (month < 1 || month > 12) {
        return 0; 
    }

    if (day < 1 || day > 31) {
        return 0;
    }

    if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30)) {
        return 0;
    }

    if(year % 4 == 0) {
        if (month == 2 && day > 29) {
            return 0;
        }
    }else {
        if (month == 2 && day > 28) {
            return 0;
        }
    }

    return 1;
}

int isValidHour(int hours, int minutes, int reservationType) {
    if (hours < 8 || hours > 18) {
        return 0;
    }

    if (minutes < 0 || minutes > 59) {
        return 0;
    }

    if (reservationType == 1) {
        if (hours > 17 || (hours == 17 && minutes > 0)) {
            return 0;
        }
    } else if (reservationType == 2) {
        if (hours > 17 || (hours == 17 && minutes > 30)) {
            return 0;
        }
    }

    return 1;
}

void addReservation(reserveList Relist, reserveList PreRelist) {
    struct Reserve reserve; 

    reserve.name = (char *) malloc(50 * sizeof(char));

    do {
        printf("Enter the client name: ");
        scanf("%s", reserve.name);
        clearInputBuffer();

        if (!isValidName(reserve.name)) {
            printf("Invalid name. Please enter only letters.\n");
        }
    } while (!isValidName(reserve.name));

    printf("Enter the client phone number: ");
    scanf("%9ld", &reserve.number);
    clearInputBuffer();

    do {

        printf("Enter the type (1: Maintenance, 2: Wash): ");
        scanf("%d", &reserve.type);
        clearInputBuffer();

    } while(reserve.type != 1 && reserve.type != 2);

    do {

        printf("Enter the date (DD-MM-YYYY): ");
        scanf("%d-%d-%d", &reserve.date.day, &reserve.date.month, &reserve.date.year);
        clearInputBuffer();

        if (!isValidDate(reserve.date.day, reserve.date.month, reserve.date.year)) {
                printf("Invalid date. Please enter a valid date in the format DD-MM-YYYY.\n");
            }
    } while (!isValidDate(reserve.date.day, reserve.date.month, reserve.date.year));


    do {    
        printf("Enter the hour (HH:MM): ");
        scanf("%d:%d", &reserve.hour.hours, &reserve.hour.minutes);
        clearInputBuffer();

        if (!isValidHour(reserve.hour.hours, reserve.hour.minutes, reserve.type)) {
                if (reserve.type == 1) {
                    printf("Invalid time. Maintenance reservation cannot be scheduled after 17:00.\n");
                } else if (reserve.type == 2) {
                    printf("Invalid time. Wash reservation cannot be scheduled after 17:30.\n");
                }
            }
    } while (!isValidHour(reserve.hour.hours, reserve.hour.minutes, reserve.type));

    system("clear");


    if (checkReserveCollision(reserve, Relist)) { 
        printf("Reservation already exists for the specified date and hour.\n");

        char choice;
        printf("Do you want to make a pre-reservation? (Y/N): ");
        scanf("%c", &choice);
        clearInputBuffer();
        system("clear");

        if (choice == 'Y' || choice == 'y') {
            // se sim inserece na lista de pre reserva
            insert(PreRelist, reserve);

            printf("Pre-reservation added successfully.\n");
            system("clear");
        } else { // se nao podemos tentar reservar para outra hora
            printf("Do you want to try booking for another time? (Y/N): ");
            scanf("%c", &choice);
            clearInputBuffer();
            system("clear");

            if (choice == 'Y' || choice == 'y') {
                addReservation(Relist, PreRelist);
            }
        }
    } else {

        reserve.name = strdup(reserve.name);

        insert(Relist, reserve);

        printf("Reservation added successfully.\n");
    }
}


void CancelReserveByDate(reserveList Relist, reserveList PreRelist){
    struct Reserve reserve;

    printf("Enter the date (DD-MM-YYYY): ");
    scanf("%d-%d-%d", &reserve.date.day, &reserve.date.month, &reserve.date.year);
    clearInputBuffer();

    printf("Enter the hour (HH:MM): ");
    scanf("%d:%d", &reserve.hour.hours, &reserve.hour.minutes);
    clearInputBuffer();
    system("clear");

    reserveList current = Relist->next;
    reserveList prev = Relist;
    reserveList previous, waiting_current;
//
    while (current != NULL) {
        if (compareTimeDate(current->reserve.date, reserve.date, current->reserve.hour, reserve.hour) == 0){ // se as datas forem iguais ás digitadas eleminamos essa reserva
            prev->next = current->next;
            printf("Reservation canceled successfully.");
            system("clear");
            searchByTime(PreRelist, reserve.hour, reserve.date, &previous, &waiting_current); // pre-reserva guardada no waiting_current
            if(waiting_current != NULL && checkReserveCollision(reserve, waiting_current)){ // se a pre-reserva a ser inserida nao colidir com a data da reserva a ser eliminada,
                previous->next = waiting_current->next;
                waiting_current->next = current->next; // apartir daqui adiciona o elemento da prereserva á lista
                prev->next = waiting_current;
            }
            free(current->reserve.name);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("No reservation found for the specified date.");
    system("clear");
}

void CancelPreReserve(reserveList PreRelist){
    long phoneNumber;
    Hour hour;
    Date date;
// pedir ao utilizador a data e a hora da sua reserva assim como o numero de telemovel associado á mesma
    printf("Enter the date (DD-MM-YYYY): ");
    scanf("%d-%d-%d", &date.day, &date.month, &date.year);
    clearInputBuffer();

    printf("Enter the hour (HH:MM): ");
    scanf("%d:%d", &hour.hours, &hour.minutes);
    clearInputBuffer();

    printf("Enter the client's phone number: ");
    scanf("%ld", &phoneNumber);
    clearInputBuffer();
    system("clear");

    reserveList current = PreRelist->next;
    reserveList prev = PreRelist;
// se o numero digitado corresponder com o de uma reserva e se a funçao que compara o tempo e a data for verdadeira
    while(current){
    if(current->reserve.number == phoneNumber && compareTimeDate(current->reserve.date,date,current->reserve.hour, hour) == 0){
        prev->next = current->next;
        printf("Reservation canceled successfully.");
        
        system("clear");
        free(current->reserve.name);
        free(current);
        return;
        }
        prev = current;
        current = current->next;
    }

    printf("No pre-reservation found for the specified date.");
    system("clear");
}

void saveReservations(reserveList Relist, reserveList PreRelist) {
    // Abre os arquivos para escrita
    FILE *fileRelist = fopen("Relist.txt", "w");
    FILE *filePreRelist = fopen("PreRelist.txt", "w");

    // Verifica se houve erro na abertura dos arquivos
    if (fileRelist == NULL || filePreRelist == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Percorre a lista Relist e salva as informações no arquivo "Relist.txt"
    Relist = Relist->next;
    while (Relist) {
        fprintf(fileRelist, "Name: %49s\n", Relist->reserve.name);
        fprintf(fileRelist, "Number: %ld\n", Relist->reserve.number);
        fprintf(fileRelist, "Type: %d\n", Relist->reserve.type);
        fprintf(fileRelist, "Hour: %02d:%02d\n", Relist->reserve.hour.hours, Relist->reserve.hour.minutes);
        fprintf(fileRelist, "Date: %02d-%02d-%04d\n", Relist->reserve.date.day, Relist->reserve.date.month, Relist->reserve.date.year);
        fprintf(fileRelist, "\n");
        Relist = Relist->next;
    }

    // Percorre a lista PreRelist e salva as informações no arquivo "PreRelist.txt"
    PreRelist = PreRelist->next;
    while (PreRelist) {
        fprintf(filePreRelist, "Name: %49s\n", PreRelist->reserve.name);
        fprintf(filePreRelist, "Number: %ld\n", PreRelist->reserve.number);
        fprintf(filePreRelist, "Type: %d\n", PreRelist->reserve.type);
        fprintf(filePreRelist, "Hour: %02d:%02d\n", PreRelist->reserve.hour.hours, PreRelist->reserve.hour.minutes);
        fprintf(filePreRelist, "Date: %02d-%02d-%04d\n", PreRelist->reserve.date.day, PreRelist->reserve.date.month, PreRelist->reserve.date.year);
        fprintf(filePreRelist, "\n");
        PreRelist = PreRelist->next;
    }

    // Fecha os arquivos
    fclose(fileRelist);
    fclose(filePreRelist);

    // Exibe uma mensagem de sucesso
    printf("Reservations saved successfully.\n");
}

void uploadReservations(reserveList Relist, reserveList PreRelist) {
    // Declaração das estruturas de reserva
    struct Reserve reserve;
    struct Reserve prereserve;

    // Abre os arquivos para leitura
    FILE* fileRelist = fopen("Relist.txt", "r");
    FILE* filePreRelist = fopen("PreRelist.txt", "r");

    // Verifica se houve erro na abertura dos arquivos
    if (fileRelist == NULL || filePreRelist == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Aloca memória para o nome da reserva
    reserve.name = (char *) malloc(50 * sizeof(char));

    // Obtém o próximo nó da lista Relist
    reserveList current = Relist->next;

    // Lê as informações das reservas do arquivo "Relist.txt"
    while (fscanf(fileRelist, "Name: %49s\n", reserve.name) == 1) {
        fscanf(fileRelist, "Number: %ld\n", &reserve.number);
        fscanf(fileRelist, "Type: %d\n", &reserve.type);
        fscanf(fileRelist, "Hour: %02d:%02d\n", &reserve.hour.hours, &reserve.hour.minutes);
        fscanf(fileRelist, "Date: %02d-%02d-%04d\n\n", &reserve.date.day, &reserve.date.month, &reserve.date.year);

        // Verifica se há colisão de reservas
        bool checkCollision = false;
        while (current) {
            if (checkReserveCollision(reserve, current)) {
                checkCollision = true;
                break;
            }
            current = current->next;
        }

        // Verifica se o horário da reserva é válido
        if (checkCollision) {
            printf("The reservation for the date %02d-%02d-%04d and hour %02d:%02d already exists.\n", reserve.date.day, reserve.date.month, reserve.date.year, reserve.hour.hours, reserve.hour.minutes);
        } else if (!isValidHour(reserve.hour.hours, reserve.hour.minutes, reserve.type)) {
            if (reserve.type == 1) {
                printf("Invalid time. Maintenance reservation from %d-%d-%d cannot be scheduled after 17:00.\n", reserve.date.day, reserve.date.month, reserve.date.year);
            } else if (reserve.type == 2) {
                printf("Invalid time. Wash reservation from %d-%d-%d cannot be scheduled after 17:30.\n", reserve.date.day, reserve.date.month, reserve.date.year);
            }
        } else {
            // Insere a reserva na lista Relist
            insert(Relist, reserve);
        }

        // Aloca memória para o próximo nome de reserva
        reserve.name = (char *) malloc(50 * sizeof(char));
    }

    // Aloca memória para o nome da pré-reserva
    prereserve.name = (char *) malloc(50 * sizeof(char));

    // Lê as informações das pré-reservas do arquivo "PreRelist.txt"
    while (fscanf(filePreRelist, "Name: %49s\n", prereserve.name) == 1) {
        fscanf(filePreRelist, "Number: %ld\n", &prereserve.number);
        fscanf(filePreRelist, "Type: %d\n", &prereserve.type);
        fscanf(filePreRelist, "Hour: %02d:%02d\n", &prereserve.hour.hours, &prereserve.hour.minutes);
        fscanf(filePreRelist, "Date: %02d-%02d-%04d\n\n", &prereserve.date.day, &prereserve.date.month, &prereserve.date.year);

        // Verifica se o horário da pré-reserva é válido
        if (!isValidHour(prereserve.hour.hours, prereserve.hour.minutes, prereserve.type)) {
            if (prereserve.type == 1) {
                printf("Invalid time. Maintenance pre-reservation from %d-%d-%d cannot be scheduled after 17:00.\n", prereserve.date.day, prereserve.date.month, prereserve.date.year);
            } else if (prereserve.type == 2) {
                printf("Invalid time. Wash pre-reservation from %d-%d-%d cannot be scheduled after 17:30.\n", prereserve.date.day, prereserve.date.month, prereserve.date.year);
            }
        } else {
            // Insere a pré-reserva na lista PreRelist
            insert(PreRelist, prereserve);
        }

        // Aloca memória para o próximo nome de pré-reserva
        prereserve.name = (char *) malloc(50 * sizeof(char));
    }

    // Fecha os arquivos
    fclose(fileRelist);
    fclose(filePreRelist);

    // Exibe uma mensagem de sucesso
    printf("Reservations uploaded successfully.\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

