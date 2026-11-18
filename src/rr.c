#include "sched.h"

void rr(Proc *p, int n, Gantt *g, int q) {
    int rem[MAXP], inq[MAXP] = {0}, qu[4096], h = 0, tl = 0, t = 0, c = 0;
    for (int i = 0; i < n; i++) rem[i] = p[i].bt;
    while (c < n) {
        for (int i = 0; i < n; i++)
            if (!inq[i] && p[i].at <= t) { qu[tl++] = i; inq[i] = 1; }
        if (h == tl) {                        // queue empty, CPU idle
            int m = 1 << 30;
            for (int i = 0; i < n; i++) if (!inq[i] && p[i].at < m) m = p[i].at;
            gantt_add(g, -1, t, m); t = m; continue;
        }
        int b = qu[h++], run = rem[b] < q ? rem[b] : q;
        gantt_add(g, p[b].pid, t, t + run);
        t += run; rem[b] -= run;
        for (int i = 0; i < n; i++)           // new arrivals go before the preempted one
            if (!inq[i] && p[i].at <= t) { qu[tl++] = i; inq[i] = 1; }
        if (rem[b] > 0) qu[tl++] = b; else c++;
    }
}
