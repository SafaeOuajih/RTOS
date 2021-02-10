#APPRAMBASE  = 0x1000000
APPRAMBASE  = 0x100000
TARGET_IP   = 135.222.138.18
APPNAME		= app

UCOSDIR		= ../../uCOS-II
KERNELDIR	= $(UCOSDIR)/Source
PORTDIR		= $(UCOSDIR)/Ports
ODIR		= obj

INCLUDES	= -I $(KERNELDIR) -I $(PORTDIR) -I ./include -I .

CC			= bfin-elf-gcc
LD			= bfin-elf-ld
NM			= bfin-elf-nm
STRIP		= bfin-elf-strip
CFLAGS		= -fno-builtin -mcsync-anomaly -c -Wall -O -g \
			  -D __ADSPLPBLACKFIN__ $(INCLUDES)
LIBGCC      = `$(CC) --print-libgcc-file-name`

KERNELOBJS	= $(ODIR)/os_core.o $(ODIR)/os_dbg_r.o $(ODIR)/os_flag.o \
			  $(ODIR)/os_mbox.o $(ODIR)/os_mem.o $(ODIR)/os_mutex.o \
			  $(ODIR)/os_q.o $(ODIR)/os_sem.o $(ODIR)/os_task.o \
			  $(ODIR)/os_time.o $(ODIR)/os_tmr.o
			  

PORTOBJS	= $(ODIR)/os_cpu_a.o $(ODIR)/os_cpu_c.o
APPOBJS		= $(ODIR)/crt0_bfin.o $(ODIR)/main.o $(ODIR)/bsp.o $(ODIR)/printf.o

OBJS		= $(KERNELOBJS) $(PORTOBJS) $(APPOBJS)

$(APPNAME): $(KERNELOBJS) $(PORTOBJS) $(APPOBJS)
		$(LD) -e start -o $(APPNAME).elf -Ttext $(APPRAMBASE) $(OBJS) $(LIBPATH) \
			-lc -lm $(LIBGCC)
		$(NM) $(APPNAME).elf > $(APPNAME).sym
		\cp $(APPNAME).elf /tftpboot


#########################################################
#
# KERNEL objects:
#
$(ODIR)/os_core.o:	$(KERNELDIR)/os_core.c
		$(CC) $(CFLAGS) -o $@ $(KERNELDIR)/os_core.c

$(ODIR)/os_dbg_r.o:	$(KERNELDIR)/os_dbg_r.c
		$(CC) $(CFLAGS) -o $@ $(KERNELDIR)/os_dbg_r.c

$(ODIR)/os_flag.o:	$(KERNELDIR)/os_flag.c
		$(CC) $(CFLAGS) -o $@ $(KERNELDIR)/os_flag.c

$(ODIR)/os_mbox.o:	$(KERNELDIR)/os_mbox.c
		$(CC) $(CFLAGS) -o $@ $(KERNELDIR)/os_mbox.c

$(ODIR)/os_mem.o:	$(KERNELDIR)/os_mem.c
		$(CC) $(CFLAGS) -o $@ $(KERNELDIR)/os_mem.c

$(ODIR)/os_mutex.o:	$(KERNELDIR)/os_mutex.c
		$(CC) $(CFLAGS) -o $@ $(KERNELDIR)/os_mutex.c

$(ODIR)/os_q.o:		$(KERNELDIR)/os_q.c
		$(CC) $(CFLAGS) -o $@ $(KERNELDIR)/os_q.c

$(ODIR)/os_sem.o:	$(KERNELDIR)/os_sem.c
		$(CC) $(CFLAGS) -o $@ $(KERNELDIR)/os_sem.c

$(ODIR)/os_task.o:	$(KERNELDIR)/os_task.c
		$(CC) $(CFLAGS) -o $@ $(KERNELDIR)/os_task.c

$(ODIR)/os_time.o:	$(KERNELDIR)/os_time.c
		$(CC) $(CFLAGS) -o $@ $(KERNELDIR)/os_time.c

$(ODIR)/os_tmr.o:	$(KERNELDIR)/os_tmr.c
		$(CC) $(CFLAGS) -o $@ $(KERNELDIR)/os_tmr.c

$(ODIR)/ucos_ii.o:	$(KERNELDIR)/ucos_ii.c
		$(CC) $(CFLAGS) -o $@ $(KERNELDIR)/ucos_ii.c


#########################################################
#
# PORT objects:
#
$(ODIR)/os_cpu_a.o:	$(PORTDIR)/os_cpu_a.S
		$(CC) $(CFLAGS) -D _LANGUAGE_ASM -o $@ $(PORTDIR)/os_cpu_a.S

$(ODIR)/os_cpu_c.o:	$(PORTDIR)/os_cpu_c.c
		$(CC) $(CFLAGS) -o $@ $(PORTDIR)/os_cpu_c.c


#########################################################
#
# APP objects:
#
$(ODIR)/main.o:	main.c
		$(CC) $(CFLAGS) -o $@ main.c

$(ODIR)/bsp.o:	bsp.c
		$(CC) $(CFLAGS) -o $@ bsp.c

$(ODIR)/printf.o:	printf.c
		$(CC) $(CFLAGS) -o $@ printf.c

$(ODIR)/crt0_bfin.o:	crt0_bfin.S
		$(CC) $(CFLAGS) -o $@ crt0_bfin.S

#########################################################
#
# miscellaneous:
#
cscope:
	find $(KERNELDIR) -name '*.[chS]' >cscope.files
	find $(PORTDIR) -name '*.[chS]' >>cscope.files
	find . -name '*.[chS]' >>cscope.files
	ctags --file-tags=yes -n -L cscope.files

clean:
	rm -rf $(APPNAME).elf $(APPNAME).sym stripped $(ODIR)/*.o
