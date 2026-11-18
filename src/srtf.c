#include "sched.h"

void srtf(Proc *p, int n, Gantt *g) {
    int rem[MAXP], t = 0, c = 0;
    for (int i = 0; i < n; i++) rem[i] = p[i].bt;
    while (c < n) {
        int b = -1;
        for (int i = 0; i < n; i++)
            if (rem[i] > 0 && p[i].at <= t && (b < 0 || rem[i] < rem[b])) b = i;
        if (b < 0) {
            int m = 1 << 30;
            for (int i = 0; i < n; i++) if (rem[i] > 0 && p[i].at < m) m = p[i].at;
            gantt_add(g, -1, t, m); t = m; continue;
        }
        gantt_add(g, p[b].pid, t, t + 1);    // run 1 tick, then re-decide
        t++;
        if (--rem[b] == 0) c++;
    }
}
