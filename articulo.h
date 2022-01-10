#ifndef ARTICULO_H_INCLUDED
#define ARTICULO_H_INCLUDED
#define M_RAL 337 //Es el numero primo proximo a 333,333. Calculando M = N/ro siendo N = 250 y ro = 0,75
#define M_RAC 307//Es el numero primo proximo a 301,204. Calculando M = N/ro siendo N = 250 y ro = 0,83
#define MAX 250
int lecOperaciones = 0; //variable global
int corrimientos, modificaPtr, consultas;


typedef struct{ // a todos le sumo 2 porque en el scanf cuando pulso enter(\n) ocupa 2 caracter.
    char codigo[10]; //a lo sumo 8
    char tipo[22]; //a lo sumo 20
    char marca[32]; //a lo sumo 30
    char descripcion[102]; //a lo sumo 100 caracteres
    float precio; //El valor del articulo es un valor real positivo.
    int cantidad; //La cantidad es un numero entero positivo.
}Articulo;

Articulo auxArt;

///Definicion de estructura para Rebalse Abierto Lineal
typedef struct{
    int cantidad;
    Articulo rebalse[M_RAL];
}RALineal;

///Definicion de estructura para Rebalse Abierto Cuadratico
typedef struct{
    int cantidad;
    Articulo rebalse[M_RAC];
}RACuadratico;

///Definicion de estructura para ABB
struct N {
    Articulo vipd;
    struct N *hijoDerecho;
    struct N *hijoIzquierdo;
};
typedef struct N nodo;

struct arbolBinarioBusqueda {
    nodo *raiz;
    nodo *cursor;
    nodo *cursorAux;
    int cantArticulos;
};
typedef struct arbolBinarioBusqueda ArbolBB;

int hashing(char* x, int m){
    int longitud, i;
    int contador = 0;
    longitud = strlen(x);
    for (i = 0; i < longitud; i++)
        contador += ((int)x[i]) * (i + 1);
    return (contador % m);
}

///Definicion de estructura para LSO y LSOBT
typedef struct{
    int ult;
    Articulo listaArticulo[MAX];
} lista;

lista *l;
lista lso;
lista lsobt;


void mostrarArticulo(Articulo art){
    printf("\n******************\n");
    printf("Codigo: %s\n",art.codigo);
    printf("Tipo de Articulo: %s\n",art.tipo);
    printf("Marca: %s\n",art.marca);
    printf("Descripcion: %s\n",art.descripcion);
    printf("Precio: $%.2f\n",art.precio);
    printf("Cantidad en Deposito: %d\n",art.cantidad);
    printf("\n******************\n");
}

void mostrarTodo(lista *l){
    system("cls");
    int i;
    for (i=0; i<=l->ult; i++) {
        printf("\n\t\tPosicion en la lista: %d",i);
        mostrarArticulo(l->listaArticulo[i]);
        printf("\n-------------------------------------------\n");
        if((i+1) % 15 == 0){
            system("pause");
            system("cls");
        }
    }
    system("pause");
}

void mostrarRA(Articulo r[], int m){
    int i;
    for(i = 0; i < m; i++){
        printf("Posicion: %d\n", i);
        if (strcmp(r[i].codigo, "*") == 0)
            printf("\t\tCelda Virgen\n\n");
        else if(strcmp(r[i].codigo, "+") == 0)
            printf("\t\tCelda Libre\n\n");
        else
            mostrarArticulo(r[i]);
        printf("------------------------------------------------\n");
        if((i+1) % 30 == 0){
            system("pause");
            system("cls");
        }
    }
    system("pause");
}

void memorizacion(RALineal *ral, RACuadratico *rac, ArbolBB *a, lista *lso, lista *lsobt, int tipo){
    int aux;
    Articulo nuevo;
    FILE *fp = NULL;
    char* nombreArchivo = "Articulos.txt";

    if((fp = fopen(nombreArchivo,"r")) == NULL){
        printf("\n\n\t\tERROR: no se pudo abrir el archivo\n");
        system("pause");
    }
    else{
        while(!(feof(fp))){
            fscanf(fp,"%[^\n]s",&nuevo.codigo);
            fgetc(fp);
            fscanf(fp,"%[^\n]s",&nuevo.tipo);
            fgetc(fp);
            fscanf(fp,"%[^\n]s",&nuevo.marca);
            fgetc(fp);
            fscanf(fp,"%[^\n]s",&nuevo.descripcion);
            fgetc(fp);
            fscanf(fp,"%f",&nuevo.precio);
            fgetc(fp);
            fscanf(fp,"%d",&nuevo.cantidad);
            fgetc(fp);
            if(tipo == 1){
                if (ral->cantidad != M_RAL)
                    altaRAL(ral, nuevo, &aux);
            }
            else if(tipo == 2){
                if (rac->cantidad != M_RAC)
                    altaRAC(rac, nuevo, &aux);
            }
            else if(tipo == 3)
                aux = altaABB(a, nuevo);
            else if(tipo == 4){
                if (lso->ult+1 != MAX)
                    altaLSO(lso,nuevo,&aux);
            }
            else {
                if (lsobt->ult+1 != MAX)
                    altaLSOBT(lsobt,nuevo,&aux);
            }
        }
        fclose(fp);
        printf("\n\n\t\tCarga exitosa\n");
        system("pause");
    }
}

void toUpper(char* source){
    int longitud, i;
    longitud = strlen(source);
    for (i = 0; i < longitud; i++)
        if (source[i] > 96 && source[i] < 123) //Rango de minusculas en ascci
            source[i] = source[i] - 32;
        else
            source[i] = source[i];
}

int isNumeric(char *sample){
    int i, length, puntos;
    length = strlen(sample);
    puntos = 0;
    for(i = 0; i < length; i++){
        if(!isdigit(sample[i])){
            if(sample[i] == '.')
                puntos++;
            if(sample[i] != '.' || puntos > 1)
                return 0;
        }
    }
    return 1;
}

int comparar(Articulo p1, Articulo p2){
    int exito=0;
    if(strcasecmp(p1.codigo,p2.codigo)==0){
        if ((strcasecmp(p1.tipo, p2.tipo))==0){
            if ((strcasecmp(p1.marca, p2.marca))==0){
                if ((strcmp(p1.descripcion, p2.descripcion))==0){
                    if (p1.precio==p2.precio){
                        if (p1.cantidad==p2.cantidad){
                            exito=1;
                        }
                    }
                }
            }
        }
    }
    return exito;
}

#endif // ARTICULO_H_INCLUDED
