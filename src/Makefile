CC=gcc
CXX=g++

IDIR=inc
ODIR=build
SDIR=src
TDIR=test
BDIR=build

CFLAGS=-O3 -I./$(IDIR)
CXXFLAGS=-O3 -I./$(IDIR)

all : parse iparse MathNodeTest

#Build parser
parse: $(ODIR)/parse.o $(ODIR)/parenthesize.o $(ODIR)/MathNodes.o $(ODIR)/MathTreeBuilder.o
	$(CXX) $(CXXFLAGS) $(ODIR)/$@.o $(ODIR)/parenthesize.o $(ODIR)/MathNodes.o $(ODIR)/MathTreeBuilder.o -o $(BDIR)/$@.exe

$(ODIR)/parse.o: $(SDIR)/parse.cpp
	$(CXX) $(CXXFLAGS) -c $(SDIR)/parse.cpp -o $@


#build inline parser
iparse: $(ODIR)/iparse.o $(ODIR)/parenthesize.o $(ODIR)/MathNodes.o $(ODIR)/MathTreeBuilder.o
	$(CXX) $(CXXFLAGS) $(ODIR)/$@.o $(ODIR)/parenthesize.o $(ODIR)/MathNodes.o $(ODIR)/MathTreeBuilder.o -o $(BDIR)/$@.exe
	

$(ODIR)/iparse.o: $(SDIR)/iparse.cpp
	$(CXX) $(CXXFLAGS) -c $(SDIR)/iparse.cpp -o $@
	

#Build Test of MathNodeTest
MathNodeTest: $(ODIR)/MathNodesTest.o $(ODIR)/parenthesize.o $(ODIR)/MathNodes.o $(ODIR)/MathTreeBuilder.o 
	$(CXX) $(ODIR)/parenthesize.o $(ODIR)/MathNodes.o $(ODIR)/MathTreeBuilder.o $(ODIR)/MathNodesTest.o -o $(BDIR)/$@.exe

$(ODIR)/MathNodesTest.o: $(TDIR)/MathNodesTest.cpp
	$(CXX) $(CXXFLAGS) -c $(TDIR)/MathNodesTest.cpp -o $@

$(ODIR)/MathTreeBuilder.o: $(SDIR)/MathTreeBuilder.cpp $(IDIR)/MathTreeBuilder.hpp $(IDIR)/MathNodes.hpp $(IDIR)/parenthesize.h
	$(CXX) $(CXXFLAGS) -c $(SDIR)/MathTreeBuilder.cpp -o $@

$(ODIR)/MathNodes.o: $(SDIR)/MathNodes.cpp $(IDIR)/MathNodes.hpp
	$(CXX) $(CXXFLAGS) -c $(SDIR)/MathNodes.cpp -o $@

$(ODIR)/parenthesize.o: $(SDIR)/parenthesize.c $(IDIR)/parenthesize.h
	$(CXX) $(CXXFLAGS) -c $(SDIR)/parenthesize.c -o $@
	
clean:
	rm -f $(ODIR)/*.o






