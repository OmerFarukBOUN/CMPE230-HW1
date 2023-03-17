#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "standart.h"
#include "deneme.h"

char mainStatement[256];
int counter = 0;
char *deflastChar = 0;
bool8 error = FALSE;
HashMap variables;
HashMap operations;
HashMap functions;


int main() {
    variables = initializeHashMap();
    solveStatement(mainStatement);
    scanf("%s", mainStatement);
    printf("%s", mainStatement);
}

void solveStatement(char *statement) {
    char *assignedVar = getVar();
    int solution;
    dismissblank();
    if (*assignedVar == 0 || (mainStatement[counter] != '=')) {
        counter = 0;
        solution = solveExpr(deflastChar);
        if (error) {
            printf("%s", "Error!");
        } else {
            printf("%d", solution);
        }
    } else {
        counter++;
        dismissblank();
        solution = solveExpr(deflastChar);
        if (error) {
            printf("%s", "Error!");
        } else {
            add_new_element(&variables, assignedVar, solution);
        }
    }
    return;
}

int getString() {
    char lastforparanthesis[2] = {')', 0};
    char lastforfunc[2] = {',', 0};
    if (mainStatement[counter] == '(') {
        counter++;
        dismissblank();
        return solveExpr(lastforparanthesis);
    }
    if ((mainStatement[counter] >= 'A' && mainStatement[counter] <= 'Z') ||
        (mainStatement[counter] >= 'a' && mainStatement[counter] <= 'z')) {
        char *str = getVar();
        int right;
        int left;
        dismissblank();
        if (strcmp(str, "xor")==0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                left = solveExpr(lastforfunc);
                if (mainStatement[counter] != ',') {
                    error = TRUE;
                    return 0;
                }
                counter ++;
                right = solveExpr(lastforparanthesis);
                if (mainStatement[counter] != ')') {
                    error = TRUE;
                    return 0;
                }
                return left ^ right;
            }
        }
        if (strcmp(str, "ls")==0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                left = solveExpr(lastforfunc);
                counter ++;
                right = solveExpr(lastforparanthesis);
                return left << right;
            }
        }
        if (strcmp(str, "rs")==0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                left = solveExpr(lastforfunc);
                counter ++;
                right = solveExpr(lastforparanthesis);
                return left >> right;
            }
        }
        if (strcmp(str, "lr")==0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                left = solveExpr(lastforfunc);
                counter ++;
                right = solveExpr(lastforparanthesis);
                right %= 16;
                return (left << right) || (left >> (16-right));
            }
        }
        if (strcmp(str, "rr")==0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                left = solveExpr(lastforfunc);
                counter ++;
                right = solveExpr(lastforparanthesis);
                right %= 16;
                return (left >> right) || (left << (16-right));
            }
        }
        if (strcmp(str, "not")==0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                left = solveExpr(lastforfunc);
                return ~left;
            }
        }
        return getValue(&variables,str);
    }
    if ((mainStatement[counter] >= '0' && mainStatement[counter] <= '9')) {

    }
}

int solveExpr(char *last) {
    if (error) {

    }
    dismissblank();

    dismissblank();
}

int getOper() {

}

char *getVar() {
    char *assignedvar;
    for (counter = 0; counter < 256; counter++) {
        if ((mainStatement[counter] >= 'A' && mainStatement[counter] <= 'Z') ||
            (mainStatement[counter] >= 'a' && mainStatement[counter] <= 'z')) {
            assignedvar[counter] = mainStatement[counter];
        } else {
            assignedvar[counter] = 0;
            return assignedvar;
        }
    }
}

void dismissblank() {
    while (mainStatement[counter] == ' ') {
        counter++;
    }
}

int solveFunc() {

}