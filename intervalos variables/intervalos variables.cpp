#include <stdio.h>

int main() {
    double valoresX[5];
    double valoresY[5];
    double yp;
    
    printf("\033[0;33m	---------- INTERVALOS VARIABLES ----------\033[0m\n\n");

    printf("\033[0;32mIngrese los valores de xi:\033[0m \033[38;2;128;255;0m");
    scanf("%lf %lf %lf %lf %lf", &valoresX[0], &valoresX[1], &valoresX[2], &valoresX[3], &valoresX[4]);

    printf("\033[0;32mIngrese los valores de yi:\033[0m \033[38;2;128;255;0m ");
    scanf("%lf %lf %lf %lf %lf", &valoresY[0], &valoresY[1], &valoresY[2], &valoresY[3], &valoresY[4]);

    double valorInterpolar;
    do {
        printf("\n\033[0;32mIngrese el valor a interpolar (entre %.2lf y %.2lf):\033[0m \033[38;2;128;255;0m ", valoresX[0], valoresX[4]);
        scanf("%lf", &valorInterpolar);

        if (valorInterpolar < valoresX[0] || valorInterpolar > valoresX[4]) {
            printf("\033[1;31mError: El valor debe estar entre %.2lf y %.2lf. Inténtelo de nuevo.\033[0m\n", valoresX[0], valoresX[4]);
        }
    } while (valorInterpolar < valoresX[0] || valorInterpolar > valoresX[4]);

    if (valorInterpolar < valoresX[2]) {
        double p = (valorInterpolar - valoresX[0]) / (valoresX[1] - valoresX[0]);

        double d0 = valoresY[1] - valoresY[0];
        double d1 = valoresY[2] - valoresY[1];
        double d2 = valoresY[3] - valoresY[2];
        double d3 = valoresY[4] - valoresY[3];
        
        double d2_0 = d1 - d0;
        double d2_1 = d2 - d1;
        double d2_2 = d3 - d2;
        
        double d3_0 = d2_1 - d2_0;
        double d3_1 = d2_2 - d2_1;
        
        double d4_0 = d3_1 - d3_0;

        printf("\n\033[1;36m| i | xi    | yi       | delta y0   | delta^2 y0  | delta^3 y0  | delta^4 y0   |\n");
        printf("|---|--------|----------|-----------|------------|------------|------------|\n");
        printf("| 1 | %.2lf | %.4lf   | %.4lf    | %.4lf      |   %.4lf    |  %.4lf    |\n", valoresX[0], valoresY[0], d0, d2_0, d3_0, d4_0);
        printf("| 2 | %.2lf | %.4lf   | %.4lf    | %.4lf      |    %.4lf    |            |\n", valoresX[1], valoresY[1], d1, d2_1, d3_1);
        printf("| 3 | %.2lf | %.4lf   | %.4lf    | %.4lf      |              |            |\n", valoresX[2], valoresY[2], d2, d2_2);
        printf("| 4 | %.2lf | %.4lf   | %.4lf    |              |              |            |\n", valoresX[3], valoresY[3], d3);
        printf("| 5 | %.2lf | %.4lf   |           |              |              |            |\033[0m\n", valoresX[4], valoresY[4]);

        double k1 = p / 1;
        double k2 = (p * (p - 1)) / 2;
        double k3 = (p * (p - 1) * (p - 2)) / 6;
        double k4 = (p * (p - 1) * (p - 2) * (p - 3)) / 24;
        double k5 = (p * (p - 1) * (p - 2) * (p - 3) * (p - 4)) / 120;
        
        yp = valoresY[0] + k1*d0 + k2*d2_0 + k3*d3_0 + k4*d4_0;
        
        printf("\n\033[0;32mEl valor interpolado es:\n\033[0m \033[38;2;128;255;0my= %.4f", yp);
    }
    
    if (valorInterpolar > valoresX[2]) {
        double p = (valorInterpolar - valoresX[4]) / (valoresX[1] - valoresX[0]);

        double d0 = valoresY[1] - valoresY[0];
        double d1 = valoresY[2] - valoresY[1];
        double d2 = valoresY[3] - valoresY[2];
        double d3 = valoresY[4] - valoresY[3];
        
        double d2_0 = d1 - d0;
        double d2_1 = d2 - d1;
        double d2_2 = d3 - d2;
        
        double d3_0 = d2_1 - d2_0;
        double d3_1 = d2_2 - d2_1;
        
        double d4_0 = d3_1 - d3_0;

        printf("\n\033[1;36m| i | xi    | yi       | delta y0   | delta^2 y0  | delta^3 y0  | delta^4 y0   |\n");
        printf("|---|--------|----------|-----------|------------|------------|------------|\n");
        printf("| 1 | %.2lf | %.4lf   |          |            |            |           |\n", valoresX[0], valoresY[0]);
        printf("| 2 | %.2lf | %.4lf   | %.4lf    |            |             |            |\n", valoresX[1], valoresY[1], d0);
        printf("| 3 | %.2lf | %.4lf   | %.4lf    | %.4lf      |              |            |\n", valoresX[2], valoresY[2], d1, d2_0);
        printf("| 4 | %.2lf | %.4lf   | %.4lf    | %.4lf        | %.4lf        |            |\n", valoresX[3], valoresY[3], d2, d2_1, d3_0);
        printf("| 5 | %.2lf | %.4lf   | %.4lf     | %.4lf        | %.4lf        | %.4lf      |\033[0m\n", valoresX[4], valoresY[4], d3, d2_2, d3_1, d4_0);

        double k1 = p / 1;
        double k2 = ((p+1)* ((p+1) - 1)) / 2;
        double k3 = ((p+2) * ((p+2) - 1) * ((p+2) - 2)) / 6;
        double k4 = ((p+3) * ((p+3) - 1) * ((p+3) - 2) * ((p+3) - 3)) / 24;
        double k5 = ((p+4) * ((p+4)- 1) * ((p+4) - 2) * ((p+4) - 3) * ((p+4) - 4)) / 120;
        
        yp = valoresY[4] + k1*d3 + k2*d2_2 + k3*d3_1 + k4*d4_0;
        
        printf("\n\033[0;32mEl valor interpolado es:\n\033[0m \033[38;2;128;255;0my= %.4f", yp);
    }
	printf("\033[1;31m\n\n\n");

    return 0;
}

