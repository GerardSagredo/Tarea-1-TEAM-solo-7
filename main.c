#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*  */

typedef struct {
  char* nombre;
  char* artista;
  char* genero;
  int año;
  char* lista;
}cancion;

int convertir_año(char* char_año){
  int año = 0;
  for(int i = 0 ; i < 4 ; i++){
    año *= 10;
    año += char_año[i] - 48;
  }
  return año;
}


void crear_cancion(List * canciones){
   
   
  char *au;
  cancion * c = (cancion *) malloc(sizeof(cancion));
  printf("ingrese el nombre: \n");
  scanf(" %[^\n]s", c->nombre);

  printf("ingrese el artista: \n");
  scanf(" %[^\n]s", c->artista);

  printf("ingrese el genero: \n");
  scanf(" %[^\n]s", c->genero);

  printf("ingrese el año: \n");
  scanf(" %d", &c->año);

  printf("ingrese la lista de reproduccion: \n");
  scanf(" %[^\n]s", c->lista);

   
  printf("%s  %s, %s, %d, %s\n ",c->nombre, c->artista,c->genero,c->año,c->lista);
    
}

void buscar_cancion (char *nombreBuscado, List *canciones){
  //se situa el current en la primera posicion
  int iguales,encontrado = 0;
  cancion *aux = firstList(canciones);
  while(aux != NULL){
    //The return value from strcmp is 0 if the two strings are equal
    iguales = strcmp(nombreBuscado,aux->nombre);
    if(iguales == 0){
      printf("%s, %s, %s, %d, %s \n",aux->nombre ,aux->artista, aux->genero, aux->año, aux->lista );
      encontrado++;
      break;
    }
    aux = nextList(canciones);
  }
  if(encontrado == 0){
    printf("No se encontraron coincidencias\n");
  }
}

//Funcion para leer el k-esimo elemento de un string (separado por comas)
char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
              ret[i-ini_i] = 0;
              return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
      ret[i-ini_i] = 0;
      return ret;
    }


    return NULL;
}


/*************************/
void buscar_artista (char *nombreBuscado, List *canciones);
void buscar_gen (char *nombreBuscado, List *canciones);
void buscar_lista (char *nombreBuscado, List *canciones);
void mostrar_listas(List *canciones);
/*************************/


int main(void) {
  int i=0;
  List *canciones = createList();
  
  FILE *fp = fopen ("Canciones.csv" , "r");
  // Cadena para guardar la linea completa del archivo csv
  char linea[1024];
  int k=0;
  while (fgets (linea, 1024, fp) != NULL) { // Se lee la linea
    cancion * c = (cancion *) malloc(sizeof(cancion));
    c->nombre = get_csv_field(linea, 0); // Se obtiene el nombre
    c->artista = get_csv_field(linea, 1);
    c->genero = get_csv_field(linea, 2);
    c->año = convertir_año(get_csv_field(linea, 3));
    c->lista = get_csv_field(linea, 4);
    pushBack(canciones,c);
    k++; if(k==70) break;
  }
  /*
  cancion *aux=firstList(canciones);
  while (aux!=NULL){
   printf("%s  %s, %s, %d, %s\n ",aux->nombre,aux->artista,aux->genero,aux->año,aux->lista);
    aux=nextList(canciones);
  }
  */
  char *nombreBuscado = (char*)malloc(50);  //se reserva memoria para cancion buscada
   printf("\n");
  printf("Ingrese un número:\n");
  printf("1 - Buscar canción por nombre\n");//<<<---- LISTO
  printf("2 - Agregar canción\n");
  printf("3 - Buscar canción por artista\n");//<<<---- LISTO
  printf("4 - Buscar canción por género\n");//<<<---- LISTO
  printf("5 - Eliminar canción(falta)\n");
  printf("6 - Mostrar nombres de las listas de reproducción(falta)\n");
 // printf("7 - Mostrar lista indicada(falta)\n");
  int opcion;
  scanf("%d",&opcion);
  switch(opcion){
    case 1:
      printf("\nIngrese un nombre para buscar: ");
      scanf(" %[^\n]s",nombreBuscado); 
      buscar_cancion(nombreBuscado,canciones);
      break;
    case 2:
      crear_cancion(canciones);
      break;
    case 3:
      printf("\nIngrese un artista para buscar: ");
      scanf(" %[^\n]s",nombreBuscado); 
      buscar_artista(nombreBuscado,canciones);
      break;
    case 4:
      printf("\nIngrese un genero para buscar: ");
      scanf(" %[^\n]s",nombreBuscado); 
      buscar_gen(nombreBuscado,canciones);
      break;
    case 5:

      printf("\nIngrese una cancion para eliminar: ");
     /* scanf(" %[^\n]s",nombreBuscado); 
      buscar_lista(nombreBuscado,canciones);*/
      break;
    
    case 6:
      printf("\nMostrar listas: ");
      scanf(" %[^\n]s",nombreBuscado); 
      mostrar_listas(canciones);
      break;
    /*case 7:
     printf("\nMostrar listas: ");
      scanf(" %[^\n]s",nombreBuscado); 
      buscar_lista(nombreBuscado,canciones);
      break;*/
      
  }
  

return 0;
}




void buscar_artista (char *nombreBuscado, List *canciones){
int iguales,encontrado = 0;
  cancion *aux = firstList(canciones);
 printf("cancion por artista: \n");
  while(aux != NULL){
   
    //The return value from strcmp is 0 if the two strings are equal
    iguales = strcmp(nombreBuscado,aux->artista);
    if(iguales == 0){

      
      printf("%s, %s, %s, %d, %s \n",aux->nombre ,aux->artista, aux->genero, aux->año, aux->lista );
      encontrado++;
    }
    aux = nextList(canciones);
  }
  if(encontrado == 0){
    printf("No se encontraron coincidencias\n");
  }
}


void buscar_gen (char *nombreBuscado, List *canciones){
int iguales,encontrado = 0;
char *busqueda;
  cancion *aux = firstList(canciones);
 printf("cancion por genero: \n");
  while(aux != NULL){
   
    //The return value from strcmp is 0 if the two strings are equal 
    //iguales = strcmp(nombreBuscado,aux->genero);

    busqueda= strstr(aux->genero, nombreBuscado);
    if(busqueda != NULL ){
      printf("%s, %s, %s, %d, %s \n",aux->nombre ,aux->artista,aux->genero, aux->año, aux->lista );
      encontrado++;
    }

    aux = nextList(canciones);
  }
  if(encontrado == 0){
    printf("No se encontraron coincidencias\n");
  }
}

void buscar_lista (char *nombreBuscado, List *canciones){
int iguales,encontrado = 0;
  cancion *aux = firstList(canciones);
  printf("cancion por lista: \n");
  while(aux != NULL){
   
    //The return value from strcmp is 0 if the two strings are equal
    iguales = strcmp(nombreBuscado,aux->lista);
    if(iguales == 0){

      
      printf("%s, %s, %s, %d, %s \n",aux->nombre ,aux->artista, aux->genero, aux->año, aux->lista );
      encontrado++;
    }
    aux = nextList(canciones);
  }
  if(encontrado == 0){
    printf("No se encontraron coincidencias\n");
  }
}

void mostrar_listas(List *canciones){

}

