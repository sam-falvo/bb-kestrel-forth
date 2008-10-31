MODULES = 	bootstrap			\
			cpu-vectors

.SUFFIXES: .a .o

.a.o:
	ca65 -Iinclude -l $<

all: ROMFILE

ROMFILE: $(MODULES:%=%.o)
	ld65 -m symbolmap --config ./ld65.config \
		$(MODULES:%=%.o)


#ROMFILE: $(MODULES:%=%.o) $(UNITTESTS:%=%_unittest.o)
#	ld65 -m symbolmap --config ./ld65.config \
#		$(MODULES:%=%.o)					 \
#		$(UNITTESTS:%=%_unittest.o)

clean:
	rm -f *.o *.lst ROMFILE a.out symbolmap

