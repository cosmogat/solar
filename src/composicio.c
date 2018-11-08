/* 07-11-2018 */
/* alex */
/* composicio.c */
#include <stdio.h>
#include <stdlib.h>
#include "metodes.h"
#include "solar.h"

int main (int num_arg, char * vec_arg[]) {
  int i, it, planetes, N, pop, pit, Neval = 0;
  char noms[MAX_PLA][MAX_CAD], f_ini[20], f_coef[20], t_metode[20];
  real masses[MAX_PLA], q[MAX_PLA][COMP], p[MAX_PLA][COMP];
  real a[NUM_MAX_COEF], b[NUM_MAX_COEF], y[NUM_MAX_COEF], z[NUM_MAX_COEF];
  real ah[NUM_MAX_COEF], bh[NUM_MAX_COEF], yh[NUM_MAX_COEF], zh[NUM_MAX_COEF];
  int tam_a = 0, tam_b = 0, tam_y = 0, tam_z = 0;
  real H0, H, DH, Hemax = 0.0;
  real h;
  int s;
  double t0, t = 0.0;
  FILE * fit_pl[MAX_PLA + 1];

  /* carregar_configuracio */
  carregar_configuracio(num_arg, vec_arg, &h, &N, &pop, &pit, f_ini, t_metode, f_coef);
  planetes = carregar_planetes(f_ini, masses, noms, q, p);
  H0 = energia(masses, q, p, planetes);
  obrir_fitxers(fit_pl, noms, f_ini, vec_arg[0], planetes);

  /* coeficients */
  lectura_coef(f_coef, a, b, y, z, &tam_a, &tam_b, &tam_y, &tam_z);
  s = tam_a;
  for (i = 0; i < NUM_MAX_COEF; i++) {
    ah[i] = a[i] * h;
    bh[i] = b[i] * h;
    yh[i] = y[i] * h;
    zh[i] = z[i] * h;
  }
  
  /* bucle principal */  
  for (it = 0; it < N; it++) {
    t0 = temps();

    /* composició del mètode */
    if (strcmp(t_metode, "ss") == 0) {
      for (i = 0; i < s; i++)
	phi_storAdj(masses, q, p, planetes, ah[i]);
      Neval += (s * (planetes - 1));
    }
    else if (strcmp(t_metode, "sb") == 0) {
      for (i = 0; i < s; i++) {
	phi_V(masses, q, p, planetes, bh[i]);
	phi_T(masses, q, p, planetes, ah[i]);
      }
      phi_V(masses, q, p, planetes, bh[s]);
      Neval += ((s + 1) * (planetes - 1));
    }
    else if (strcmp(t_metode, "sa") == 0) {
      for (i = 0; i < s; i++) {
	phi_T(masses, q, p, planetes, ah[i]);
	phi_V(masses, q, p, planetes, bh[i]);
      }
      phi_T(masses, q, p, planetes, ah[s]);
      Neval += (s * (planetes - 1));
    }
    else if (strcmp(t_metode, "nb") == 0) {}
    else if (strcmp(t_metode, "na") == 0) {}
    else if (strcmp(t_metode, "nia") == 0) {}
    else {
      fputs("El mètode especificat no existeix\n", stderr);
      exit(1);
    }
      
    t += temps() - t0;
    H = energia(masses, q, p, planetes);
    DH = ABSOLUT(H - H0);
    if (DH > Hemax)
      Hemax = DH;
    if ((it % pit) == 0)
      escriure_fitxers(fit_pl, pop, ((real) it) * h, q, p, H0, H, planetes);
  }
  tancar_fitxers(fit_pl, planetes);
  print_info(h, t, Neval, Hemax / H0);
  return 0;
}
