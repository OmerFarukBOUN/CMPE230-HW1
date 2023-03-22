#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "standart.h"
#include "deneme.h"

char mainStatement[256]; // the given statement
int counter = 0; // iterator
char deflastChar[2] = {'%', 0}; // default last character
bool8 error = FALSE; // were there any errors
HashMap variables; // hashmap of variables
//HashMap operations;
//HashMap functions;
//char operatorStack[256];
//int OSC = 0;
//int noStack[256];
//int NSC = 0;


int main() {
    HashMap *vc = &variables;
    variables = initializeHashMap();
//    add_new_element(&variables,"bruh", 5);
//    printf("%d", getValue(&variables, "bruh"));
    while (TRUE) {
        if (fgets(mainStatement, 256, stdin) != NULL) {
            for(int i = 0; i<256;i++) {
                if (mainStatement[i] == '\n') {mainStatement[i] = 0;}
            }
            char *ha = mainStatement;
            solveStatement(mainStatement);
            counter = 0;
            error = FALSE;
        } else {
            deconstractor(&variables);
            return 0;
        }
    }

//    int flag = 0;
//    while (TRUE) {
//        flag = scanf("%256[^\n]", mainStatement);
//        if (flag == EOF) { return 0; }
//        solveStatement(mainStatement);
//    }
    //printf("%d", getString());
}

/*
 * <statement> := <assignment> | <expression>
 * <assignment> := <var> = <expression>
 * this function checks if the statement is an assignment or expression and proceeds accordingly.
*/
void solveStatement(char *statement) {
    char *assignedVar = calloc(256, sizeof(char));
    getVar(assignedVar);
    int solution;
    dismissblank();
    // checks if this is an assignment
    if (*assignedVar == '\0' || (mainStatement[counter] != '=')) {
        counter = 0;
        solution = solveExpr(deflastChar);
        if (error) {
            printf("%s\n", "Error!");
        } else {
            printf("%d\n", solution);
        }
    } else {
        counter++;
        dismissblank();
        solution = solveExpr(deflastChar);
        if (error) {
            printf("%s\n", "Error!");
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
    char lastforparanthesis[3] = {')', '%', 0};
    char lastforfunc[3] = {',', '%', 0};
    dismissblank();
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
        char str[256];
        getVar(str);
        int right;
        int left;
        dismissblank();
        // checks if it is a func(<expression>, <expression>) | not(<expression>)
        if (chadstrcmp(str, "xor") == 0) {
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
                return left ^ right;
            } else {
                error = TRUE;
                return 0;
            }
        }
        if (chadstrcmp(str, "ls") == 0) {
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
                return left << right;
            } else {
                error = TRUE;
                return 0;
            }
        }
        if (chadstrcmp(str, "rs") == 0) {
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
                return left >> right;
            } else {
                error = TRUE;
                return 0;
            }
        }
        if (chadstrcmp(str, "lr") == 0) {
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
                counter++;
                return (left << right) | (left >> (16 - right));
            } else {
                error = TRUE;
                return 0;
            }
        }
        if (chadstrcmp(str, "rr") == 0) {
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
                return (left >> right) | (left << (16 - right));
            } else {
                error = TRUE;
                return 0;
            }
        }
        // checks if it is a not(<expression>)
        if (chadstrcmp(str, "not") == 0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                left = solveExpr(lastforparanthesis);
                if (mainStatement[counter] != ')') {
                    error = TRUE;
                    return 0;
                }
                counter++;
                return ~left;
            } else {
                error = TRUE;
                return 0;
            }
        }
        return getValue(&variables, str);
    }
    // checks if it is a <num>
    if ((mainStatement[counter] >= '0' && mainStatement[counter] <= '9')) {
        int solution = 0;
        while ((mainStatement[counter] >= '0' && mainStatement[counter] <= '9')) {
            solution = 10 * solution + (mainStatement[counter] - '0');
            counter++;
        }
        return solution;
    }
    error = TRUE;
    return 0;
}


/*
 * solves expression starting from the counter
 * stays in the last character
 */
int solveExpr(char *last) {
    if (error) {
        return 0;
    }
    dismissblank();
    int left = getString();
    dismissblank();
    char operator1 = mainStatement[counter];
    return solveOperation(left, operator1, last);
}

// gets operation
// stays in the current operator

int getOper(char op) {
    dismissblank();
    if (op == '|') { return or; }
    if (op == '&') { return and; }
    if (op == '+') { return sum; }
    if (op == '-') { return min; }
    if (op == '*') { return mul; }
    return notoperator;
}

// gets the nearest string from the counter
void getVar(char *assignedvar) {
    dismissblank();
    for (int i = 0; i < 256; i++) {
        if ((mainStatement[counter] >= 'A' && mainStatement[counter] <= 'Z') ||
            (mainStatement[counter] >= 'a' && mainStatement[counter] <= 'z')) {
            assignedvar[i] = mainStatement[counter];
            counter++;
        } else {
            assignedvar[i] = 0;
            dismissblank();
            return;
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

//gets counter left in operator, leaves counter in second operator
int solveOperation(int left, char op, char *last) {
    int i = 0;
    if (op == 0) {
        return left;
    }
    while (last[i] != 0) {
        if (op == last[i]) {
            return left;
        }
        i++;
    }
    counter++;
    int right = getString();
    dismissblank();
    char secondop = mainStatement[counter];
    if (getOper(op) >= getOper(secondop)) {
        if (op == '|') { return solveOperation(left | right, secondop, last); }
        if (op == '&') { return solveOperation(left & right, secondop, last); }
        if (op == '-') { return solveOperation(left - right, secondop, last); }
        if (op == '+') { return solveOperation(left + right, secondop, last); }
        if (op == '*') { return solveOperation(left * right, secondop, last); }
    } else {
        if (op == '|') { return left | solveOperation(right, secondop, last); }
        if (op == '&') { return left & solveOperation(right, secondop, last); }
        if (op == '-') { return left - solveOperation(right, secondop, last); }
        if (op == '+') { return left + solveOperation(right, secondop, last); }
        if (op == '*') { return left * solveOperation(right, secondop, last); }
    }
    error = TRUE;
    return 0;
}

//void darlandum(int* left, int* right) {
//    counter++;
//    dismissblank();
//    *left = solveExpr(lastforfunc);
//    if (mainStatement[counter] != ',') {
//        error = TRUE;
//        return;
//    }
//    counter++;
//    *right = solveExpr(lastforparanthesis);
//    if (mainStatement[counter] != ')') {
//        error = TRUE;
//        return;
//    }
//}

//void add_new_operator(char op) {
//    operatorStack[OSC] = op;
//    OSC++;
//}
//
//int pop_operatorStack() {
//    if (OSC == 0) {
//        error = TRUE;
//        return 0;
//    }
//    OSC--;
//    return operatorStack[OSC];
//}
//
//int seek_operatorStack() {
//    if (OSC == 0) {
//        error = TRUE;
//        return 0;
//    }
//    return operatorStack[OSC - 1];
//}
//
//void add_new_int(int num) {
//    noStack[NSC] = num;
//    NSC++;
//}
//
//int pop_intStack() {
//    if (NSC == 0) {
//        error = TRUE;
//        return 0;
//    }
//    NSC--;
//    return noStack[NSC];
//}
//
//int seek_intStack() {
//    if (NSC == 0) {
//        error = TRUE;
//        return 0;
//    }
//    return noStack[NSC - 1];
//}