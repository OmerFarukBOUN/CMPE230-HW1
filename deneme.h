#pragma once

#include <string.h>
#include "standart.h"

#define min 3

void solveStatement(char *);
int getString();
int solveExpr(char *);
int getOper(char);
void getVar(char *);
void dismissblank();
int checkiffunc(char *);
int solveOperation(int, char, char*);

//enum functions {
//    notfunc,
//    xor,
//    ls,
//    rs,
//    lr,
//    rr,
//    not,
//};

enum operator {
    notoperator,
    or,
    and,
    sum,
    mul,
};

