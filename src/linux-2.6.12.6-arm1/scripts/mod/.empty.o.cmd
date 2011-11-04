cmd_scripts/mod/empty.o := arm-linux-uclibc-gcc -Wp,-MD,scripts/mod/.empty.o.d  -nostdinc -isystem /home/juergh/Projects/dns-323/toolchain/bin/../lib/gcc-lib/arm-linux-uclibc/3.3.3/include -D__KERNEL__ -Iinclude  -mlittle-endian -Wall -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -ffreestanding -Os     -fno-omit-frame-pointer -g -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mapcs-32 -mno-thumb-interwork   -mshort-load-bytes -msoft-float -Uarm      -DKBUILD_BASENAME=empty -DKBUILD_MODNAME=empty -c -o scripts/mod/.tmp_empty.o scripts/mod/empty.c

deps_scripts/mod/empty.o := \
  scripts/mod/empty.c \

scripts/mod/empty.o: $(deps_scripts/mod/empty.o)

$(deps_scripts/mod/empty.o):
