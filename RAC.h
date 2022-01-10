#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
/**
    Definicion de las funciones de un Rebalse Abierto Cuadratico.

    Notacion:
        La marca * indica celda virgen.
        La marca + indica celda libre.
*/
// PROTOTIPOS
void initRAC(RACuadratico *r);
int localizarRAC(RACuadratico r, char* codigo, int *exito);
void altaRAC(RACuadratico *r, Articulo nuevo, int *exito);
void evocarRAC(RACuadratico r, char* codigo, int *exito, Articulo *a);
void bajaRAC(RACuadratico *r, char* codigo, int *exito);

// DEFINICIONES
void initRAC(RACuadratico *r){
    /**
        Inicializa el RAL definiendo la cantidad como 0
        y asignando la marca de celda virgen "*" a cada
        elemento en el campo "codigo"
    */
    int i;
    r->cantidad = 0;
    for(i=0; i < M_RAC; i++)
        strcpy(r->rebalse[i].codigo, "*");
}

int localizarRAC(RACuadratico r, char* codigo, int *exito){
    int i, pos, libre = -1;
    int iteracion = 0;
    consultas = 0;

    i = hashing(codigo,M_RAC);
    while(iteracion < M_RAC && strcasecmp(r.rebalse[i].codigo, codigo) != 0 && (strcmp(r.rebalse[i].codigo,"*") != 0)){
        if(libre == -1 && strcmp(r.rebalse[i].codigo,"+") == 0)
            libre = i;
        iteracion++;
        i = ((i + iteracion) % M_RAC);
        consultas++;
    }
    if (iteracion < M_RAC){
        consultas++;
    }

    if(strcasecmp(r.rebalse[i].codigo, codigo) == 0){ //Encontro el elemento
        pos = i;
        *exito = 1;
    }else{
        if(iteracion >= M_RAC && libre == -1) //La estructura esta llena
            *exito = 2;
        else{
            if(libre != -1) //Si encontre alguna celda libre
                pos = libre; //Devuelvo la primera que encontre
            else
                pos = i; //Sino devuelvo la celda virgen
            *exito = 0;
        }
    }
    return pos;
}

void altaRAC(RACuadratico *r, Articulo nuevo, int *exito){
    int pos = 0;
    pos = localizarRAC((*r), nuevo.codigo, exito);
    if(*exito == 0){
        strcpy(r->rebalse[pos].codigo, nuevo.codigo);
        strcpy(r->rebalse[pos].tipo, nuevo.tipo);
        strcpy(r->rebalse[pos].marca, nuevo.marca);
        strcpy(r->rebalse[pos].descripcion, nuevo.descripcion);
        r->rebalse[pos].precio = nuevo.precio;
        r->rebalse[pos].cantidad = nuevo.cantidad;
        r->cantidad++;
        *exito = 1;
    }else{
        if(*exito == 1)
            *exito = 0; //El articulo ya existe
    }
}

void evocarRAC(RACuadratico r, char* codigo, int *exito, Articulo *a){
    int pos;
    Articulo nulo;
    pos = localizarRAC(r, codigo, exito);
    if(*exito == 1)
        *a = r.rebalse[pos];
    else
        *a = nulo;
}

void bajaRAC(RACuadratico *r, char* codigo, int *exito){
    int pos, aux;
    pos = localizarRAC((*r), codigo, exito);
    if(*exito == 1){
        if(lecOperaciones==0){
            printf("\n\n\t\t Datos del articulo:\n");
            mostrarArticulo(r->rebalse[pos]);
            printf("\n\n\t\t Desea eliminar el articulo?\n\t\t1 - Eliminar\n\t\t2 - Volver\n\n\t\tOpcion: ");
            scanf("%d", &aux);
            getchar();
            while(aux != 1 && aux != 2){
                printf("\n\t\tOpcion invalida, intente nuevamente.\n\t\t1 - Eliminar\n\t\t2 - Volver\n\t\tOpcion: ");
                scanf("%d", &aux);
                getchar();
            }
        }else
            aux=comparar(auxArt, r->rebalse[pos]);

        if(aux == 1){
            strcpy(r->rebalse[pos].codigo, "+");
            r->cantidad--;
            *exito = 1;
        }
        else
            *exito = 2;
    }
    else
        *exito = 0;
}

#endif // RAC_H_INCLUDED
