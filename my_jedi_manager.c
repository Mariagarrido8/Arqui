#include <stdio.h>
#include "my_jedi_manager.h"
#include <string.h>  //Para los string
#include <stdlib.h>  //Para la memoria
#include <pthread.h>
#include <unistd.h>



/* La función que viene a continuación recoge strings escritos por teclado*/
	char * get_string() {
		    char * cadena = NULL;
		    size_t n = 0;
		    int nleidos;
		    nleidos = getline(&cadena, &n, stdin);
		    if (nleidos <= 0) {
		            fprintf(stderr, "Sales del programa\n");
		    } else {
		            if (cadena[nleidos-1] == '\n') cadena[nleidos-1] = '\0';
		    }
		    return cadena;
	}





	/* La función que viene a continuación recoge ints escritos por teclado*/

	int get_int () {
		    char * cadena = get_string();
		    int aux;
		    if (cadena == NULL) {
		            aux = -1;
		    } else {
		            aux = strtol(cadena, NULL, 10);
		            free(cadena);
		    }
		    return aux;
	}





	/* La función que viene a continuación recoge floats escritos por teclado*/

	int get_float () {
		    char * cadena = get_string();
		    float aux;
		    if (cadena == NULL) {
		            aux = -1;
		    } else {
		            aux = strtol(cadena, NULL, 10);
		            free(cadena);
		    }
		    return aux;
	}





	/* La función que viene a continuación compara dos char*, si son iguales devuelve un cero.
	Para ello se utiliza la función strcmp que podemos usar gracias a los ficheros incluidos en las
	primeras lineas del codigo*/

	int compare (char * string1, char * string2){
	int a;
	a=strcmp(string1,string2);
	return a;
	}

//Esta función sirve para imprimir el menú

	void imprimir_menu(){
			


			printf("=========================================\n");
			printf("[*][2017][SAUCEM APPS][JediManager]======\n");
			printf("=========================================\n");
			printf("[1] Salir\n");
			printf("[2] Insertar Jedi\n");
			printf("[3] Mostrar Jedis\n");
			printf("[4] Mostrar Jedi por ID\n");
			printf("[5] Modificar un Jedi por ID\n");
			printf("[6] Borrar Jedi por ID\n");
			printf("[7] Exportar Jedis a fichero binario\n");
			printf("[8] Importar Jedis de fichero binario\n");
			printf("[9] Simulador de combate Jedi\n");
			printf("[10] Ordenar Jedis por puntos de vida\n");
			printf("[11] Autosalvado Jedi (5 segundos, si ha habido cambios)\n");

			
		//	printf("\t\t\t#INFO: %i veces mostrado el menú principal\n",contador);

			
			
		
			

		
	}

//Esta función se encarga de introducir un Jedi a través de la línea de comandos. El nuevo elemento será creado en memoria dinámica para así poder ser manipulado en tiempo de ejecución.

	struct jedi *crear_jedi(int * error){
						struct jedi *j=malloc(sizeof(struct jedi));
						j->ptr_points= malloc(sizeof(struct points));
						*error=0;
					  printf("Insertando jedi\n");
					  printf("Dame el ID\t");
					  j->id=get_int();
					  printf("Dame el nombre\t");
					  j->s_full_name=get_string();
					  printf("Dame la vida\t");
					  j->ptr_points->hit_points=get_int();
					  printf("Dame el ataque aprendiz\t");
					  j->ptr_points->attack_array[T_APPRENTICE]=get_int();
					  printf("Dame la defensa aprendiz\t");
					  j->ptr_points->defense_array[T_APPRENTICE]=get_int();
					  printf("Dame la velocidad de aprendiz\t");
					  j->ptr_points->speed_array[T_APPRENTICE]=get_float();
					  printf("Dame el ataque maestro\t");
					  j->ptr_points->attack_array[T_MASTER]=get_int();
					  printf("Dame la defensa maestro\t");
					  j->ptr_points->defense_array[T_MASTER]=get_int();
					  printf("Dame la velocidad maestro\t");
					  j->ptr_points->speed_array[T_MASTER]=get_float();
					  printf("Es maestro (s/N)\t");
					  char * aux=NULL;
						
					  aux=get_string();
					  while(compare(aux,"s")!=0 && compare(aux,"N")!=0){
					  printf("Introduzca unicamente una N o una s, intentelo de nuevo\t");
					  aux=get_string();
					  
					  }
					if(compare(aux,"s")==0){
					  j->ptr_points->level=1;
					}else{
					j->ptr_points->level=0;
					}
					  return j;
	}
			
	  

//Esta opción muestra el identificador de todos los Jedis incluídos en el sistema

	void mostrar_jedis(struct lista_jedis *primero){
		  struct lista_jedis* auxiliar;
		  int i=0;
		  printf("==================================\n");
		  printf("|  ID|    Nomb. |Vida| Ata.| Def. |\n");
		  printf("==================================\n");
		  auxiliar=primero;
	  while(auxiliar!=NULL){
		if (auxiliar->j->ptr_points->level==T_MASTER){
		printf( "|  %d |   %.*s   | %d | %d | %d|\n", auxiliar->j->id,10,auxiliar->j->s_full_name,auxiliar->j->ptr_points->hit_points,auxiliar->j->ptr_points->attack_array[T_MASTER],auxiliar->j->ptr_points->defense_array[T_MASTER]);
		auxiliar=auxiliar->next;
	}
		else{
		printf( "|  %d |   %.*s   | %d | %d | %d|\n", auxiliar->j->id,10,auxiliar->j->s_full_name,auxiliar->j->ptr_points->hit_points,auxiliar->j->ptr_points->attack_array[T_APPRENTICE],auxiliar->j->ptr_points->defense_array[T_APPRENTICE]);
		auxiliar=auxiliar->next;
	  }
	  i++;
	}
	if (i==0) printf( "\nLa lista está vacía!!\n" );
	}

//Esta opción muestra toda la información de un Jedi incluido en el sistema. La forma de acceder a la información es mediante el identificador (ID) asociado al Jedi.

	void mostrar_inf_completa(struct lista_jedis *primero, int id){
	  struct lista_jedis* auxiliar;
	  auxiliar=primero;
	  printf("= Información completa de Jedi:\n");
	  while(auxiliar!=NULL && id!=auxiliar->j->id){
		auxiliar=auxiliar->next;
	  
	}
	if(auxiliar==NULL){
	  printf("No hay Jedi con ese ID");
	}
	else{
	  printf("= ID: %d \n" ,auxiliar->j->id);
	  printf("= Vida: %d \n",auxiliar->j->ptr_points->hit_points);
	  printf("= Nombre: %s \n",auxiliar->j->s_full_name);
	  printf("= Ataque de aprendiz: %d\n", auxiliar->j->ptr_points->attack_array[T_APPRENTICE]);
	  printf("= Defensa de aprendiz: %d\n",auxiliar->j->ptr_points->defense_array[T_APPRENTICE]);
	  printf("= Velocidad de aprendiz: %f\n", auxiliar->j->ptr_points->speed_array[T_APPRENTICE] );
	  printf("= Ataque de maestro: %d\n",auxiliar->j->ptr_points->attack_array[T_MASTER] );
	  printf("= Defensa de maestro: %d\n",auxiliar->j->ptr_points->defense_array[T_MASTER]);
	  printf("= Velocidad de maestro: %f\n",auxiliar->j->ptr_points->speed_array[T_MASTER] );
	  
	}
}

//Esta opción permitirá modificar todos los campos de un Jedi, cuyo ID se pasará a través de la línea de comandos.

struct lista_jedis *modificar_jedi(struct lista_jedis *primero, int id){
	struct lista_jedis *auxiliar;
    auxiliar=primero;
    while(auxiliar!=NULL && id!=auxiliar->j->id){
    	auxiliar=auxiliar->next;

	}
	if(auxiliar==NULL){
        printf(" No hay un jedi con ese id\n");
	}
	else{
		printf("Dame el nombre\t");
    	auxiliar->j->s_full_name=get_string();
    	auxiliar->j->size_name=strlen(auxiliar->j->s_full_name);
    	printf("Dame la vida\t");
    	auxiliar->j->ptr_points->hit_points=get_int();
    	printf("Dame el ataque aprendiz\t");
    	auxiliar->j->ptr_points->attack_array[0]=get_int();
    	printf("Dame la defensa aprendiz\t");
     	auxiliar->j->ptr_points->defense_array[0]=get_int();
    	printf("Dame el ataque maestro\t");
     	auxiliar->j->ptr_points->attack_array[1]=get_int();
    	printf("Dame la defensa maestro\t");
     	auxiliar->j->ptr_points->defense_array[1]=get_int();
    	printf("Dame la velocidad aprendiz\t");
     	auxiliar->j->ptr_points->speed_array[0]=get_float();
    	printf("Dame la velocidad maestro\t");
    	auxiliar->j->ptr_points->speed_array[1]=get_float();
    	printf("Es maestro (s/N)\t");
		char * aux=NULL;
    	aux=get_string();
    	while(compare(aux,"s")!=0 && compare(aux,"N")!=0){
      		printf("Introduzca unicamente una n o una s, intentelo de nuevo\t");
     	 	aux=get_string();
    	}
    	auxiliar-> j->ptr_points->level=1;
	}
	return primero ;
}

//Esta opción del menú se encargará de eliminar el identificador que se pasa a través de la línea de comandos.

struct lista_jedis *borrar_jedi(struct lista_jedis *primero, int id){
 	struct lista_jedis *aux=NULL;
 	struct lista_jedis *jedi_borrado=NULL; 
    	aux=primero;
	int i=0;
	while(aux!=NULL && id!=aux->j->id){
		
       		aux=aux->next;
		i++;
	}

	if(aux==NULL){
  		if(i==0){ 
  			printf( "\nLa lista está vacía!!\n" );
  		}
 		else{ 
  			printf(" No hay un jedi con ese id\n");
  		}
	}
	else if(i==0){
		jedi_borrado=primero; 
		primero=primero->next; 
		printf("El jedi con Id: %d ha sido eliminado con exito\n",jedi_borrado->j->id);
		free(jedi_borrado->j); 
		free(jedi_borrado);

	}

	else{ 
  		aux=primero;
  		while(id!=aux->next->j->id){
        	aux = aux->next;
  		}
  
  		jedi_borrado=aux->next;
  	
		aux->next=aux->next->next;
  		printf("El jedi con Id: %d ha sido eliminado con exito\n",jedi_borrado->j->id);
 		free(jedi_borrado->j); 
  		free(jedi_borrado);
	}
		return primero;
}

int main(){
   	 struct jedi *j=malloc(sizeof(struct jedi));
	struct lista_jedis *primero=NULL, *ultimo=NULL;
	struct lista_jedis *nuevo=NULL;
   	 int opcion=0;
do{
	
	imprimir_menu();
	
	opcion=get_int();

	switch(opcion){
			case 1:
			  printf("¿Está seguro de que desea salir del programa?[s/N]:\n");
		    char * answer = NULL;
		    answer = get_string();

		    if (compare(answer, "s") == 0){
		     printf("Has salido del programa");


		    } else if (compare(answer, "N") == 0){

		    opcion=0;

		    } else {

		    printf("\nError de lectura.\n");
		               opcion=0;
		    }
		     break;
			
				case 2: {int error=0;
        
               j = crear_jedi(&error);
	       nuevo = (struct lista_jedis *)malloc (sizeof(struct lista_jedis));
              if (error==1) {
      		fprintf(stderr, "Error, no se ha podido añadir a la lista el nuevo Jedi");
              }
	      else {
                if (nuevo==NULL) {
        		 printf( "No hay memoria disponible!\n");
         	}

				
					
		}

				nuevo = (struct lista_jedis *)malloc (sizeof(struct lista_jedis));
				nuevo->j = j;
				nuevo->next = NULL;
				if (primero==NULL) {
					primero = nuevo;
					ultimo = nuevo;
				}

						
				else{
						
					ultimo->next=nuevo;
					ultimo=nuevo;
					}
	}
			      
	    	 
								 
	
	  
				
					break;
				case 3:
				 mostrar_jedis(primero);
					break;
				case 4:{
				      int id=0;
				      printf("Introduce el ID del jedi del que quieres ver la informacion : \t");
				      id=get_int();
				      mostrar_inf_completa(primero, id);
				}
					break;
				case 5:{
					int id=0;
				    printf("Introduce el ID del jedi que quieres modificar : \t");
				    id=get_int();
					modificar_jedi(primero, id);
				}
					break;
				case 6:{
						int id=0;
				      	printf("Introduce el ID del jedi que quieres borrar : \t");
				      	id=get_int();
						primero=borrar_jedi(primero, id);
					}

					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;
				case 11:
					break;
				default:
					break;
			}


	


	
	
}while(opcion!=1);

	return 0;
}
	
