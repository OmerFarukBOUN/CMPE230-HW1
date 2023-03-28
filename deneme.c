#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "hashmap.h"
#include "standart.h"
#include "deneme.h"

char mainStatement[257]; // The given statement
int counter = 0; // Iterator
char deflastChar[2] = {'%', 0}; // Our default last character
char lastforparanthesis[3] = {')', '%', 0}; // Last characters for expressions inside parenthesis
char lastforfunc[3] = {',', '%', 0}; // Last characters for expressions inside functions
bool8 error = FALSE; // Error checker flag
HashMap variables; // Hashmap of variables
char *functions[6] = {"xor", "ls", "rs", "lr", "rr", "not"}; // Array of function names


// This is our main function. It takes inputs until our program terminates
int main() {
    /// For debugging purposes
    // HashMap *vc = &variables;

    // Initialization of HashMap
    variables = initializeHashMap();

    /// F.d.p
    //add_new_element(&variables,"bruh", 5);
    //printf("%d", getValue(&variables, "bruh"));

    // Our main loop
    while (TRUE) {
        /// (We will turn 0 s to '\n' s later on)
        // Reading and solving the input
        printf("%s", "> ");
        if (fgets(mainStatement, 257, stdin) != NULL) {
            for (int i = 0; i < 257; i++) {
                if (mainStatement[i] == '\n') { mainStatement[i] = 0; }
            }
            //char *ha = mainStatement;
            solveStatement();
            counter = 0;
            error = FALSE;
        } else {
            // In order to free allocated memories
            deconstractor(&variables);
            return 0;
        }
    }
}

/*
 * Our BNF rules for creating statements is (shortly):
 * <statement> := <assignment> | <expression>
 * <assignment> := <var> = <expression>
 * This function checks if the statement is an assignment or expression and proceeds accordingly
*/
void solveStatement() {
    char *assignedVar = calloc(257, sizeof(char));
    getVar(assignedVar);
    long long int solution;
    dismissblank();
    // Checks if this is an expression or an assignment
    if (*assignedVar == '\0' || (mainStatement[counter] != '=')) {
        if (*assignedVar == '\0' && (mainStatement[counter] == '\0'||mainStatement[counter] == '%')) { return;}
        counter = 0;
        solution = solveExpr(deflastChar);
        if (error) {
            printf("%s\n", "Error!");
        } else {
            printf("%lld\n", solution);
        }
    }
    else {
        // Checks if the variable's name is a function name
        for (int i = 0; i < 6; i++) {
            if (chadstrcmp(functions[i], assignedVar) == 0) {
                printf("%s\n", "Error!");
                return;
            }
        }
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
 * Our BNF rules for creating strings is (shortly):
 * <string> := (<expression>) | <var> | func(<expression>, <expression>) | not(<expression>) | <num>
 * Starting from the counter, this function gets the nearest string, solves it and returns its value
*/
long long int getString() {
    dismissblank();
    // Checks if it is a (<expression>)
    if (mainStatement[counter] == '(') {
        counter++;
        dismissblank();
        long long int solution = solveExpr(lastforparanthesis);
        if (mainStatement[counter] != ')') {
            error = TRUE;
            return 0;
        }
        counter++;
        return solution;
    }
    // Checks if it is a <var> | func(<expression>, <expression>) | not(<expression>)
    if ((mainStatement[counter] >= 'A' && mainStatement[counter] <= 'Z') ||
        (mainStatement[counter] >= 'a' && mainStatement[counter] <= 'z')) {
        char str[257];
        getVar(str);
        long long int *right;
        long long int *left;
        dismissblank();
        // Checks if it is a func(<expression>, <expression>) | not(<expression>)
        if (chadstrcmp(str, "xor") == 0) {
            initialize_sides(left, right);
            if (error) { return 0; }
            return *left ^ *right;
        }
        // Checks if it is a ls(<expression>, <expression>)
        if (chadstrcmp(str, "ls") == 0) {
            initialize_sides(left, right);
            if (error) { return 0; }
            return *left << *right;
        }
        // Checks if it is a rs(<expression>, <expression>)
        if (chadstrcmp(str, "rs") == 0) {
            initialize_sides(left, right);
            if (error) { return 0; }
            return *left >> *right;
        }
        // Checks if it is a lr(<expression>, <expression>)
        if (chadstrcmp(str, "lr") == 0) {
            initialize_sides(left, right);
            if (error) { return 0; }
            *right %= 64;
            return (*left << *right) | (*left >> (64 - *right));
        }
        // Checks if it is a rr(<expression>, <expression>)
        if (chadstrcmp(str, "rr") == 0) {
            initialize_sides(left, right);
            *right %= 64;
            if (error) { return 0; }
            return (*left >> *right) | (*left << (64 - *right));
        }
        // Checks if it is a not(<expression>)
        if (chadstrcmp(str, "not") == 0) {
            if (mainStatement[counter] == '(') {
                counter++;
                dismissblank();
                *left = solveExpr(lastforparanthesis);
                if (mainStatement[counter] != ')') {
                    error = TRUE;
                    return 0;
                }
                counter++;
                return ~*left;
            } else {
                error = TRUE;
                return 0;
            }
        }
        return getValue(&variables, str);
    }
    // Checks if it is a <num>
    if ((mainStatement[counter] >= '0' && mainStatement[counter] <= '9')) {
        long long int solution = 0;
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
 * Solves expression starting from the counter
 * (Stays in the last character)
 */
long long int solveExpr(char *last) {
    if (error) {
        return 0;
    }
    dismissblank();
    long long int left = getString();
    dismissblank();
    char operator1 = mainStatement[counter];
    return solveOperation(left, operator1, last);
}

// Gets operation (stays in the current operator)
// Returns to precedence of the given operator
long long int getOper(char op) {
    dismissblank();
    if (op == '|') { return or; }
    if (op == '&') { return and; }
    if (op == '+') { return sum; }
    if (op == '-') { return min; }
    if (op == '*') { return mul; }
    return notoperator;
}

// Gets the nearest variable from the counter
void getVar(char *assignedvar) {
    dismissblank();
    for (int i = 0; i < 257; i++) {
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

// Dismisses all blanks until it hits something else
void dismissblank() {
    while (isspace(mainStatement[counter])) {
        counter++;
    }
}

// Solves operations (from left to right) in a recursive manner
long long int solveOperation(long long int left, char op, char *last) {
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
    long long int right = getString();
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

void initialize_sides(long long int *left, long long int *right) {
    if (mainStatement[counter] == '(') {
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
        counter++;
    } else {
        error = TRUE;
        return;
    }
}
