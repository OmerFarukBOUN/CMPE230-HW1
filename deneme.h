#pragma once

#include <string.h>
#include "standart.h"

void solveStatement(char *);
int getString();
int solveExpr(char *);
int getOper();
char* getVar();
void dismissblank();
int checkiffunc(char *);

enum functions {
    notfunc,
    xor,
    ls,
    rs,
    lr,
    rr,
    not,
};