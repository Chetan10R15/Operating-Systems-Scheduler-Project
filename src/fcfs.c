#include "sched.h"

void fcfs(Proc *p, int n, Gantt *g) {
    int done[MAXP] = {0}, t = 0;
    for (int c = 0; c < n; c++) {
        int b = -1;
        for (int i = 0; i < n; i++)
            if (!done[i] && (b < 0 || p[i].at < p[b].at)) b = i;
        if (p[b].at > t) { gantt_add(g, -1, t, p[b].at); t = p[b].at; }
        gantt_add(g, p[b].pid, t, t + p[b].bt);
        t += p[b].bt; done[b] = 1;
    }
}
