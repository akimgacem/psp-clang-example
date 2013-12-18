.macro STUB_START module, flags_ver, stub_len
	.section .rodata.sceResident, "a", @progbits
	.word   0
__stub_modulestr_\module:
	.asciz  "\module"
	.align  2

	.section .lib.stub, "a", @progbits
	.word   __stub_modulestr_\module
	.word   \flags_ver
	.word   \stub_len
	.word   __stub_idtable_\module
	.word   __stub_text_\module

	.section .rodata.sceNid, "a", @progbits
__stub_idtable_\module:

	.section .sceStub.text, "ax", @progbits
__stub_text_\module:
.endm

.macro STUB_FUNC funcid, funcname
	.section .sceStub.text, "ax", @progbits
	.globl  \funcname
\funcname:
	jr	$ra

	.section .rodata.sceNid, "a", @progbits
	.word   \funcid
.endm

.macro STUB_END
.endm

STUB_START "LoadExecForUser",0x40010000,0x00020005
STUB_FUNC 0x05572A5F,sceKernelExitGame
STUB_FUNC 0x4AC57943,sceKernelRegisterExitCallback
STUB_END

STUB_START "sceDisplay",0x40010000,0x00020005
STUB_FUNC 0x0E20F177,sceDisplaySetMode
STUB_FUNC 0x289D82FE,sceDisplaySetFrameBuf
STUB_END

STUB_START "sceGe_user",0x40010000,0x00010005
STUB_FUNC 0xE47E40E4,sceGeEdramGetAddr
STUB_END

STUB_START "ThreadManForUser",0x40010000,0x00050005
STUB_FUNC 0x446D8DE6,sceKernelCreateThread
STUB_FUNC 0x82826F70,sceKernelSleepThreadCB
STUB_FUNC 0x9ACE131E,sceKernelSleepThread
STUB_FUNC 0xE81CAF8F,sceKernelCreateCallback
STUB_FUNC 0xF475845D,sceKernelStartThread
STUB_END

