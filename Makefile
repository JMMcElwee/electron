IDIR=./include
CXX=g++
CXXFLAGS=-I$(IDIR) `root-config --cflags --libs`

ODIR=obj

_DEPS= fileSys.h limits.h classes.h sims.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= poly.o fileSys.o neut.o limits.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: src/%.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

poly: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@


.PHONY: clean

clean:
	rm -f poly $(ODIR)/*.o *~ core src/*~ $(INCDIR)/*~
