#include <stdio.h>
#include "sched.h"

static const char *names[] = {"FCFS", "SJF", "SRTF", "Priority (non-preemptive)",
                              "Priority (preemptive)", "Round Robin"};

static void runalgo(int k, Proc *p, int n, Gantt *g, int q) {
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

int export_html(const char *file, Proc *p, int n, int q) {
    FILE *f = fopen(file, "w");
    if (!f) { perror(file); return -1; }
    static const char *col[] = {"#e74c3c", "#3498db", "#2ecc71", "#f39c12", "#9b59b6", "#1abc9c"};

    fprintf(f, "<html><head><meta charset='utf-8'><title>CPU Scheduler Simulator</title><style>"
        "body{font-family:sans-serif;margin:30px}"
        ".bar{display:flex}"
        ".seg{color:#fff;text-align:center;padding:8px 0;border-right:1px solid #fff;font-size:11px;overflow:hidden;box-sizing:border-box}"
        ".idle{background:#ccc;color:#555}"
        "table{border-collapse:collapse}td,th{border:1px solid #999;padding:4px 10px}"
        ".wt{background:#3498db;height:14px}.tat{background:#e67e22;height:14px}"
        "</style></head><body><h1>CPU Scheduler Simulator</h1>");

    float W[6], T[6];
    Gantt g;
    for (int k = 0; k < 6; k++) {
        runalgo(k, p, n, &g, q);
        metrics(p, n, &g, &W[k], &T[k]);
        fprintf(f, "<h2>%s</h2><div class='bar'>", names[k]);
        for (int i = 0; i < g.n; i++) {
            int w = (g.seg[i].end - g.seg[i].start) * 20;
            if (g.seg[i].pid < 0)
                fprintf(f, "<div class='seg idle' style='width:%dpx'>idle<br>%d-%d</div>",
                        w, g.seg[i].start, g.seg[i].end);
            else
                fprintf(f, "<div class='seg' style='width:%dpx;background:%s'>P%d<br>%d-%d</div>",
                        w, col[g.seg[i].pid % 6], g.seg[i].pid, g.seg[i].start, g.seg[i].end);
        }
        fprintf(f, "</div><p>Avg WT = %.2f, Avg TAT = %.2f</p>", W[k], T[k]);
    }

    fprintf(f, "<h2>Comparison (Round Robin quantum = %d)</h2><table>"
               "<tr><th>Algorithm</th><th>Avg WT</th><th>Avg TAT</th></tr>", q);
    for (int k = 0; k < 6; k++)
        fprintf(f, "<tr><td>%s</td>"
                   "<td>%.2f<div class='wt' style='width:%dpx'></div></td>"
                   "<td>%.2f<div class='tat' style='width:%dpx'></div></td></tr>",
                names[k], W[k], (int)(W[k] * 20), T[k], (int)(T[k] * 20));
    fprintf(f, "</table></body></html>");
    fclose(f);
    return 0;
}
