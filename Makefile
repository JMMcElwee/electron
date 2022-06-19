IDIR=./include
CXX=g++
CXXFLAGS=-I$(IDIR) `root-config --cflags --libs`


poly: src/*.cc
	$(CXX) $(CXXFLAGS) $? -o $@
