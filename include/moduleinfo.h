#ifndef __MODULEINFO_H__
#define __MODULEINFO_H__

typedef struct {
    unsigned short modattribute;
    unsigned char modversion[2];
    char modname[27];
    char terminal;
    void* gp_value;
    void* ent_top;
    void* ent_end;
    void* stub_top;
    void* stub_end;
} __attribute__((aligned(16))) SceModuleInfo;

extern char _gp[];

enum PspModuleInfoAttr {
    PSP_MODULE_USER = 0,
    PSP_MODULE_NO_STOP = 0x0001,
    PSP_MODULE_SINGLE_LOAD = 0x0002,
    PSP_MODULE_SINGLE_START = 0x0004,
    PSP_MODULE_KERNEL = 0x1000
};

#define PSP_MODULE_INFO(name, attributes, major_version, minor_version) \
    const int __lib_ent_top __attribute__((section(".lib.ent.top"), align(4))) = 0; \
    const int __lib_ent_bottom __attribute__((section(".lib.ent.btm"), align(4))) = 0; \
    const int __lib_stub_top __attribute__((section(".lib.stub.top"), align(4))) = 0; \
    const int __lib_stub_bottom __attribute__((section(".lib.stub.btm"), align(4))) = 0; \
    SceModuleInfo module_info __attribute__((section(".rodata.sceModuleInfo"), unused)) = { \
        attributes, {minor_version, major_version}, name, 0, _gp, \
        (void *) &__lib_ent_top + 4, (void *) &__lib_ent_bottom, \
        (void *) &__lib_stub_top + 4, (void *) &__lib_stub_bottom \
    }

#endif

