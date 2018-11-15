/* 08-11-2018 */
/* alex */
/* metodes.h */
#ifndef _METODES_H
#define _METODES_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <quadmath.h>
#include "tipus.h"
#undef COMP
#undef MAX_PAR
#define COMP 3
#define MAX_PAR 20

/* variables globals per a potencials genèrics */
real (*gradV)(real m[MAX_PAR], real q[MAX_PAR][COMP], int i, int j, int npl);
real (*egradV)(real m[MAX_PAR], real q[MAX_PAR][COMP], int i, int j, int npl);
real (*deriv2q)(real m[MAX_PAR], real q[MAX_PAR][COMP], int i, int j, int npl);
void (*gradVmod)(real masses[MAX_PAR], real q[MAX_PAR][COMP], int i, int j, int npl, real * gV, real * gV2);
void (*phi0)(real q[COMP], real p[COMP], real h, real m);
real (*energia)(real masses[MAX_PAR], real q[MAX_PAR][COMP], real p[MAX_PAR][COMP], int npl);

/* mètodes */
void phi_T(real m[MAX_PAR], real q[MAX_PAR][COMP], real p[MAX_PAR][COMP], int npl, real t);
void phi_V(real m[MAX_PAR], real q[MAX_PAR][COMP], real p[MAX_PAR][COMP], int npl, real t);
void phi_Vm(real m[MAX_PAR], real q[MAX_PAR][COMP], real v[MAX_PAR][COMP], int npl, real t1, real t2);
void phi_Tv(real m[MAX_PAR], real q[MAX_PAR][COMP], real v[MAX_PAR][COMP], int npl, real t);
void phi_Vv(real m[MAX_PAR], real q[MAX_PAR][COMP], real v[MAX_PAR][COMP], int npl, real t);
void phi_simpTV(real m[MAX_PAR], real q[MAX_PAR][COMP], real p[MAX_PAR][COMP], int npl, real t);
void phi_simpVT(real m[MAX_PAR], real q[MAX_PAR][COMP], real p[MAX_PAR][COMP], int npl, real t);
void phi_stor(real m[MAX_PAR], real q[MAX_PAR][COMP], real p[MAX_PAR][COMP], int npl, real t);
void phi_storAdj(real m[MAX_PAR], real q[MAX_PAR][COMP], real p[MAX_PAR][COMP], int npl, real t);
void phi_storMod(real m[MAX_PAR], real q[MAX_PAR][COMP], real p[MAX_PAR][COMP], int npl, real t);
void phi_H0(real m[MAX_PAR], real q[MAX_PAR][COMP], real p[MAX_PAR][COMP], int npl, real t);
void phi_eV1(real m[MAX_PAR], real q[MAX_PAR][COMP], real p[MAX_PAR][COMP], int npl, real t);

/* funcions auxiliars dels mètodes */
void copiar(real orig[MAX_PAR][COMP], real copi[MAX_PAR][COMP], int npl);
void p2v(real m[MAX_PAR], real p[MAX_PAR][COMP], real v[MAX_PAR][COMP], int npl);
void v2p(real m[MAX_PAR], real p[MAX_PAR][COMP], real v[MAX_PAR][COMP], int npl);
real dif_v(real v1[COMP], real v2[COMP]);
real dot(real v1[COMP], real v2[COMP]);
real norm(real v[COMP]);

#endif
