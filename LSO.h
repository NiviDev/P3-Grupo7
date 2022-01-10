#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

///Prototipo
int localizarLSO(lista l, char codigo[10],int *exito);
void altaLSO(lista *l, Articulo articulo1, int *exito);
void bajaLSO(lista *l, char codigo1[10], int *exito);
Articulo evocarLSO(lista l,char codigo[10], int *exito);



int localizarLSO(lista l, char codigo[10],int *exito){
    int pos=0;
    *exito = 0;
    consultas = 0;

    while(pos < l.ult+1 && strcasecmp(l.listaArticulo[pos].codigo,codigo)<0){
        pos++;
        consultas++;
    }
    if(pos < l.ult+1){
        consultas ++;
    }
    *exito = (pos < l.ult+1 && strcasecmp(l.listaArticulo[pos].codigo,codigo)==0);
    return pos;
}

void altaLSO(lista *l, Articulo articulo1, int *exito){
    int pos, i;
    corrimientos = 0;
    pos = localizarLSO((*l),articulo1.codigo,exito);
    //Si no lo encontro, ajusta la lista y lo agrega donde corresponde
    if(*exito==0){
        for(i=l->ult+1; i>=pos+1; i--){
            strcpy(l->listaArticulo[i].codigo, l->listaArticulo[i-1].codigo);
            strcpy(l->listaArticulo[i].tipo, l->listaArticulo[i-1].tipo);
            strcpy(l->listaArticulo[i].marca, l->listaArticulo[i-1].marca);
            strcpy(l->listaArticulo[i].descripcion, l->listaArticulo[i-1].descripcion);
            l->listaArticulo[i].precio = l->listaArticulo[i-1].precio;
            l->listaArticulo[i].cantidad = l->listaArticulo[i-1].cantidad;
            corrimientos++;
        }
        strcpy(l->listaArticulo[i].codigo, articulo1.codigo);
        strcpy(l->listaArticulo[i].tipo, articulo1.tipo);
        strcpy(l->listaArticulo[i].marca, articulo1.marca);
        strcpy(l->listaArticulo[i].descripcion, articulo1.descripcion);
        l->listaArticulo[i].precio = articulo1.precio;
        l->listaArticulo[i].cantidad = articulo1.cantidad;
        l->ult++;
        *exito = 1;
    }
    else
        *exito = 0;
}

void bajaLSO(lista *l, char codigo1[10], int *exito){
    int pos, aux, i;
    pos = localizarLSO((*l),codigo1,exito);
    corrimientos = 0;
    if(*exito==1){
        if(lecOperaciones == 0){
            mostrarArticulo(l->listaArticulo[pos]);
            printf("\n\t\tDesea eliminar el articulo?\n\t\t1 - Eliminar\n\t\t2 - Volver\n\n\t\tOpcion: ");
            scanf("%d",&aux);
            getchar();
            while(aux != 1 && aux != 2){
                system("cls");
                printf("\n\t\tOpcion invalida, ingrese nuevamente.\n\t\t1 - Eliminar\n\t\t2 - Volver\n\t\tOpcion: ");
                scanf("%d", &aux);
                getchar();
        }
        }else
            aux=comparar(auxArt, l->listaArticulo[pos]);

        if(aux==1){
            for(i=pos; i<l->ult;i++){
                strcpy(l->listaArticulo[i].codigo,l->listaArticulo[i+1].codigo);
                strcpy(l->listaArticulo[i].tipo,l->listaArticulo[i+1].tipo);
                strcpy(l->listaArticulo[i].marca,l->listaArticulo[i+1].marca);
                strcpy(l->listaArticulo[i].descripcion,l->listaArticulo[i+1].descripcion);
                l->listaArticulo[i].precio = l->listaArticulo[i+1].precio;
                l->listaArticulo[i].cantidad = l->listaArticulo[i+1].cantidad;
                corrimientos++;
            }
            l->ult--;
        }
        else
            *exito = 2;
    }
}

Articulo evocarLSO(lista l,char codigo[10], int *exito){
    int pos;
    Articulo nulo;
    pos = localizarLSO(l,codigo,exito);
    if(*exito == 1)
        return l.listaArticulo[pos];
    else
        return nulo;
}

#endif // LSO_H_INCLUDED
