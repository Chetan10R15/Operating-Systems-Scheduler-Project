#include <stdio.h>
#include "sched.h"

static const char *names[] = {"FCFS", "SJF", "SRTF", "Priority (non-preemptive)",
                              "Priority (preemptive)", "Round Robin"};

static void run(int k, Proc *p, int n, Gantt *g, int q) {
    g->n = 0;
    switch (k) {
        case 0: fcfs(p, n, g); break;
        case 1: sjf(p, n, g); break;
        case 2: srtf(p, n, g); break;
        case 3: priority_np(p, n, g); break;
        case 4: priority_p(p, n, g); break;
        case 5: rr(p, n, g, q); break;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) { printf("usage: %s <datafile>\n", argv[0]); return 1; }
    Proc p[MAXP];
    int n = load_procs(argv[1], p);
    if (n <= 0) return 1;
    Gantt g;

    while (1) {
        printf("\n1.FCFS 2.SJF 3.SRTF 4.Priority(NP) 5.Priority(P) 6.RR 7.Compare all 0.Exit\nChoice: ");
        int ch; if (scanf("%d", &ch) != 1 || ch == 0) break;
        if (ch >= 1 && ch <= 5) { run(ch - 1, p, n, &g, 0); report(names[ch - 1], p, n, &g); }
        else if (ch == 6) {
            int q; printf("Quantum: "); scanf("%d", &q);
            run(5, p, n, &g, q); report(names[5], p, n, &g);
        } else if (ch == 7) {
            printf("\n%-28s %8s %8s\n", "Algorithm", "Avg WT", "Avg TAT");
            for (int k = 0; k < 6; k++) {
                float wt, tat;
                run(k, p, n, &g, 2);
                metrics(p, n, &g, &wt, &tat);
                printf("%-28s %8.2f %8.2f\n", names[k], wt, tat);
            }
            printf("(Round Robin uses quantum 2)\n");
        }
           else if (ch == 8) {
            if (export_html("report.html", p, n, 2) == 0) printf("Wrote report.html\n");
        }
    }
    return 0;
}
