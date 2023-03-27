#pragma once

#include <string.h>
#include "standart.h"

void solveStatement();
long long int getString();
long long int solveExpr(char *);
long long int getOper(char);
void getVar(char *);
void dismissblank();
long long int solveOperation(long long int, char, char*);
void initialize_sides(long long int*, long long int*);


enum operator {
    notoperator,
    or,
    and,
    sum,
    mul,
};

#define min sum
