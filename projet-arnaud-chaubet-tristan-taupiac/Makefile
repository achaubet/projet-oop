CXX=g++
CXXFLAGS=-std=c++98 -pedantic -Wall -Werror -g `pkg-config pugixml --cflags`
LDFLAGS=`pkg-config pugixml --libs-only-L`
LDLIBS=`pkg-config pugixml --libs-only-l`
RM=rm -fv
.PHONY: all clean
all: ssp.out
%.o: %.cpp %.h
		$(CXX) $(CXXFLAGS) -c -o $@ $<
ssp.out: anime.o film.o media.o series.o ssp.cpp str2f-error.o str2i-error.o str2l-error.o streaming-service.o
	  $(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)
clean:
	  $(RM) *.o *.out
