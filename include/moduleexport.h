#ifndef PSP_MODEXPORT_H_
#define PSP_MODEXPORT_H_

struct _PspLibraryEntry {
    const char * name;
    unsigned short version;
    unsigned short attribute;
    unsigned char entLen;
    unsigned char varCount;
    unsigned short funcCount;
    void * entrytable;
};

#endif

