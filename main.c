/* 
 * simple lennard-jones potential MD code with velocity verlet.
 * units: Length=Angstrom, Mass=amu; Energy=kcal
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <ljmd.h>

int main(int argc, char **argv) 
{
  double t_start = cclock();
  int nprint;
  char restfile[BLEN], trajfile[BLEN], ergfile[BLEN], line[BLEN];
  FILE *traj,*erg, *time;
  mdsys_t sys;
  
  /* sets the system usyn parameters in stdin */
  set_mdsys(&sys,restfile,trajfile,ergfile,line,&nprint);

  /* allocate memory */
  allocate_mdsys(&sys);

  /* read restart - set initial conditions */
  set_ic(&sys,restfile);

  /* initialize forces and energies.*/
  sys.nfi=0;
  force(&sys);
  ekin(&sys);
    
  erg=fopen(ergfile,"w");
  traj=fopen(trajfile,"w");

  printf("Starting simulation with %d atoms for %d steps.\n",sys.natoms,
	 sys.nsteps);
  printf("     NFI            TEMP            EKIN                 EPOT              ETOT\n");
  output(&sys, erg, traj);

  /**************************************************/
  /* main MD loop */
  for(sys.nfi=1; sys.nfi <= sys.nsteps; ++sys.nfi) {

    /* write output, if requested */
    if ((sys.nfi % nprint) == 0)
      output(&sys, erg, traj);

    /* propagate system and recompute energies */
    velverlet_1(&sys);
    force(&sys);
    velverlet_2(&sys);
    ekin(&sys);
  }
  /**************************************************/

  /* clean up: close files, free memory */
  printf("Simulation Done.\n");
  fclose(erg);
  fclose(traj);

  free_mdsys(&sys);
    
  double t_end = cclock();

  char outfile[50];
  sprintf(outfile, "time_%d.txt", sys.natoms);
#if defined(_OPENMP)
  sprintf(outfile, "time_%d_omp.txt", sys.natoms);
#endif 
  time=fopen(outfile,"w+");
  fprintf(time, "Execution times: %.3f s\n", t_end-t_start);
  fclose(time);

  return 0;
}
