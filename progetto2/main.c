#include <stdio.h>
#include <unistd.h>
#include "heap.h"
#include "users.h"
#include "menu.h"
void test();

// 3 different menu's
void menu();
void usermenu(struct Graph *flys,struct User *user);
void adminmenu(struct Graph *flys,struct User_tree **users);


int main() {
    welcomeMessage();
    menu();
    //test();
    return 0;

}

void menu()
{

    struct User_tree **user = (struct User_tree**)malloc(sizeof(struct  User_tree));
    *user=NULL;
    char city[21][MAXLENCITY]={"london","mykonos","crete","milan","naples","barcellona","berlin","prague","rome","paris",
                              "palermo","venice","osaka","dubai","singapore","kuala","new york","istanbul","tokyo","antalya"};
    struct Graph *flys;
    flys = createGraph(20, city);
    populateEdge(flys);
    int choice=0,find;
    char username[255]="a",password[255]="a";
    insertUser(user, "silvia", "stranieri");
    do{
        system("cls");
        headMessage("MAIN MENU");
        printf("\n\t\t\t1.Register user");
        printf("\n\t\t\t2.Login as user");
        printf("\n\t\t\t3.Login as admin");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:

                do{
                    system("cls");
                    headMessage("User registration");
                    printf("\n\t\t\tInsert username: ");
                    scanf("%s",&username[0]);
                    find=findUser(user,username,"");
                    if(find < 0){//if find less then 0 means there isnt no account with same name
                        printf("\n\t\t\tInsert the password: ");
                        scanf("%s",&password[0]);
                        insertUser(user, username, password);
                        printf("\n\t\t\tAccount inserted ");
                        printf("\n\n\n\t\t\tPress enter to continue......");
                        getch();
                    } else{
                        printf("\n\t\t\tUsername already exist, retry! ");
                        sleep(2);
                    }
                }while(find >= 0);
                break;
            case 2:
                do{
                    system("cls");
                    headMessage("Login as user");
                    printf("\n\t\t\tInsert username: ");
                    scanf("%s",&username[0]);
                    printf("\n\t\t\tInsert the password: ");
                    scanf("%s",&password[0]);
                    find=findUser(user,username,password);

                    if(find == 1){//if find less then 0 means there isnt no account with same name
                        printf("\n\t\t\tUsername and password accepted ");
                        printf("\n\t\t\tWe bring you to the user menu! ");
                        sleep(3);
                        usermenu(flys,getUser(user,username,password));
                    } else{
                        printf("\n\t\t\tWrong username or password, retry! ");
                        sleep(2);
                    }

                }while(find != 1);
                break;
            case 3:
                do{
                    system("cls");
                    headMessage("Login as admin");
                    printf("\n\t\t\tInsert username: ");
                    scanf("%s",&username[0]);
                    printf("\n\t\t\tInsert the password: ");
                    scanf("%s",&password[0]);
                    if(strcmp(username,"silvia") == 0 && strcmp(password,"stranieri") == 0){
                        printf("\n\t\t\tUsername and password accepted ");
                        printf("\n\t\t\tWe bring you to the Admin menu! ");
                        sleep(2);
                        adminmenu(flys,user);
                        find=1;
                    } else{
                        printf("\n\t\t\tWrong username or password, retry! ");
                        find=-1;
                        sleep(2);
                    }

                }while(find < 0);
                break;
            case 0:
                printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
                sleep(2);
                exit(1);
            default:
                printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
                sleep(2);
        }
    }
    while(choice!=0);
}
void usermenu(struct Graph *flys,struct User *user) {
    int choice = 0, points = 0, val, pathdim, src, dest, price;
    int dist[flys->V], prec[flys->V], path[flys->V];
    char city1[255] , city2[255];

    do {
        system("cls");
        headMessage("USER MENU");
        printf("\n\t\t\t1.See rented fly");
        printf("\n\t\t\t2.See economic flight from a departure city to a destination");
        printf("\n\t\t\t3.See shorter flight from a departure city to a destination");
        printf("\n\t\t\t4.See economic flight from a departure city and no destination");
        printf("\n\t\t\t5.See most popular destination from a departure city");
        printf("\n\t\t\t6.See all destination from a departure city with price");
        printf("\n\t\t\t7.See all destination from a departure city with duration");
        printf("\n\t\t\t8.See cities popularity");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);

        switch (choice) {
            case 1:
                system("cls");
                headMessage("RENTED FLIGHTS");
                printlist(user->flightlist);
                printf("\n\n\n\t\t\tPress enter to continue......");
                getch();
                break;
            case 2:
                do{
                    system("cls");
                    headMessage("RENT AN ECONOMIC FLIGHTS");
                    printf("\n\t\t\tInsert departure city: ");

                    scanf("%s",&city1[0]);
                    src=findSrc(flys->array,flys->V,city1);
                    if(src==-1){
                        printf("\n\t\t\tdeparture city not present,retry!");
                        sleep(2);
                    }
                }while (src <= -1);
                do{
                    system("cls");
                    headMessage("RENT AN ECONOMIC FLIGHTS");
                    printf("\n\t\t\tInsert destination city: ");
                    scanf("%s",&city2[0]);
                    dest=findSrc(flys->array, flys->V, city2);
                    if(dest == -1){
                        printf("\n\t\t\tdestination city not present,retry");
                        sleep(2);
                    }
                }while (dest <= -1);
                dijkstraSrcDest(flys, src, dest, 1, dist, prec);

                do {
                    system("cls");
                    headMessage("RENT AN ECONOMIC FLIGHTS");
                    if (dist[dest] != INT_MAX) {
                        printBestFlyCity(flys, src, dest, dist, 1);
                        findPath(src,dest,prec,path,&pathdim);
                        printf("\n\t\t");
                        printPath(flys, path, pathdim);
                        printf("\n\n\t\t\tYou wanna rent this flight ?");
                        printf("\n\t\t\t1)yes");
                        printf("\n\t\t\t2)no");
                        printf("\n\n\n\t\t\tEnter choice => ");
                        val = 0;
                        scanf("%d", &val);
                        if (val == 1) {
                            if (getPoints(&user) >= 100) {
                                printf("\n\n\n\t\t\tentering in points ");
                                sleep(2);
                                system("cls");
                                headMessage("FLIGHTS");
                                printf("\n\t\t\t Wanna use your points to discount the flying ticket?");
                                printf("\n\t\t\t 1)yes");
                                printf("\n\t\t\t 2)no");
                                printf("\n\n\n\t\t\tEnter choice => ");
                                scanf("%d", &points);
                                if (points == 1) {
                                    push(&user->flightlist, city1, city2, dist[dest] / 2);
                                    deletePoints(&user, 100);
                                    flys->array[dest].visits++;

                                } else {
                                    push(&user->flightlist, city1, city2, dist[dest]);
                                    flys->array[dest].visits++;
                                    addPoints(&user, dist[dest]);
                                }
                            } else {
                                push(&user->flightlist, city1, city2, dist[dest]);
                                flys->array[dest].visits++;
                                addPoints(&user, dist[dest]);
                            }
                            printf("\n\n\n\t\t\tThank you for renting this flight");
                            sleep(2);
                        } else if (val == 2) {
                            printf("\n\n\n\t\t\t We bring you back to the user menu");
                            sleep(3);
                        } else {
                            printf("\n\n\n\t\t\tWrong choice, retry! ");
                            sleep(3);
                        }
                    } else{
                        printf("\n\n\n\t\t\t This route don't exist");
                        val=1;
                        sleep(3);
                    }
                }while (!(val >= 1 && val <= 2));
                break;
            case 3:
                do{
                    system("cls");
                    headMessage("RENT AN SHORTER FLIGHTS");
                    printf("\n\t\t\tInsert departure city: ");
                    scanf("%s",&city1[0]);
                    src=findSrc(flys->array,flys->V,city1);
                    if(src==-1){
                        printf("\n\t\t\tdeparture city not present, retry");
                        sleep(2);
                    }
                }while (src <= -1);
                do{
                    system("cls");
                    headMessage("RENT AN SHORTER FLIGHTS");
                    printf("\n\t\t\tInsert destination city: ");
                    scanf("%s",&city2[0]);
                    dest=findSrc(flys->array, flys->V, city2);
                    if(dest == -1){
                        printf("\n\t\t\tdestination city not present,retry");
                    }
                }while (dest <= -1);
                dijkstraSrcDest(flys, src, dest, 0, dist, prec);
                val=0;
                if (dist[dest] != INT_MAX){
                    do {
                        system("cls");
                        headMessage("RENT AN SHORTER FLIGHTS");
                        //finding all path price
                        findPath(src,dest,prec,path,&pathdim);
                        price = findPathPrice(flys, path, pathdim);
                        printBestFlyCity(flys, src, dest, dist, 0);
                        printf("\n\t\t");
                        printPath(flys, path, pathdim);
                        printf("\n\t\t\tWith price of %d",price);
                        printf("\n\n\n\t\t\tYou wanna rent this flight ?");
                        printf("\n\t\t\t1)yes");
                        printf("\n\t\t\t2)no");
                        printf("\n\n\n\t\t\tEnter choice => ");
                        scanf("%d", &val);
                        if (val == 1) {
                            if (getPoints(&user) >= 100) {
                                system("cls");
                                headMessage("RENT AN SHORTER FLIGHTS");
                                printf("\n\t\t\t Wanna use your points to discount the flying ticket?");
                                printf("\n\t\t\t 1)yes");
                                printf("\n\t\t\t 2)no");
                                printf("\n\n\n\t\t\tEnter choice => ");
                                scanf("%d", &points);
                                if (points == 1) {
                                    push(&user->flightlist, city1, city2, price / 2);
                                    deletePoints(&user, 100);
                                    flys->array[dest].visits++;

                                } else {
                                    push(&user->flightlist, city1, city2, price);
                                    flys->array[dest].visits++;
                                    addPoints(&user, price);
                                }
                            } else{
                                push(&user->flightlist, city1, city2, price);
                                flys->array[dest].visits++;
                                addPoints(&user, price);
                            }
                            printf("\n\n\n\t\t\tThank you for renting this flight");
                            sleep(2);
                        }else if (val == 2) {
                            printf("\n\t\t\t We bring you back to the user menu");
                            sleep(3);
                        }else{
                            printf("\n\t\t\tWrong choice, retry! ");
                            sleep(2);
                        }

                    }while (!(val >= 1 && val <= 2));
                }else{
                    printf("\n\n\n\t\t\tThis route don't exist");
                    sleep(3);
                }
                break;
            case 4:
                do{
                    system("cls");
                    headMessage("RENT ECONOMIC FLIGHTS(NO DESTINATION)");
                    printf("\n\t\t\tInsert departure city: ");
                    scanf("%s",&city1[0]);
                    src=findSrc(flys->array,flys->V,city1);
                    if(src==-1){
                        printf("\n\t\t\tdeparture city not present, retry");
                        sleep(2);
                    }
                }while (src < 0);
                dijkstra(flys, src, 1, dist, prec);
                val=0;
                do {
                    system("cls");
                    headMessage("RENT ECONOMIC FLIGHTS(NO DESTINATION)");
                    dest = printBestFly(flys, src, dist,1);
                    findPath(src,dest,prec,path,&pathdim);
                    printf("\n\t\t");
                    printPath(flys, path, pathdim);
                    if(dest != -1){
                        printf("\n\n\t\t\tYou wanna rent this flight ?");
                        printf("\n\t\t\t1)yes");
                        printf("\n\t\t\t2)no");
                        printf("\n\n\n\t\t\tEnter choice => ");
                        scanf("%d",&val);
                        if (val == 1) {
                            if (getPoints(&user) >= 100) {
                                system("cls");
                                headMessage("RENT ECONOMIC FLIGHTS(NO DESTINATION)");
                                printf("\n\n\t\t\tWanna use your points to discount the flying ticket?");
                                printf("\n\t\t\t1)yes");
                                printf("\n\t\t\t2)no");
                                printf("\n\n\n\t\t\tEnter choice => ");
                                scanf("%d", &points);
                                if (points == 1) {
                                    push(&user->flightlist, city1, flys->array[dest].city, dist[dest] / 2);
                                    deletePoints(&user, 100);
                                    flys->array[dest].visits++;
                                } else {
                                    push(&user->flightlist, city1, flys->array[dest].city, dist[dest]);
                                    flys->array[dest].visits++;
                                    addPoints(&user, dist[dest]);
                                }
                            } else {
                                push(&user->flightlist, city1, flys->array[dest].city, dist[dest]);
                                flys->array[dest].visits++;
                                addPoints(&user, dist[dest]);
                            }
                            printf("\n\n\n\t\t\tThank you for renting this flight");
                            sleep(2);
                        } else if (val == 2) {
                            printf("\n\n\n\t\t\tWe bring you back to the user menu");
                            sleep(3);
                        } else {
                            printf("\n\n\n\t\t\tWrong choice, retry! ");
                            sleep(3);
                        }
                    } else{
                        val=1;
                        printf("\n\n\n\t\t\tNo route from this departure");
                        sleep(3);
                    }
                }while (!(val >= 1 && val <= 2));
                break;
            case 5:
                do{
                    system("cls");
                    headMessage("RENT MOST POPULAR FLIGHTS");
                    printf("\n\t\t\tInsert departure city: ");
                    scanf("%s",&city1[0]);
                    src=findSrc(flys->array,flys->V,city1);
                    if(src==-1){
                        printf("\n\t\t\tDeparture city not present, retry");
                    }
                }while (src < 0);
                val=0;
                do {
                    system("cls");
                    headMessage("RENT MOST POPULAR FLIGHTS");
                    dest=printMostPopularCity(flys, dist , src, prec);
                    findPath(src,dest,prec,path,&pathdim);
                    printPath(flys, path, pathdim);
                    if (dest != -1) {
                        printf("\n\n\t\t\t You wanna rent this flight ?");
                        printf("\n\t\t\t1)yes");
                        printf("\n\t\t\t2)no");
                        printf("\n\n\n\t\t\tEnter choice => ");
                        scanf("%d", &val);
                        if (val == 1) {
                            if (getPoints(&user) >= 100) {
                                system("cls");
                                headMessage("RENT MOST POPULAR FLIGHTS");
                                printf("\n\n\t\t\tWanna use your points to discount the flying ticket?");
                                printf("\n\t\t\t1)yes");
                                printf("\n\t\t\t2)no");
                                printf("\n\n\n\t\t\tEnter choice => ");
                                scanf("%d", &points);
                                if (points == 1) {
                                    push(&user->flightlist, city1, flys->array[dest].city, dist[dest] / 2);
                                    deletePoints(&user, 100);
                                    flys->array[dest].visits++;

                                } else {
                                    push(&user->flightlist, city1, flys->array[dest].city, dist[dest] / 2);
                                    flys->array[dest].visits++;
                                    addPoints(&user, price);
                                }
                            }else {
                                push(&user->flightlist, city1, flys->array[dest].city, dist[dest]);
                                flys->array[dest].visits++;
                                addPoints(&user, price);
                            }
                            printf("\n\t\t\tThank you for renting this flight");
                            sleep(3);
                    }else if (val == 2) {
                            printf("\n\t\t\tWe bring you back to the user menu");
                            sleep(3);
                        }else{
                            printf("\n\t\t\tWrong choice, retry! ");
                            sleep(2);
                        }
                }else
                    val=1;
                }while (!(val >= 1 && val <= 2));
                break;
            case 6:
                do{
                    system("cls");
                    headMessage("SEE ALL CITY FLIGHTS BY PRICE");
                    printf("\n\t\t\tInsert departure city: ");
                    scanf("%s",&city1[0]);
                    src=findSrc(flys->array,flys->V,city1);
                    if(src==-1){
                        printf("\n\t\t\tDeparture city not present, retry");
                    }
                }while (src < 0);
                dijkstra(flys, src, 1, dist, prec);

                system("cls");
                headMessage("SEE ALL CITY FLIGHTS BY PRICE");
                printAllCities(flys, src, dist, prec, path, 1 );
                printf("\n\n\t\t\tPress enter to continue......");
                getch();
                break;
            case 7:
                do{
                    system("cls");
                    headMessage("SEE ALL CITY FLIGHTS AND DURATION ");
                    printf("\n\t\t\tInsert departure city: ");
                    scanf("%s",&city1[0]);
                    src=findSrc(flys->array,flys->V,city1);
                    if(src==-1){
                        printf("\n\t\t\tDeparture city not present, retry");
                    }
                }while (src < 0);
                dijkstra(flys, src, 0, dist, prec);

                system("cls");
                headMessage("SEE ALL CITY FLIGHTS AND DURATION");
                printAllCities(flys, src, dist, prec, path, 0 );
                printf("\n\n\t\t\tPress enter to continue......");
                getch();
                break;
            case 8:
                system("cls");
                headMessage("CITY POPULARITY");
                printCityPopularity(flys);
                printf("\n\n\n\t\t\tPress enter to continue......");
                getch();
                break;

        }

    } while (choice != 0);

}
void adminmenu(struct Graph *flys,struct User_tree **user){
    int choice=0, find=-2, find2=-2, price, duration;
    char city2[255], city1[255];
    do {
        system("cls");
        headMessage("ADMIN MENU");
        printf("\n\t\t\t1.Add flight city");
        printf("\n\t\t\t2.Add route between cities");
        printf("\n\t\t\t3.Remove city");
        printf("\n\t\t\t4.Remove route between cities");
        printf("\n\t\t\t5.Print city and near flight");
        printf("\n\t\t\t6.See reservations");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                system("cls");
                headMessage("NEW CITY");
                printf("\n\t\t\tInsert city name: ");
                scanf("%s",&city1[0]);
                find=findSrc(flys->array,flys->V,city1);
                if(find == -1){
                    addNodeGraph(flys,city1);
                } else{
                    printf("\n\t\t\tThis city already exist!");
                    sleep(3);
                }
                break;
            case 2:
                system("cls");
                headMessage("ADDING ROUTE");
                printf("\n\t\t\tInsert departure city name: ");
                scanf("%s",&city1[0]);
                printf("\n\t\t\tInsert destination city name: ");
                scanf("%s",&city2[0]);
                printf("\n\t\t\tInsert route price: ");
                scanf("%d",&price);
                printf("\n\t\t\tInsert route duration: ");
                scanf("%d",&duration);
                find=findSrc(flys->array,flys->V,city1);
                find2=findSrc(flys->array,flys->V,city2);


                if(find != -1 && find2 != -1){
                    addEdge(flys, find, find2, city2, price, duration);
                } else{
                    printf("\n\t\t\tCities not existent");
                    sleep(3);
                }
                break;
            case 3:

                system("cls");
                headMessage("REMOVING CITY");
                printf("\n\t\t\tInsert city name: ");
                scanf("%s",&city1[0]);
                find=findSrc(flys->array,flys->V,city1);
                if(find != -1){
                    deleteNodeGraph(flys,find,city1);
                } else{
                    printf("This city already not exist!");
                    sleep(3);
                }
                break;
            case 4:
                system("cls");
                headMessage("REMOVING EDGE");
                printf("\n\t\t\tInsert departure city name: ");
                scanf("%s",&city1[0]);
                printf("\n\t\t\tInsert destination city name: ");
                scanf("%s",&city2[0]);
                find=findSrc(flys->array,flys->V,city1);
                find2=findSrc(flys->array,flys->V,city2);
                if(find != -1 && find2 != -1){
                    deleteEdgeGraph(flys, find, city2);
                } else{
                    printf("\n\t\t\tCities not existent");
                    sleep(3);
                }
                break;

            case 5:
                system("cls");
                headMessage("CITIES AND NEAR ROUTE");
                printGraph(flys);
                printf("\n\n\n\t\t\tPress enter to continue......");
                getch();
                break;
            case 6:
                system("cls");
                headMessage("RESERVATIONS");
                printFlysForEachUser(user);
                printf("\n\n\n\t\t\tPress enter to continue......");
                getch();
                break;

            case 0:
                printf("\n\n\n\t\t\t\tGoing into main menu!!!\n\n\n\n\n");
                sleep(2);
                choice=0;
            default:
                printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
                sleep(2);
        }
    }
    while(choice!=0);
}