#include "moduleinfo.h"
#include "user/display.h"
#include "user/ge.h"
#include "user/loadexec.h"
#include "user/threadman.h"

PSP_MODULE_INFO("clang_test", PSP_MODULE_USER, 1, 1);

int exit_callback(int arg1, int arg2, void *common) {
    sceKernelExitGame();
    return 0;
}

int callback_thread(unsigned int args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, 0);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

int setup_callbacks() {
    int thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, 0);
    if (thid >= 0)
        sceKernelStartThread(thid, 0, 0);
    return thid;
}

void display_init() {
    void *vram = (void *) (0x40000000 | (unsigned int) sceGeEdramGetAddr());
    sceDisplaySetMode(0, 480, 272);
    sceDisplaySetFrameBuf(vram, 512, 3, 1);
}

void display_clear() {
    unsigned int *vram = (unsigned int*) (0x40000000 | (unsigned int) sceGeEdramGetAddr());
    for(int x = 0; x < (512 * 272); x++)
        *vram++ = 0x00ff00ff;
}

int _main(int args, void *argp) {
    setup_callbacks();
    display_init();
    display_clear();
    sceKernelSleepThread();
    sceKernelExitGame();
    return 0;
}

int module_start(int args, void *argp) {
    int thid = sceKernelCreateThread("user_main", (void*) _main, 0x20, 0x40000, 0, 0);
    sceKernelStartThread(thid, args, argp);
    return 0;
}

