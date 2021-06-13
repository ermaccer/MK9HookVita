#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <psp2/kernel/threadmgr.h> 
#include "mk9.h"
#include "mk9menu.h"




SceUID thid = -1;


int mk9_thread(unsigned int args, void* argp)
{
	while (1)
	{
		MK9Menu_Update();
	}
	return 0;
}


void _start() __attribute__((weak, alias("module_start")));

int module_start(SceSize argc, const void *args) 
{
	thid = sceKernelCreateThread("mk9hook_thread", mk9_thread, 0x40, 0x10000, 0, 0, NULL);
	sceKernelStartThread(thid, 0, NULL);
	MK9Menu_Init();
	InitHooks();

	return SCE_KERNEL_START_SUCCESS;
}
int module_stop(SceSize argc, const void *args)
{
	sceKernelWaitThreadEnd(thid, NULL, NULL);

	return SCE_KERNEL_STOP_SUCCESS;
}
