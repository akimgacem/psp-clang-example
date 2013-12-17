#ifndef __THREADMAN_H__
#define __THREADMAN_H__

typedef int (*SceKernelThreadEntry)(unsigned int args, void *argp);

typedef int (*SceKernelCallbackFunction)(int arg1, int arg2, void *arg);

typedef struct {
    unsigned int size;
    int stackMpid;
} SceKernelThreadOptParam;

int sceKernelCreateThread(const char * name, SceKernelThreadEntry entry, int initPriority, int stackSize, unsigned int attr, SceKernelThreadOptParam * option);
int sceKernelStartThread(int thid, unsigned int arglen, void * argp);
int sceKernelSleepThread();
int sceKernelSleepThreadCB();
int sceKernelCreateCallback(const char * name, SceKernelCallbackFunction func, void * arg);

#endif

