CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

demo: main.o data_reader.o func.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp data_reader.hpp func.hpp
	$(CXX) $(CXXFLAGS) -c $<

data_reader.o: data_reader.cpp data_reader.hpp
	$(CXX) $(CXXFLAGS) -c $<

func.o: func.cpp func.hpp data_reader.hpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o demo
