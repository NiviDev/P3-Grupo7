#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
// VARIABLE GLOBAL
int pausa = 0;

// PROTOTIPOS
void initABB(ArbolBB *a);
void resetABB(ArbolBB *a);
int localizarABB(ArbolBB *a, char* codigo);
int altaABB(ArbolBB *a, Articulo nuevo);
int bajaABB(ArbolBB *a, char* codigo);
int evocarABB(ArbolBB *a, Articulo *art);

// DEFINICIONES
void initABB(ArbolBB *a){
    (*a).cursor = NULL;
    (*a).cursorAux = NULL;
    (*a).raiz = NULL;
    (*a).cantArticulos = 0;
}

void resetABB(ArbolBB *a){
    (*a).cursor = (*a).raiz;
    (*a).cursorAux = NULL;
}

int localizarABB(ArbolBB *a, char* codigo){
    resetABB(a);
    int exito = 0;
    consultas = 0;

    if ((*a).cursor != NULL) { //cuando no esta vacio el arbol
        while (strcasecmp((*a).cursor->vipd.codigo, codigo) != 0) {
            (*a).cursorAux = (*a).cursor;
            if (strcasecmp((*a).cursor->vipd.codigo, codigo) < 0){
                (*a).cursor = (*(*a).cursorAux).hijoDerecho;
            }
            else{
                (*a).cursor = (*(*a).cursorAux).hijoIzquierdo;
            }
            consultas++;
            if ((*a).cursor == NULL){
                exito = 0;
                return exito;
            }
        }
        consultas++;
        exito = 1;
    }
    return exito;
}

int altaABB(ArbolBB *a, Articulo nuevo){
    int exito = 0;
    nodo *A;
    modificaPtr = 0;

    exito = localizarABB(a, nuevo.codigo);
    if (exito==0) {
        A = (nodo*) malloc(sizeof (nodo));
        if (A != NULL) {
            if ((*a).raiz == NULL) { //si esta vacio el arbol
                (*a).raiz = A;
                (*a).cursor = A;
                (*a).cursorAux = A;
            } else {
                if (strcasecmp((*a).cursorAux->vipd.codigo, nuevo.codigo) < 0) {
                    (*(*a).cursorAux).hijoDerecho = A;
                    (*a).cursor = (*(*a).cursorAux).hijoDerecho;
                } else {
                    (*(*a).cursorAux).hijoIzquierdo = A;
                    (*a).cursor = (*(*a).cursorAux).hijoIzquierdo;
                }
            }
            modificaPtr++;
            (a->cursor->vipd) = nuevo;
            a->cursor->hijoIzquierdo = NULL;
            a->cursor->hijoDerecho = NULL;
            (*a).cantArticulos++;
            exito = 1;
        } else // No hay memoria suficiente para cargar un nuevo articulo
            exito = 2;
    } else {
        exito = 0;
    }
    return exito;
}

int bajaABB(ArbolBB *a, char* codigo){
    int exito = 0, HI;
    nodo *Q;
    nodo *P;
    modificaPtr = 0;

    exito = localizarABB(a, codigo);
    if (exito==1) {
        if (lecOperaciones == 0) {
            printf("\n\n\t\t Datos del articulo:\n");
            mostrarArticulo(a->cursor->vipd);
            printf("\n\n\t\t Desea eliminar el articulo?\n\t\t1 - Eliminar\n\t\t2 - Volver\n\n\t\tOpcion: ");
            scanf("%d",&exito);
            getchar();
            while(exito != 1 && exito != 2){
                printf("\n\t\tOpcion invalida, intente nuevamente.\n\t\t1 - Eliminar\n\t\t2 - Volver\n\t\tOpcion: ");
                scanf("%d", &exito);
                getchar();
            }
        }else
            exito=comparar(auxArt, (*(*a).cursor).vipd); ///SI NO FUNCIONA EN COSTO REVISAR ESTA LINEA CON LINEA 93

        if (exito == 1) { //configuro eliminar nodo
            Q = (*a).cursor;
            if ((*a).cursorAux != NULL) {
                if ((*(*a).cursorAux).hijoIzquierdo != NULL && strcasecmp((*a).cursorAux->hijoIzquierdo->vipd.codigo, (*Q).vipd.codigo) == 0)
                    HI = 1;
                else
                    HI = 0;
            }
            if ((*(*a).cursor).hijoIzquierdo == NULL && (*(*a).cursor).hijoDerecho == NULL) { /// Caso 1: el nodo a eliminar no tiene hijos
                if ((*a).cursorAux == NULL) { //si el nodo es raiz
                    (*a).raiz = NULL;
                } else {
                    if (HI)
                        ((*(*a).cursorAux).hijoIzquierdo) = NULL;
                    else
                        ((*(*a).cursorAux).hijoDerecho) = NULL;
                }
                modificaPtr++;
            } else {
                if ((*(*a).cursor).hijoIzquierdo == NULL || (*(*a).cursor).hijoDerecho == NULL){ /// Caso 2: el nodo a eliminar tiene 1 hijo
                    if ((*a).cursorAux == NULL) { //si el nodo es raiz
                        if((*(*a).cursor).hijoIzquierdo != NULL){
                            (*a).raiz = (*(*a).cursor).hijoIzquierdo;
                        }
                        else{
                            (*a).raiz = (*(*a).cursor).hijoDerecho;
                        }
                    } else { // el nodo no es la raiz
                        if (HI){
                            if((*(*a).cursor).hijoIzquierdo != NULL){
                                (*(*a).cursorAux).hijoIzquierdo = (*(*a).cursor).hijoIzquierdo;
                            }
                            else{
                                (*(*a).cursorAux).hijoIzquierdo = (*(*a).cursor).hijoDerecho;
                            }
                        }
                        else{
                            if((*(*a).cursor).hijoIzquierdo != NULL){
                                (*(*a).cursorAux).hijoDerecho = (*(*a).cursor).hijoIzquierdo;
                            }
                            else{
                                (*(*a).cursorAux).hijoDerecho = (*(*a).cursor).hijoDerecho;
                            }
                        }
                    }
                    modificaPtr++;
                }else{ /// Caso 3: el nodo a eliminar tiene 2 hijos, politica de reemplazo(menor de los mayores)
                    P=Q;
                    Q=(*Q).hijoDerecho;
                        while ((*Q).hijoIzquierdo != NULL) {
                            P = Q;
                             Q = (*P).hijoIzquierdo;
                        }
                        a->cursor->vipd = Q->vipd;
                        modificaPtr++;
                        if(strcasecmp(P->vipd.codigo, a->cursor->vipd.codigo) != 0)
                            (*P).hijoIzquierdo =  Q->hijoDerecho;
                        else
                            (*(*a).cursor).hijoDerecho = Q->hijoDerecho;
                        modificaPtr++;
                        if ((*a).cursorAux == NULL)
                            (*a).raiz = a->cursor;
                }
            }
            (*a).cantArticulos--;
            free((void*) Q);
            return 1;
        } else {
            return 2; //decido no eliminar
        }
    }else{
        return 0; //no encontro la persona
    }
}

int evocarABB(ArbolBB *a, Articulo *art){
    int exito = 0;
    exito = localizarABB(a,(*art).codigo);
    if (exito == 1) {
         (*art)=(*(*a).cursor).vipd;
    }
    else{
        exito=0;
    }
    return exito;
}

void mostrarUnNodo(nodo *a){
    if(pausa % 5 == 0){
        system("pause");
        system("cls");
    }
    mostrarArticulo(a->vipd);
    printf("\t\tHijo izquierdo(Menor): ");
    if ((*a).hijoIzquierdo != NULL){
        printf("%s", (*(*a).hijoIzquierdo).vipd.codigo);
    }
    else{
        printf("-");
    }
    printf("\n\t\tHijo derecho(Mayor): ");
    if ((*a).hijoDerecho != NULL){
        printf("%s", (*(*a).hijoDerecho).vipd.codigo);
    }else{
        printf("-");
    }
    printf("\n\t\t-------------------------------------------------\n");
    if ((*a).hijoIzquierdo != NULL) {
        pausa++;
        mostrarUnNodo((*a).hijoIzquierdo);
    }
    if ((*a).hijoDerecho != NULL) {
        pausa++;
        mostrarUnNodo((*a).hijoDerecho);
    }
}

void mostrarTodoABB(ArbolBB *a){
    system("cls");
    printf("\n\t\tCantidad de articulos: %d\n\n", (*a).cantArticulos);
    resetABB(a);
    pausa = 0;
    mostrarUnNodo((*a).cursor);
    system("pause");
}

#endif // ABB_H_INCLUDED
