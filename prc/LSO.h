#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED
#include <string.h>
#define VACIA -1
#define LLENA 250
#include "Articulo.h"

typedef struct {
    articulo arti[LLENA];
    int ult; // TIENE LA ULTIMA POSICION DONDE HAYA ARTICULOS.
    int cur;
}ListaArticulos;
void inicializar_lista(ListaArticulos *l){
    int i=0;
    (*l).ult=VACIA;
    (*l).cur=VACIA;
    for(i=0;i<LLENA;i++){
        inicializar(&(*l).arti[i]);
    }

}
int localizarBS(ListaArticulos l, int *pos,char codigo[],int *costo){
    int i;
    for(i=0;i<=l.ult;i++){
        *costo=*costo+1;
        if(strcmpi(codigo,l.arti[i].Codigo)<=0) // SI ME DA ENCONTRO EL CODIGO O ENCONTRO UNO QUE ESTA DESPUES LEXICOGRAFICAMENTE
            break;}
    *pos=i; // DEVUELVO LA POSICION DONDE ESTA O DONDE DEBERIA ESTAR
    return(i<=l.ult && strcmpi(codigo,l.arti[i].Codigo)==0); // SI LA ENCONTRO DEVUELVE UN 1
}
int alta(ListaArticulos *l,articulo a,int *costo)
{
    int pos=0,i=0,b;
    if (localizarBS(*l,&pos,a.Codigo,&b))
        return 0;
    else if (!((*l).ult==LLENA-1)){
        (*l).cur=pos;
        for(i = (*l).ult; i >= (*l).cur; i--){
            (*l).arti[i+1]=(*l).arti[i];
            *costo=*costo+1;}
        (*l).arti[(*l).cur]=a;
        (*l).ult++;
            return 2;}
        else
            return 1;
}
int baja(ListaArticulos *l,articulo auxi,int *costo,int admcomp){
    int pos=0,i,opcion,boolmenu,b;
    if(localizarBS((*l),&pos,auxi.Codigo,&b)){
        if(admcomp==2){//estoy comparando
            boolmenu=((strcmpi((*l).arti[pos].TipoDeArticulo,auxi.TipoDeArticulo)==0)&&(strcmpi((*l).arti[pos].Marca,auxi.Marca)==0)&&(strcmpi((*l).arti[pos].Descripcion,auxi.Descripcion)==0)&&((*l).arti[pos].PrecioUnitario==auxi.PrecioUnitario)&&((*l).arti[pos].CantidadExistente==auxi.CantidadExistente));
        if(boolmenu==0)
            return 3;} //aviso que no coinciden campos en comparar estructuras
        if(admcomp==1){
            printf("El elemento que quiere borrar es el siguiente:\n");
            printf("\nCodigo:%s",(*l).arti[pos].Codigo);
            printf("\nTipo de articulo:%s",(*l).arti[pos].TipoDeArticulo);
            printf("\nMarca:%s",(*l).arti[pos].Marca);
            printf("\nDescripcion:%s",(*l).arti[pos].Descripcion);
            printf("\nPrecio unitario %.2f",(*l).arti[pos].PrecioUnitario);
            printf("\nCantidad Existente:%d",(*l).arti[pos].CantidadExistente);
            do{
                printf("\nConfirma la baja del elemento?\n (1): Si (2) No\n");
                scanf("%d",&opcion);
            }while(opcion!=1 && opcion != 2);
                getchar();
                if(opcion==2)
                    return 2; //CANCELACION DE BAJA
            }
        for(i=pos;i<(*l).ult;i++){
            (*l).arti[i]=(*l).arti[i+1]; //corro los elementos una posicion a la izq. desde pos +1(borro lo que hay en pos)
            *costo=*costo+1;}
        (*l).ult--; //borro el repetido que es el ultimo
        return 1; //devuelvo true - baja exitosa
    }else //localización fracasa
        return 0; //retorno false porque el elemento no estaba

}
int evocacionAsociativa(ListaArticulos l,char codigo[],articulo *aux,int *costo){
    int pos=0,punt=0;
    if (localizarBS(l,&pos,codigo,&punt)){
        *aux=l.arti[pos];
        *costo=punt;
        return 1;}
    else{
        *costo=punt;
        return 0;}
}
void mostrar(ListaArticulos l){
    int i,m=0;
    for(i=0;i<=(l).ult;i++){
        printf("\nArticulo nro %d:\nCodigo:%s",i,l.arti[i].Codigo);
        printf("\nTipo de articulo:%s",l.arti[i].TipoDeArticulo);
        printf("\nMarca:%s",l.arti[i].Marca);
        printf("\nDescripcion:%s",l.arti[i].Descripcion);
        printf("\nPrecio unitario %.2f",l.arti[i].PrecioUnitario);
        printf("\nCantidad Existente:%d",l.arti[i].CantidadExistente);
        printf("\n*****************\n");
        if (i>0 && i%4==0)
        {system("PAUSE");}

        }

    }

int memorizacionPreviaLSO(ListaArticulos *lista){
    FILE *fp;
    int b;
    articulo aux;
    inicializar(&aux);
    if((fp = fopen("Articulos.txt","r"))==NULL){
        return 0;
    }
    else{
        while((!(feof(fp)))&&(!((*lista).ult==LLENA-1))){
                fscanf(fp,"%s\n",aux.Codigo);
                fscanf(fp,"%s\n",aux.TipoDeArticulo);
                fscanf(fp,"%s\n",aux.Marca);
                fscanf(fp,"%[^\n]s",aux.Descripcion);
                fscanf(fp,"%f\n",&aux.PrecioUnitario);
                fscanf(fp,"%d\n",&aux.CantidadExistente);
                alta(&(*lista),aux,&b);
        }
        fclose(fp);
        return 1;
    }
}
#endif // LSO_H_INCLUDED
