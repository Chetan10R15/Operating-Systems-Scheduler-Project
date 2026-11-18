#ifndef SCHED_H
#define SCHED_H
#define MAXP 32
#define MAXSEG 512

typedef struct { int pid, at, bt, pr; } Proc;
typedef struct { int pid, start, end; } Seg;      // pid = -1 means idle
typedef struct { Seg seg[MAXSEG]; int n; } Gantt;

int  load_procs(const char *file, Proc *p);
void gantt_add(Gantt *g, int pid, int s, int e);
void report(const char *name, Proc *p, int n, Gantt *g);
void metrics(Proc *p, int n, Gantt *g, float *wt, float *tat);

void fcfs(Proc *p, int n, Gantt *g);
void sjf(Proc *p, int n, Gantt *g);
void priority_np(Proc *p, int n, Gantt *g);
void srtf(Proc *p, int n, Gantt *g);
void priority_p(Proc *p, int n, Gantt *g);
void rr(Proc *p, int n, Gantt *g, int q);
int export_html(const char *file, Proc *p, int n, int q);
#endif
