# Simple VC (6) makefile for Cmdow.

CPPFLAGS = /nologo /W3 /O2 /MD
LIBS = user32.lib shell32.lib
OBJS = obj\main.obj obj\args.obj obj\tlist.obj obj\wlist.obj obj\help.obj

LD = $(CC)
V = 0
!IF $V == 0
CC = @$(CC)
LD = @echo $@&$(LD)
!ENDIF

{}.cpp{obj}.obj::
	$(CC) $(CPPFLAGS) /c /Foobj\ $<

all: bin obj bin\cmdow.exe

bin obj:
		mkdir $@

bin\cmdow.exe: $(OBJS)
		$(LD) /nologo /Fe$@ $** $(LIBS) /link /filealign:512

clean:
		-del $(OBJS)
