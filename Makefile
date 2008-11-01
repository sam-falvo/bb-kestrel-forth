MODULES =	bootstrap			\
			cpu-vectors			\
			terminal

.SUFFIXES: .a .o

.a.o:
	ca65 -Iinclude -l $<

all: builddir ROMFILE

builddir:
	mkdir -p build
	cp $(MODULES:%=%.a) build

ROMFILE: $(MODULES:%=build/%.o)
	ld65 -m symbolmap --config ./ld65.config \
		$(MODULES:%=build/%.o)


#ROMFILE: $(MODULES:%=%.o) $(UNITTESTS:%=%_unittest.o)
#	ld65 -m symbolmap --config ./ld65.config \
#		$(MODULES:%=%.o)					 \
#		$(UNITTESTS:%=%_unittest.o)

clean:
	rm -f *.o *.lst ROMFILE a.out symbolmap
	rm -rf build

