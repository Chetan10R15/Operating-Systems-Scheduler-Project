#include <stdio.h>
#include "sched.h"

void gantt_add(Gantt *g, int pid, int s, int e) {
    if (g->n && g->seg[g->n-1].pid == pid && g->seg[g->n-1].end == s) {
        g->seg[g->n-1].end = e; return;      // merge back-to-back slices
    }
    g->seg[g->n++] = (Seg){pid, s, e};
}

void report(const char *name, Proc *p, int n, Gantt *g) {
    printf("\n=== %s ===\n", name);
    for (int i = 0; i < g->n; i++) {
        if (g->seg[i].pid < 0) printf("|  -  ");
        else printf("\033[4%dm| P%-2d \033[0m", 1 + g->seg[i].pid % 6, g->seg[i].pid);
    }
    printf("|\n");
    for (int i = 0; i < g->n; i++) printf("%-6d", g->seg[i].start);
    int total = g->seg[g->n-1].end;
    printf("%d\n\nPID  AT  BT  CT  TAT  WT  RT\n", total);

    float sw = 0, st = 0, sr = 0; int busy = 0;
    for (int i = 0; i < n; i++) {
        int ct = 0, first = -1;
        for (int j = 0; j < g->n; j++) if (g->seg[j].pid == p[i].pid) {
            if (first < 0) first = g->seg[j].start;
            ct = g->seg[j].end;
        }
        int tat = ct - p[i].at, wt = tat - p[i].bt, rt = first - p[i].at;
        printf("P%-3d %3d %3d %3d %4d %3d %3d\n", p[i].pid, p[i].at, p[i].bt, ct, tat, wt, rt);
        sw += wt; st += tat; sr += rt; busy += p[i].bt;
    }
    printf("Avg WT=%.2f  Avg TAT=%.2f  Avg RT=%.2f  CPU util=%.1f%%\n",
           sw / n, st / n, sr / n, 100.0 * busy / total);
}
void metrics(Proc *p, int n, Gantt *g, float *wt, float *tat) {
    *wt = *tat = 0;
    for (int i = 0; i < n; i++) {
        int ct = 0;
        for (int j = 0; j < g->n; j++) if (g->seg[j].pid == p[i].pid) ct = g->seg[j].end;
        int t = ct - p[i].at;
        *tat += t; *wt += t - p[i].bt;
    }
    *wt /= n; *tat /= n;
}
