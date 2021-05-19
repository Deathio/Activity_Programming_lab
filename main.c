#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Custom Library
#include "myLibrary.h"

int sizeOfTheArray, limitOfTheCondition = 4, okayNumbers = 0, okayStrings = 0, maxSize = 55, sizeAlpha = 26, isEncrpyted = 0;
double average;
char encryptChars[26] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '!', '@', '#',
                         '$', '%', ':', '&', '*', '(', ')', '-', '+', '<', '>', '/', ','
                        };
char AlphabetChar[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                         'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'Y', 'Z',
                        };

// number functions
void DefineLenght(double **);
void DigitValues(double *);
void ReturnPosition(double *);
void RunMultiplier(double *);
void RunAverageWeighted(double *);
void SeeThelist(double *);
// string functions
void DigitStrings(char **, int *);
void SeeTheString(char *, int);
void Encrypt(char **, int, int*);
void Decrypt(char **, int, int*);

void Error(int command);

int main()
{
    char * stringRead;
    double * numberList = 0;
    int command = 0, strLenght = 0, multiplyEncript = 0;

    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    stringRead = calloc(maxSize, sizeof(char));
    numberList = calloc(sizeOfTheArray, sizeof(double));

    while(1)
    {
        command = 0;
        printf("%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
               "MENU: \n",
               "N�meros:\n",
               " 1. Informar a quantidade de n�meros a tratar\n",
               " 2. Digitar os n�meros\n",
               " 3. Informar o menor n�mero\n",
               " 4. Informar o maior n�mero\n",
               " 5. Retornar o n-�simo n�mero da lista\n",
               " 6. Calcular a soma dos n�meros\n",
               " 7. Calcular o produto dos n�meros\n",
               " 8. Multiplicar todos os n�meros por um valor\n",
               " 9. Calcular a m�dia aritm�tica dos n�meros\n",
               " 10. Informar quantos n�meros est�o acima da m�dia aritm�tica\n",
               " 11. Calcular a m�dia ponderada dos n�meros\n",
               " 12. Ordenar os n�meros em ordem crescente\n",
               " 13. Ordenar os n�meros em ordem decrescente\n",
               "Strings:\n",
               " 14. Ler string\n",
               " 15. Mostrar string lida e o seu tamanho\n",
               " 16. Criptografar a string\n",
               " 17. Descriptografar a string\n",
               " 18. Terminar a execu��o\n");
        if(sizeOfTheArray > limitOfTheCondition && okayNumbers)
            SeeThelist(numberList);
        printf("Comando: ");
        while(!scanf(" %d", &command))
        {
            printf("\n Lembre-se de que os comandos s� est�o em n�meros inteiros\n\a");
            fflush(stdin);
            printf("\nComando: ");
        }
        printf("\n");

        if(command == 1)
            DefineLenght(&numberList);
        else if(command == 2)
            DigitValues(numberList);

        else if(sizeOfTheArray > limitOfTheCondition && okayNumbers && command < 14)
        {
            if(command == 3)
                printf("O menor n�mero da lista � o valor: %.1f\n\n", ExtremeValue(numberList, sizeOfTheArray, -1));
            else if(command == 4)
                printf("O maior n�mero da lista � o valor: %.1f\n\n", ExtremeValue(numberList, sizeOfTheArray, 1));
            else if(command == 5)
                ReturnPosition(numberList);
            else if(command == 6)
                printf("A soma de todos os n�meros � igual ao n�mero: %.1f\n\n", ListSum(numberList, sizeOfTheArray));
            else if(command == 7)
                printf("O produto de todos os n�meros � igual ao n�mero: %.1f\n\n", ListProduct(numberList, sizeOfTheArray));
            else if(command == 8)
                RunMultiplier(numberList);
            else if(command == 9)
                printf("A m�dia de todos os n�meros da lista � igual ao n�mero: %.1f\n\n", average);
            else if(command == 10)
                printf("A quantidade de n�meros acima da m�dia �: %d\n\n", AverageForCounter(numberList, average, sizeOfTheArray));
            else if(command == 11)
                RunAverageWeighted(numberList);
            else if(command == 12)
                SortList(numberList, sizeOfTheArray, 1);
            else if(command == 13)
                SortList(numberList, sizeOfTheArray, -1);
        }
        else if(command == 14)
            DigitStrings(&stringRead, &strLenght);
        else if(okayStrings)
        {
            if(command == 15)
                SeeTheString(stringRead, strLenght);
            else if(command == 16)
                Encrypt(&stringRead, strLenght, &multiplyEncript);
            else if(command == 17 && isEncrpyted)
                Decrypt(&stringRead, strLenght, &multiplyEncript);
            else
                printf("N�o pode decriptar um c�digo que n�o foi encriptado\n\n");
        }
        else if(command == 18)
            return 0;
        else
            Error(command);
    }
}
void DefineLenght(double ** numberList)
{
    sizeOfTheArray = 0;

    while(sizeOfTheArray < 5 || sizeOfTheArray > 15)
    {
        printf("Aqui voc� ir� definir o tamanho da lista, lembre-se ela tem que estar entre 5 e 15\n");

        printf("Defina o tamanho da lista: ");
        if(scanf(" %d", &sizeOfTheArray) != 1)
            printf("\a\nLembrando somente tipos n�mericos!\n");
        printf("\n");
        fflush(stdin);
    }

    *numberList = realloc(*numberList, sizeof(double) * sizeOfTheArray);
    okayNumbers = 0;
}
void DigitValues(double * numberList)
{
    int loopValue = 0;

    if(sizeOfTheArray > limitOfTheCondition)
    {
        printf("Agora digite os valores reais que voc� deseja colocar em cada posi��o, por�m lembre-se \nos n�meros tem que estar entre -100 e 500, n�o podem ser multiplos de 8, diferentes de 0 e que para colocar os decimais use a ,\n");
        while(loopValue < sizeOfTheArray)
        {
            int isNum = 0;
            double inputValue = 0;
            printf("Digite o valor da posi��o %d da lista: ", loopValue + 1);

            if(scanf(" %lf", &inputValue))
                isNum = 1;

            if(inputValue >= -100 && inputValue <= 500 && isNum && fmod(inputValue, 8) != 0)
            {
                numberList[loopValue] = inputValue;
                loopValue++;
            }
            else
            {
                printf("\a\nLembre-se dos tipos n�mericos, diferentes de 0, diferentes dos multiplos de 8 e estando eles dentro do conjunto\n");
            }
            fflush(stdin);
        }
        okayNumbers = 1;
        average = ListAverage(numberList, sizeOfTheArray);
        printf("\n");
    }
    else
    {
        Error(2);
    }
}
void ReturnPosition(double * numberList)
{
    int position = -1, isNum = 0;

    while(position <= 0 || position > sizeOfTheArray || !isNum)
    {
        isNum = 0;
        printf("Diga a posi��o do n�mero que deseja retornar (ele tem que estar entre 1 e %d)\n", sizeOfTheArray);

        printf("Posi��o: ");

        if(scanf(" %d", &position))
            isNum = 1;
        else
            printf("\a\nLembrando somente tipos inteiros dentro do conjunto demonstrado!\n");

        printf("\n");
        fflush(stdin);
    }
    double value = numberList[position - 1];
    printf("O n�mero nessa posi��o � o %.1f\n\n", value);

}
void RunMultiplier(double * numberList)
{
    double value = 0;
    int isNum = 0;

    do{
        isNum = 0;
        printf("%s%s",
               "Digite o n�mero que vai ser multiplicado pela lista de valores (Lembre-se ele tem de ser diferente de 0)\n",
               "N�mero: ");

        if(scanf(" %lf", &value))
            isNum = 1;
        else
            printf("\a\nLembrando somente tipos n�mericos!\n");

        printf("\n");
        fflush(stdin);

    }while(!value || !isNum);

    MultiplyTheList(numberList, value, sizeOfTheArray);
    average = ListAverage(numberList, sizeOfTheArray);
}
void RunAverageWeighted(double * numberList)
{
    double * weightList;
    int loopValue = 0, isNum = 0;

    weightList = malloc(sizeof(double) * sizeOfTheArray);

    printf("Para saber a m�dia ponderada precisamos dos pesos de cada valor(Somente tipos num�ricos diferentes de 0)\n");

    while(loopValue < sizeOfTheArray || isNum == 0)
    {

        printf("Digite o peso da posi��o %d da lista: ", loopValue);

        if(scanf(" %lf", &weightList[loopValue]) && weightList[loopValue] != 0)
        {
            isNum = 1;
            loopValue++;
        }
        else
            printf("\a\nLembrando somente tipos n�mericos e sendo eles diferentes de 0!\n");

        fflush(stdin);
    }

    printf("\nA m�dia ponderada de todos os n�meros da lista � igual ao n�mero: %.1f\n\n", ListAverageWeighted(numberList, weightList, sizeOfTheArray));
}
void SeeThelist(double * list_of_values)
{
    int loopValue, lineLenght;
    lineLenght = 30 + (sizeOfTheArray - 5) * 5;
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
void Error(int command)
{
    if(command < 14)
    {
        if(sizeOfTheArray > limitOfTheCondition && !okayNumbers)
            printf("Digite os valores da nova lista criada\n\a");
        else if((sizeOfTheArray < limitOfTheCondition && !okayNumbers) || (sizeOfTheArray < limitOfTheCondition && okayNumbers))
            printf("Digite o tamanho da nova lista\n\a");
    }
    else if(command > 13 && command < 18 && !okayStrings)
        printf("Digite a frase/palavra primeiro antes de executar os demais comandos\n\a");
    else
        printf("O comando digitado � inv�lido\n\a");



    printf("\n");
}
void DigitStrings(char ** stringIn, int * newLen)
{
    if(okayStrings == 1)
        *stringIn = (char *) realloc(*stringIn, maxSize * sizeof(char));

    printf("Digite a frase / palavra para o programa: ");

    okayStrings = 1;

    do
    {
        fflush(stdin);
        fgets(*stringIn, maxSize, stdin);
        *newLen = strlen(*stringIn) - 1;

    }
    while(*newLen > 50 || *stringIn[0] == '\n' || AlphaSpaceCheck(*stringIn, *newLen));

    while((*stringIn)[*newLen - 1] == ' ') *newLen -= 1;
    (*stringIn)[*newLen] = '\0';

    *stringIn = (char *) realloc(*stringIn, *newLen * sizeof(char));
    printf("\n");
}
void SeeTheString(char * stringIn, int strLenght)
{
    printf("Frase / Palavra : %s\n", stringIn);
    printf("N�mero de letras: %d\n\n", strLenght);
}
void Encrypt(char ** stringIn, int strLenght, int * multiplyEncript)
{
    int stringCheck, encryptCheck, encryptedPosition = 0;

    isEncrpyted = 1;

    printf("Digite um numero para encrip�ao: ");
    fflush(stdin);
    while(!scanf("%d", &(*multiplyEncript)))
    {
        printf("Digite um n�mero v�lido!\n");
        printf("Digite um numero para encrip��o: ");
        fflush(stdin);
    }
    printf("\n");
    for(stringCheck = 0; stringCheck < strLenght; stringCheck++)
    {
        (*stringIn)[stringCheck] = toupper((*stringIn)[stringCheck]);

        for(encryptCheck = 0; encryptCheck < sizeAlpha; encryptCheck++)
        {
            if((*stringIn)[stringCheck] == AlphabetChar[encryptCheck])
            {
                encryptedPosition = encryptCheck + (*multiplyEncript - 1);

                while(encryptedPosition >= sizeAlpha) encryptedPosition -= sizeAlpha;

                (*stringIn)[stringCheck] = encryptChars[encryptedPosition];
                break;
            }
        }
    }
    printf("Frase/Palavra encriptada\n\n");
}
void Decrypt(char ** stringIn, int strLenght, int * multiplyEncript)
{
    int stringCheck, decryptCheck, encryptedPosition = 0;

    for(stringCheck = 0; stringCheck < strLenght; stringCheck++)
    {
        for(decryptCheck = 0; decryptCheck < sizeAlpha; decryptCheck++)
        {
            if((*stringIn)[stringCheck] == encryptChars[decryptCheck])
            {
                encryptedPosition = decryptCheck - (*multiplyEncript - 1);

                while(encryptedPosition < 0) encryptedPosition += sizeAlpha;

                (*stringIn)[stringCheck] = AlphabetChar[encryptedPosition];
                break;
            }
        }
    }
    printf("Frase/Palavra decriptada\n\n");
}
