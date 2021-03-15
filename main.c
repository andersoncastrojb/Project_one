#include <stdio.h>
#include <stdlib.h>

int sum(int a, int b){
    return(a+b);
}

int main(void){

    int a = 0, b = 0, sal = 0;
    int operacion = 0;
    float resultado = 0;
    printf("This program is for numerical  calculation\r\n");
    printf("Sum, subtraction, multiplication, division\r\n");
    printf("Input first number\r\n--> ");
    scanf("%d",&a);
    printf("Input second number\r\n--> ");
    scanf("%d",&b);
    printf("Choose: Sum[1], subtraction[2], multiplication[3], division[4]\r\n--> ");

    while(sal < 1){

          scanf("%d",&operacion);

          if (operacion == 1){
              resultado = sum(a,b);
              sal = 1;
              printf("Result of the sum is: %f\r\n",resultado);
          }
          else{
                printf("Choose: Sum[1], subtraction[2], multiplication[3], division[4]\r\n--> ");
                sal = 0;
          }

    }


    return(0);
}


