//
// Created by mario on 04/06/2020.
//
#include <unistd.h>

#include "menu.h"
/**********************************Menu function*****************************************/
// menu functions
void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len =(int)(74 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
void headMessage(const char *message)
{
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t############           __|__                                   ############");
    printf("\n\t\t\t############    --------(_)--------    Esposito Airlines       ############");
    printf("\n\t\t\t############      O  O       O  O                              ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
}
void welcomeMessage(){
    printf("\n\t\t\t############################################################################");
    printf("\n\t\t\t############           __|__                                   #############");
    printf("\n\t\t\t############    --------(_)--------    Esposito Airlines       #############");
    printf("\n\t\t\t############      O  O       O  O                              #############");
    printf("\n\t\t\t############################################################################");
    printf("\n\t\t\t----------------------------------------------------------------------------\n");

    printf("\n\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
    printf("\n\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t        =   __  _                                   =");
    printf("\n\t\t\t\t        =   \\ `/ |                                  =");
    printf("\n\t\t\t\t        =    \\__`!                                  =");
    printf("\n\t\t\t\t        =     / ,' `-.__________________            =");
    printf("\n\t\t\t\t        =     '-'\\_____ Esposito Air   []`-.        =");
    printf("\n\t\t\t\t        =         <____()-=O=O=O=O=O=[]====--)      =");
    printf("\n\t\t\t\t        =           `.___ ,-----,_______...-'       =");
    printf("\n\t\t\t\t        =                /    .'                    =");
    printf("\n\t\t\t\t        =               /   .'                      =");
    printf("\n\t\t\t\t        =              /  .'                        =");
    printf("\n\t\t\t\t        =              `-'                          =");
    printf("\n\t\t\t\t        =    Flights company by mario esposito      =");
    printf("\n\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t\t Enter any key to continue.....");
    getch();
}


