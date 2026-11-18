#include <stdio.h>
#include "sched.h"

int load_procs(const char *f, Proc *p) {
    FILE *fp = fopen(f, "r");
    if (!fp) { perror(f); return -1; }
    int n = 0;
    while (n < MAXP && fscanf(fp, "%d %d %d %d",
           &p[n].pid, &p[n].at, &p[n].bt, &p[n].pr) == 4) n++;
    fclose(fp);
    return n;
}
