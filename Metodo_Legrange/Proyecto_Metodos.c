#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <ctype.h>
#define n 10
int i, j, t = n;

//prototipos de Funciones
char cargando(char carg[]);
double Mostrar_Tabla(double x[], double fx[], double puntos);
double lagrange_solucion(double x[], double fx[], double puntos, double valor);

//funciones

char cargando(char carg[]){
	for(i = 0; i < t; i++){
		printf("%c", carg[i%4]);
		fflush(stdout);
		usleep(250000);
		printf("\b");
	}
}

double Mostrar_Tabla(double x[], double fx[], double puntos){
	char carg[] = {'|', '/', '-','\\'};
	printf("procesando programa ");
	cargando(carg);
	system("cls");
	
	printf("+***************************************+\n"
		   "|Valores ingresados por el usuario      |\n"
		   "+---------------------------------------+\n"
	       "|i		|x		|f(x)	|\n");
	for(i = 0; i < puntos; i++){
		sleep(1);
		printf("|%d		|%.2lf		|%.4lf	|\n", i, x[i], fx[i]);
	}
	printf("+***************************************+\n");
	system("pause");
	
}

double lagrange_solucion(double x[], double fx[], double puntos, double valor){
	char carg[] = {'|', '/', '-','\\'};
	double resultado = 0.0, termino;
	printf("procesando programa ");
	cargando(carg);
	system("cls");
	printf("formulas a utilizar\n"
	       "fn(x) = sumatoria (Li(x)*%c(xi)) donde Li(x) = (x - xj)/(xi - xj)\n\n",159);
	for(i = 0; i < puntos; i++){
		termino = fx[i];
		sleep(1);
		
		for(j = 0; j < puntos; j++){
			if(j != i){
				printf("[(%.4lf - %.4lf)/(%.3lf - %.4lf)]", valor, x[j], x[i], x[j]);
				termino *= (valor - x[j]) / (x[i] - x[j]);
			}
		}
		printf(" * (%.3lf)",fx[i]);
		resultado += termino;
		printf("\nIteracion %d:\n", i + 1);
		printf("  Terminos Parciales: %.4lf\n\n", termino);
	}
	return resultado;
}

int main(int argc, char *argv[]) {
	double x[n], fx[n], valor, solucion;
	char op, minop, carg[] = {'|', '/', '-','\\'};
	int puntos;
	do{
		printf("+-----------------------------------+\n"
			   "|Metodo de Interpolacion de Lagrange|\n"
		       "+**************MENU*****************+\n"
			   "| a) Introducir valores             |\n"
			   "| b) Mostrar informacion            |\n"
			   "| c) Mostrar resultado              |\n"
			   "| d) salir del programa             |\n"
			   "+***********************************+\n");
		scanf("%c",& op);
		op = tolower(op);
		if(isdigit(op)){
			printf("ERROR! valor ingresado no corresponde a el menu\n");
			system("pause");
		}else{
			system("cls");
			switch(op){
				case 'a':
					printf("Procesando programa ");
					cargando(carg);
					system("cls");
					 
					printf("cantidad de puntos a interpolar\n");
					scanf("%d",&puntos);
					printf("¿que valor tendra x para evaluar?\n");
					scanf("%lf",&valor);
					printf("Intrododuce los valores de x0 hasta x%d\n", puntos-1);
					for(i = 0; i < puntos; i++){
						printf("x%d = ",i);
						scanf("%lf",& x[i]);			
					}
					printf("Introduce los valores de f(x)\n");
					for(i = 0; i < puntos; i++){
						printf("f(x%d) = ",i);
						scanf("%lf",& fx[i]);
					}
				break;
					
				case 'b':
					system("cls");
					Mostrar_Tabla(x, fx, puntos);
				break;
				
				case 'c':
					system("cls");			
					solucion = lagrange_solucion(x, fx, puntos, valor);
					printf("sumando los terminos parciales ");
					cargando(carg);
					printf("\nla aproximacion en x = (%.1lf) es = %.4lf\n", valor, solucion);
					system("pause");
				break;
			}
		}
	}while(op != 'd');
	printf("saliendo del programa ");
	cargando(carg);
	system("cls");
	printf("Fin del programa");
	return 0;
}