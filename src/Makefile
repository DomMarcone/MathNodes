CC=g++
CXX=g++

IDIR=inc
ODIR=obj
SDIR=src
TDIR=test
BDIR=build

CFLAGS=-O3 -I./$(IDIR)
CXXFLAGS=-O3 -I./$(IDIR)


Parse: $(ODIR)/MathNodesTest.o $(ODIR)/parenthesize.o $(ODIR)/MathNodes.o $(ODIR)/MathNodeBuilder.o 
	$(CXX) $(ODIR)/parenthesize.o $(ODIR)/MathNodes.o $(ODIR)/MathNodeBuilder.o $(ODIR)/MathNodesTest.o -o $(BDIR)/$@.exe

$(ODIR)/MathNodesTest.o: $(TDIR)/MathNodesTest.cpp
	$(CXX) $(CXXFLAGS) -c $(TDIR)/MathNodesTest.cpp -o $@

$(ODIR)/MathNodeBuilder.o: $(SDIR)/MathNodeBuilder.cpp $(IDIR)/MathNodeBuilder.hpp $(IDIR)/MathNodes.hpp $(IDIR)/parenthesize.h
	$(CXX) $(CXXFLAGS) -c $(SDIR)/MathNodeBuilder.cpp -o $@

$(ODIR)/MathNodes.o: $(SDIR)/MathNodes.cpp $(IDIR)/MathNodes.hpp
	$(CXX) $(CXXFLAGS) -c $(SDIR)/MathNodes.cpp -o $@

$(ODIR)/parenthesize.o: $(SDIR)/parenthesize.c $(IDIR)/parenthesize.h
	$(CXX) $(CXXFLAGS) -c $(SDIR)/parenthesize.c -o $@
	
clean:
	rm -f $(ODIR)/*.o





