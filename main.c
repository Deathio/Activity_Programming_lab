#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <math.h>
// Custom Library
#include "myLibrary.h"

int sizeOfTheArray, limitOfTheCondition = 4, okay = 0;
double average;

void DefineLenght(double *);
void DigitValues(double *);
void ReturnPosition(double *);
void Error();
void RunMultiplier(double *);
void RunAverageWeighted(double *);
void SeeThelist(double *);

int main()
{
    double * numberList;
    int command = 0;

    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    numberList = malloc(sizeof(double) * sizeOfTheArray);

    while(1)
    {
        command = 0;
        printf("MENU: \n");
        printf(" 1. Informar a quantidade de números a tratar \n 2. Digitar os números \n 3. Informar o menor número \n 4. Informar o maior número \n 5. Retornar o n-ésimo número da lista \n");
        printf(" 6. Calcular a soma dos números \n 7. Calcular o produto dos números \n 8. Multiplicar todos os números por um valor \n 9. Calcular a média aritmética dos números \n");
        printf(" 10. Informar quantos números estão acima da média aritmética \n 11. Calcular a média ponderada dos números \n 12. Ordenar os números em ordem crescente \n 13. Ordenar os números em ordem decrescente \n 14. Terminar a execução \n");
        if(sizeOfTheArray > limitOfTheCondition && okay)
            SeeThelist(numberList);
        printf("Comando: ");
        scanf(" %d", &command);
        printf("\n");

        if(command == 1)
            DefineLenght(numberList);
        else if(command == 2)
            DigitValues(numberList);

        else if(sizeOfTheArray > limitOfTheCondition && okay && command < 14)
        {
            if(command == 3)
                printf("O menor número da lista é o valor: %.1f\n\n", ShortestNumber(numberList, sizeOfTheArray));
            else if(command == 4)
                printf("O maior número da lista é o valor: %.1f\n\n", LargestNumber(numberList, sizeOfTheArray));
            else if(command == 5)
                ReturnPosition(numberList);
            else if(command == 6)
                printf("A soma de todos os números é igual ao número: %.1f\n\n", ListSum(numberList, sizeOfTheArray));
            else if(command == 7)
                printf("O produto de todos os números é igual ao número: %.1f\n\n", ListProduct(numberList, sizeOfTheArray));
            else if(command == 8)
                RunMultiplier(numberList);
            else if(command == 9)
                printf("A média de todos os números da lista é igual ao número: %.1f\n\n", average);
            else if(command == 10)
                printf("A quantidade de números acima da média é: %d\n\n", AverageForCounter(numberList, average, sizeOfTheArray));
            else if(command == 11)
                RunAverageWeighted(numberList);
            else if(command == 12)
                SortGrowingList(numberList, sizeOfTheArray);
            else if(command == 13)
                SortDescendingList(numberList, sizeOfTheArray);
        }
        else if(command == 14)
            return 0;
        else
            Error();
    }
}
void Error()
{
    if(sizeOfTheArray > limitOfTheCondition && okay == 0)
        printf("Digite os valores da nova lista criada\n\n\a");
    else if((sizeOfTheArray < limitOfTheCondition && okay == 0) || (sizeOfTheArray < limitOfTheCondition && okay == 1))
        printf("Digite o tamanho da nova lista\n\n\a");
    else
        printf("O comando digitado é inválido\n\n\a");
}
void DefineLenght(double * numberList)
{
    sizeOfTheArray = 0;

    while(sizeOfTheArray < 5 || sizeOfTheArray > 15)
    {
        printf("Aqui você irá definir o tamanho da lista, lembre-se ela tem que estar entre 5 e 15\n");

        printf("Defina o tamanho da lista: ");
        if(scanf(" %d", &sizeOfTheArray) != 1)
            printf("\a\nLembrando somente tipos númericos!\n");
        printf("\n");
        fflush(stdin);
    }

    numberList = malloc(sizeof(double) * sizeOfTheArray);
    okay = 0;
}
void DigitValues(double * numberList)
{
    int loopValue;

    if(sizeOfTheArray > limitOfTheCondition)
    {
        printf("Agora digite os valores reais que você deseja colocar em cada posição, porém lembre-se \nos números tem que estar entre -100 e 500, não podem ser multiplos de 8, diferentes de 0 e que para colocar os decimais use a ,\n");
        while(loopValue < sizeOfTheArray)
        {
            int isNum = 0;
            double inputValue = 0;
            printf("Digite o valor da posição %d da lista: ", loopValue);

            if(scanf(" %lf", &inputValue) == 1)
                isNum = 1;

            if(inputValue >= -100 && inputValue <= 500 && isNum && fmod(inputValue, 8) != 0)
            {
                numberList[loopValue] = inputValue;
                loopValue++;
            }
            else
            {
                printf("\a\nLembre-se dos tipos númericos, diferentes de 0, diferentes dos multiplos de 8 e dos valores máximos e mínimos, \n");
            }
            fflush(stdin);
        }
        okay = 1;
        average = ListAverage(numberList, sizeOfTheArray);
        printf("\n");
    }
    else
    {
        Error();
    }
}
void ReturnPosition(double * numberList)
{
    int position = -1, isNum = 0;

    while(position < 0 || position > sizeOfTheArray - 1 || isNum == 0)
    {
        isNum = 0;
        printf("Diga a posição do número que deseja retornar (ele tem que estar entre 0 e %d)\n", sizeOfTheArray - 1);

        printf("Posição: ");

        if(scanf(" %d", &position) == 1)
            isNum = 1;
        else
            printf("\a\nLembrando somente tipos númericos!\n");

        printf("\n");
    }
    double value = numberList[position];
    printf("O número nessa posição é o %.1f\n\n", value);

}
void RunMultiplier(double * numberList)
{
    double value = 0;
    int isNum = 0;

    while(value == 0 && isNum == 0)
    {
        isNum = 0;
        printf("Digite o número que vai ser multiplicado pela lista de valores (Lembre-se ele tem de ser diferente de 0)\n");
        printf("Número: ");

        if(scanf(" %lf", &value) == 1)
            isNum = 1;
        else
            printf("\a\nLembrando somente tipos númericos!\n");

        printf("\n");
    }

    MultiplyTheList(numberList, value, sizeOfTheArray);
    average = ListAverage(numberList, sizeOfTheArray);
}
void RunAverageWeighted(double * numberList)
{
    double * weightList;
    int loopValue = 0, isNum = 0;

    weightList = malloc(sizeof(double) * sizeOfTheArray);

    printf("Para saber a média ponderada precisamos dos pesos de cada valor\n");

    while(loopValue < sizeOfTheArray || isNum == 0)
    {

        printf("Digite o peso da posição %d da lista: ", loopValue);

        if(scanf(" %lf", &weightList[loopValue]) == 1)
            isNum = 1;
        else
            printf("\a\nLembrando somente tipos númericos!\n");

        loopValue++;
        fflush(stdin);
    }

    printf("\nA média ponderada de todos os números da lista é igual ao número: %.1f\n\n", ListAverageWeighted(numberList, weightList, sizeOfTheArray));
}
void SeeThelist(double * list_of_values)
{
    int loopValue, lineLenght;
    lineLenght = 30 + (sizeOfTheArray - 5) * 4;
    for(loopValue = 0; loopValue < lineLenght; loopValue++)
        printf("-");
    printf("\n");
    printf(" Valores: ");
    for(loopValue = 0; loopValue < sizeOfTheArray; loopValue++)
        printf("%.1f ", list_of_values[loopValue]);
    printf("\n");
    for(loopValue = 0; loopValue < lineLenght; loopValue++)
        printf("-");
    printf("\n");
}
