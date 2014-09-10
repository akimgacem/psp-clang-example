TARGET=clang_test
OBJS=main.o exports.o imports.o

CC=clang
AS=llvm-mc
LD=psp-ld

CFLAGS=-target mipsallegrexel-unknown-psp-elf -mabi=eabi -G0 -O2 -Wall -I./include
ASFLAGS=-triple=mipsallegrexel-unknown-psp-elf -filetype=obj
LDFLAGS=-G0 -EL -q -T/opt/pspsdk/psp/sdk/lib/linkfile.prx

all: EBOOT.PBP

$(TARGET).elf: $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

PARAM.SFO: 
	mksfo $(TARGET) $@

EBOOT.PBP: $(TARGET).prx PARAM.SFO
	pack-pbp EBOOT.PBP PARAM.SFO NULL NULL NULL NULL NULL $(TARGET).prx NULL

$(TARGET).prx: $(TARGET).elf
	psp-prxgen $< $@

main.o: main.c
	$(CC) $(CFLAGS) -S $<
	$(AS) main.s $(ASFLAGS) -o $@

exports.o: exports.c
	$(CC) $(CFLAGS) -S $<
	$(AS) exports.s $(ASFLAGS) -o $@

imports.o: imports.s
	$(AS) $< $(ASFLAGS) -o $@

clean: 
	rm -f $(TARGET).prx $(TARGET).elf PARAM.SFO EBOOT.PBP $(OBJS) main.s exports.s

rebuild: clean all

