TARGET=clang_test
OBJS=main.o exports.o imports.o

CC=clang
AS=clang
LD=psp-ld

CFLAGS=-target mipsallegrexel-unknown-psp-elf -mabi=eabi -O2 -Wall -I./include -integrated-as
ASFLAGS=-target mipsallegrexel-unknown-psp-elf -mabi=eabi -O2 -Wall -integrated-as -c
LDFLAGS=-q -T/opt/pspsdk/psp/sdk/lib/linkfile.prx

all: EBOOT.PBP

$(TARGET).elf: $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

PARAM.SFO: 
	mksfo $(TARGET) $@

EBOOT.PBP: $(TARGET).prx PARAM.SFO
	pack-pbp EBOOT.PBP PARAM.SFO NULL NULL NULL NULL NULL $(TARGET).prx NULL

$(TARGET).prx: $(TARGET).elf
	psp-prxgen $< $@

clean: 
	rm -f $(TARGET).prx $(TARGET).elf PARAM.SFO EBOOT.PBP $(OBJS)

rebuild: clean all

