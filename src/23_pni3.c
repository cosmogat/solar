/* 30-06-2018 */
/* alex */
/* 23_pni3.c */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solar.h"

int main (int num_arg, char * vec_arg[]){
  int i, j, k, it, planetes, N, pop, pit, Neval = 0;
  char noms[MAX_PLA][MAX_CAD], f_ini[20];
  real masses[MAX_PLA], q[MAX_PLA][COMP], p[MAX_PLA][COMP];
  real H0, H, DH, Hemax = 0.0, gV;
  real h;
  int s = 3;
  int m = 6;
  real a[s + 1], ah[s + 1];
  real b[s], bh[s];
  real y[s], yh[s];
  real z[s], zh[s];
  double t0, t = 0.0;
  FILE * fit_pl[MAX_PLA + 1];

  carregar_configuracio(num_arg, vec_arg, &h, &N, &pop, &pit, f_ini);
  planetes = carregar_planetes(f_ini, masses, noms, q, p);
  H0 = energia(masses, q, p, planetes);
  obrir_fitxers(fit_pl, noms, f_ini, vec_arg[0], planetes);

  /* coeficients */
  a[0] = a[3] = 0.5600879810924619L;
  a[1] = a[2] = 0.5 - a[0];
  b[0] = b[2] = 1.5171479707207228L;
  b[1] = 1.0 - (2.0 * b[0]);
  y[0] = -1.6218101180868010L;
  y[1] = 0.0061709468110142L;
  y[2] = 0.8348493592472594L;
  y[3] = -0.0511253369989315L;
  y[4] = 0.5633782670698199L;
  y[5] = -0.5L;
  z[0] = -0.3346222298730800L;
  z[1] = 1.0975679907321640L;
  z[2] = -1.0380887460967830L;
  z[3] = 0.6234776317921379L;
  z[4] = -1.1027532063031910L;
  z[5] = -0.0141183222088869L;
  for (i = 0; i < s; i++) {
    ah[i] = a[i] * h;
    bh[i] = b[i] * h;
  }
  ah[s] = a[s] * h;
   for (i = 0; i < m; i++) {
    yh[i] = y[i] * h;
    zh[i] = z[i] * h;
  } 
  
  /* preprocessat */
  t0 = temps();
  for (k = 0; k < m; k++) {
    for (i = 1; i < planetes; i++)
      phiKepler(q[i], p[i], zh[k], masses[i]);      
    for (i = 1; i < planetes; i++) {
      for (j = 0; j < COMP; j++) {
	gV = egradV(masses, q, i, j, planetes);
	p[i][j] -= yh[k] * gV;
      }
    }
  }
  Neval += (m * (planetes - 1));
  t += temps() - t0;
  
  /* Mètode d'escissió */  
  for (it = 0; it < N; it++) {
    t0 = temps();
    /* Bucle per a k */
    for (k = 0; k < s; k++) {
      for (i = 1; i < planetes; i++)
	phiKepler(q[i], p[i], ah[k], masses[i]);      
      for (i = 1; i < planetes; i++) {
	for (j = 0; j < COMP; j++) {
	  gV = egradV(masses, q, i, j, planetes);
	  p[i][j] -= bh[k] * gV;
	}
      }
    }
    for (i = 1; i < planetes; i++)
      phiKepler(q[i], p[i], ah[s], masses[i]);
    
    Neval += (s * (planetes - 1));
    t += temps() - t0;
    /* imprimir */
    if ((it % pit) == 0) {
      /* postprocessat */
      t0 = temps();
      for (k = m - 1; k >= 0; k--) {     
	for (i = 1; i < planetes; i++) {
	  for (j = 0; j < COMP; j++) {
	    gV = egradV(masses, q, i, j, planetes);
	    p[i][j] -= -yh[k] * gV;
	  }
	}
	for (i = 1; i < planetes; i++)
	  phiKepler(q[i], p[i], -zh[k], masses[i]); 
      }
      Neval += (m * (planetes - 1));
      t += temps() - t0;
      /* escriptura */
      H = energia(masses, q, p, planetes);
      DH = ABSOLUT(H - H0);
      if (DH > Hemax)
	Hemax = DH;      
      escriure_fitxers(fit_pl, pop, ((real) it) * h, q, p, H0, H, planetes);
      /* preprocessat */
      t0 = temps();
      for (k = 0; k < m; k++) {
	for (i = 1; i < planetes; i++)
	  phiKepler(q[i], p[i], zh[k], masses[i]);
	for (i = 1; i < planetes; i++) {
	  for (j = 0; j < COMP; j++) {
	    gV = egradV(masses, q, i, j, planetes);
	    p[i][j] -= yh[k] * gV;
	  }
	}
      }
      Neval += (m * (planetes - 1));
      t += temps() - t0;
    }
  }
  tancar_fitxers(fit_pl, planetes);
  print_info(h, t, Neval, Hemax / H0);
  return 0;
}