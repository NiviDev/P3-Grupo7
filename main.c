/**
Practico de maquina 3
Grupo 7
Integrante: Wang Chih Wen
            Viluron Nicolas

            Segun los datos obtenidos es claro que para este problema se
            debe utilizar alguna estructura de Rebalse Abierto, ya sea
            de paso Linear o Cuadratico, ambas arrojan buenos resultados
            de evocación considerando como función de costos la cantidad
            de celdas consultadas (nodos en caso del árbol). Ademas como
            se analizaron la cantidad de corrimientos (cantidad de
            modificaciones de punteros para el árbol) para los costos de
            las Altas y Bajas tenemos costo 0 en ambos Rebalses por la
            forma en la que esta estructura funciona.
**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "articulo.h"
#include "menu.h"
#include "RAL.h"
#include "RAC.h"
#include "ABB.h"
#include "LSO.h"
#include "LSOBT.h"
#include "lecturaOperacion.h"



int main(){
    int opc, opc1;
    RALineal ral;
    RACuadratico rac;
    ArbolBB abb;

    initRAL(&ral);
    initRAC(&rac);
    initABB(&abb);
    lso.ult=-1;
    lsobt.ult=-1;

    while(1){

        do{
            system("cls");
            printf("\n\n\n\t\t1 - Administracion de estructuras\n\n\t\t2 - Comparacion de Estructuras\n\n\t\t3 - Salir\n\n\nIngrese la opcion: ");
        }while((!scanf("%d",&opc1)||(opc1>3)||(opc1<=0)));
        system("cls");

        switch(opc1){
            case 1:{ // Administracion de estructuras
                lecOperaciones = 0;
                do{
                    system("cls");
                    printf("\n\n\n\t\t1 - Rebalse Abierto Lineal(RAL)\n\n\t\t2 - Rebalse Abierto Cuadratico(RAC)\n\n\t\t3 - Arbol Binario de Busqueda(ABB)\n\n\t\t4 - Lista Secuencial Ordenada(LSO)\n\n\t\t5 - Lista Secuencial Ordenada con Busqueda Binaria por Triseccion(LSOBT)\n\n\t\t6 - Salir\n\n\nIngrese la opcion: ");
                }while(!scanf("%d",&opc)||(opc>6)||(opc<=0));
                system("cls");
                switch(opc){
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:{
                        menu(&ral,&rac,&abb,&lso,&lsobt,opc);
                        break;
                    }
                    case 6:{
                        //exit(1);
                        break;
                    }
                }
                break;
            }
            case 2:{ //Comparacion de Estructuras
                lecOperaciones = 1;
                initRAL(&ral);
                initRAC(&rac);
                initABB(&abb);
                lso.ult=-1;
                lsobt.ult=-1;

                leerArchivo(&ral,&rac,&abb,&lso,&lsobt);

                break;
            }
            case 3:{
                exit(1);
            }
        }

    }


    return 0;
}
