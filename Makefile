IDIR=./include
CXX=g++
CXXFLAGS=-I$(IDIR) -Wall `root-config --cflags --libs`

TARGET1 = poly
TARGET2 = q3EB

ODIR1=obj
ODIR2=$(ODIR1)/q3EB

_DEPS= fileSys.h limits.h classes.h sims.h histEdit.h kinematics.h simulation.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ1= poly.o fileSys.o neut.o limits.o histEdit.o kinematics.o
OBJ1 = $(patsubst %,$(ODIR1)/%,$(_OBJ1))

_OBJ2= q3EB.o simulation.o
OBJ2 = $(patsubst %,$(ODIR2)/%,$(_OBJ2))

all: $(TARGET1) $(TARGET2)

$(ODIR1)/%.o: src/%.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(TARGET1): $(OBJ1)
	$(CXX) $(CXXFLAGS) $^ -o $@


$(ODIR2)/%.o: src/q3EB/%.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(TARGET2): $(OBJ2)
	$(CXX) $(CXXFLAGS) $^ -o $@



.PHONY: clean

clean:
	rm -f $(TARGET1) $(TARGET2) $(ODIR1)/*.o $(ODIR2)/*.o *~ core src/*~ $(INCDIR)/*~
