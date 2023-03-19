#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "standart.h"
#include "deneme.h"

char mainStatement[256]; // the given statement
int counter = 0; // iterator
char *deflastChar = 0; // default last character
bool8 error = FALSE; // were there any errors
HashMap variables; // hashmap of variables
HashMap operations;
HashMap functions;


int main() {
    variables = initializeHashMap();
    scanf("%s", mainStatement);
    //solveStatement(mainStatement);
    printf("%d", getString());
}

/*
 * <statement> := <assignment> | <expression>
 * <assignment> := <var> = <expression>
 * this function checks if the statement is an assignment or expression and proceeds accordingly.
*/
void solveStatement(char *statement) {
    char *assignedVar = getVar();
    int solution;
    dismissblank();
    // checks if this is an assignment
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

/*
 * <string> := (<expression>) | <var> | func(<expression>, <expression>) | not(<expression>) | <num>
 * starting from the counter, this function gets the nearest string, solves it and returns its value
*/
int getString() {
    char lastforparanthesis[2] = {')', 0};
    char lastforfunc[2] = {',', 0};
    // checks if it is a (<expression>)
    if (mainStatement[counter] == '(') {
        counter++;
        dismissblank();
        int solution = solveExpr(lastforparanthesis);
        if (mainStatement[counter] != ')') {
            error = TRUE;
            return 0;
        }
        counter++;
        return solution;
    }
    // checks if it is a <var> | func(<expression>, <expression>) | not(<expression>)
    if ((mainStatement[counter] >= 'A' && mainStatement[counter] <= 'Z') ||
        (mainStatement[counter] >= 'a' && mainStatement[counter] <= 'z')) {
        char *str = getVar();
        int right;
        int left;
        dismissblank();
        // checks if it is a func(<expression>, <expression>) | not(<expression>)
        if (strcmp(str, "xor") == 0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                left = solveExpr(lastforfunc);
                if (mainStatement[counter] != ',') {
                    error = TRUE;
                    return 0;
                }
                counter++;
                right = solveExpr(lastforparanthesis);
                if (mainStatement[counter] != ')') {
                    error = TRUE;
                    return 0;
                }
                return left ^ right;
            }
        }
        if (strcmp(str, "ls") == 0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                left = solveExpr(lastforfunc);
                if (mainStatement[counter] != ',') {
                    error = TRUE;
                    return 0;
                }
                counter++;
                right = solveExpr(lastforparanthesis);
                if (mainStatement[counter] != ')') {
                    error = TRUE;
                    return 0;
                }
                return left << right;
            }
        }
        if (strcmp(str, "rs") == 0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                left = solveExpr(lastforfunc);
                if (mainStatement[counter] != ',') {
                    error = TRUE;
                    return 0;
                }
                counter++;
                right = solveExpr(lastforparanthesis);
                if (mainStatement[counter] != ')') {
                    error = TRUE;
                    return 0;
                }
                return left >> right;
            }
        }
        if (strcmp(str, "lr") == 0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                left = solveExpr(lastforfunc);
                if (mainStatement[counter] != ',') {
                    error = TRUE;
                    return 0;
                }
                counter++;
                right = solveExpr(lastforparanthesis);
                if (mainStatement[counter] != ')') {
                    error = TRUE;
                    return 0;
                }
                right %= 16;
                return (left << right) || (left >> (16 - right));
            }
        }
        if (strcmp(str, "rr") == 0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                left = solveExpr(lastforfunc);
                if (mainStatement[counter] != ',') {
                    error = TRUE;
                    return 0;
                }
                counter++;
                right = solveExpr(lastforparanthesis);
                if (mainStatement[counter] != ')') {
                    error = TRUE;
                    return 0;
                }
                counter++;
                right %= 16;
                return (left >> right) || (left << (16 - right));
            }
        }
        // checks if it is a not(<expression>)
        if (strcmp(str, "not") == 0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                left = solveExpr(lastforfunc);
                if (mainStatement[counter] != ')') {
                    error = TRUE;
                    return 0;
                }
                return ~left;
            }
        }
        return getValue(&variables, str);
    }
    // checks if it is a <num>
    if ((mainStatement[counter] >= '0' && mainStatement[counter] <= '9')) {
        int solution = 0;
        while ((mainStatement[counter] >= '0' && mainStatement[counter] <= '9')) {
            solution = 10*solution + (mainStatement[counter]-'0');
            counter++;
        }
        return solution;
    }
}


/*
 * solves expression starting from the counter
 */
int solveExpr(char *last) {
    if (error) {

    }
    dismissblank();

    dismissblank();
    return 5;
}

// gets ooperation
int getOper() {

}

// gets the nearest string from the counter
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

//dismisses all blanks until it hits something else
void dismissblank() {
    while (mainStatement[counter] == ' ') {
        counter++;
    }
}

int solveFunc() {

}

void darlandum(int* left, int* right) {
    counter++;
    dismissblank();
    *left = solveExpr(lastforfunc);
    if (mainStatement[counter] != ',') {
        error = TRUE;
        return;
    }
    counter++;
    *right = solveExpr(lastforparanthesis);
    if (mainStatement[counter] != ')') {
        error = TRUE;
        return;
    }
}