#ifndef LSOBB_H_INCLUDED
#define LSOBB_H_INCLUDED

///Prototipo
int localizarLSOBT(lista *l, char codigo[10], int *exito);
void altaLSOBT(lista *l, Articulo articulo, int *exito);
void bajaLSOBT(lista *l, char codigo[10], int *exito);
Articulo evocarLSOBT(lista *l,char codigo[10], int *exito);


///Funciones
int localizarLSOBT(lista *l, char codigo[10], int *exito){ //inclusivo, exclusivo, segmento mas grande a la izquierda
    int li=0,ls=(l->ult)+1,m=0;
    *exito=0;
    consultas = 0;

    if(ls!=-1){
        m=floor((li+ls)/2.0); // pongo 2.0 para q el resultado de la division de un flotante y le puedo aplicar el floor (Segmento mas grande a la izquierda)
        //m=floor((li+ls-1)/2.0); // <-- Segmento mas grande a la derecha
        while(li!=ls && strcasecmp(l->listaArticulo[m].codigo,codigo) != 0){
            //costoLSOBT=costoLSOBT+1;
            if(strcasecmp(codigo,l->listaArticulo[m].codigo) > 0){
                li=m+1;
            }else{
                ls=m;
            }
            m=floor((li+ls)/2.0);
            consultas++;
        }
        if(li != ls){
            consultas ++;
        }
        if(li<ls){
            *exito=1;
        }else{
            if(m==-1) //Este caso para cuando haga alta en una lista con elementos y cargo en la primera posicion
                m++;
            else{
                if(strcasecmp(l->listaArticulo[m].codigo,codigo) < 0){
                    m++;
                }
            }
        }
    }
    return m;
}



void altaLSOBT(lista *l, Articulo articulo, int *exito){
    int pos, i;
    pos = localizarLSOBT(l,articulo.codigo,exito);
    corrimientos = 0;
    if(*exito == 0){
        for(i=l->ult+1; i>=pos+1; i--){
            strcpy(l->listaArticulo[i].codigo,l->listaArticulo[i-1].codigo);
            strcpy(l->listaArticulo[i].tipo,l->listaArticulo[i-1].tipo);
            strcpy(l->listaArticulo[i].marca,l->listaArticulo[i-1].marca);
            strcpy(l->listaArticulo[i].descripcion,l->listaArticulo[i-1].descripcion);
            l->listaArticulo[i].precio = l->listaArticulo[i-1].precio;
            l->listaArticulo[i].cantidad = l->listaArticulo[i-1].cantidad;
            corrimientos++;
        }
        l->ult++;
        strcpy(l->listaArticulo[i].codigo, articulo.codigo);
        strcpy(l->listaArticulo[i].tipo, articulo.tipo);
        strcpy(l->listaArticulo[i].marca, articulo.marca);
        strcpy(l->listaArticulo[i].descripcion, articulo.descripcion);
        l->listaArticulo[i].precio = articulo.precio;
        l->listaArticulo[i].cantidad = articulo.cantidad;
        *exito = 1;
    }else{
        *exito = 0;
    }
}

void bajaLSOBT(lista *l, char codigo[10], int *exito){
    int pos, aux=0,i;
    pos=localizarLSOBT(l, codigo, exito);
    corrimientos = 0;
    if(*exito == 1){
        if(lecOperaciones == 0){
            mostrarArticulo(l->listaArticulo[pos]);
            printf("\n\t\tDesea eliminar el articulo?\n\t\t1 - Eliminar\n\t\t2 - Volver\n\n\t\tOpcion: ");
            fflush(stdin);
            scanf("%d",&aux);
            while(aux!=1&&aux!=2){
                system("cls");
                printf("\n\t\tOpcion invalido, ingrese nuevamente.\n\t\t1 - Eliminar\n\t\t2 - Volver\n\t\tOpcion: ");
                fflush(stdin);
                scanf("%d",&aux);
            }
        }else
            aux=comparar(auxArt, l->listaArticulo[pos]);

        if(aux==1){ //decide eliminar
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
        }else{
            *exito = 2; // no decide eliminar
        }
    }
}

Articulo evocarLSOBT(lista *l,char codigo[10], int *exito){
    int pos;
    pos = localizarLSOBT(l, codigo, exito);
    if(*exito == 1){
        return l->listaArticulo[pos];
    }
}

#endif // LSOBB_H_INCLUDED
