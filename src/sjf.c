#include "sched.h"

void sjf(Proc *p, int n, Gantt *g) {
    int done[MAXP] = {0}, t = 0, c = 0;
    while (c < n) {
        int b = -1;
        for (int i = 0; i < n; i++)
            if (!done[i] && p[i].at <= t && (b < 0 || p[i].bt < p[b].bt)) b = i;
        if (b < 0) {                         // idle: jump to next arrival
            int m = 1 << 30;
            for (int i = 0; i < n; i++) if (!done[i] && p[i].at < m) m = p[i].at;
            gantt_add(g, -1, t, m); t = m; continue;
        }
        gantt_add(g, p[b].pid, t, t + p[b].bt);
        t += p[b].bt; done[b] = 1; c++;
    }
}
