#ifndef __DISPLAY_H__
#define __DISPLAY_H__

int sceDisplaySetMode(int mode, int width, int height);
int sceDisplaySetFrameBuf(void * topaddr, int bufferwidth, int pixelformat, int sync);

#endif

