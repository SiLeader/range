TARGET		= test.out
CXXFLAGS	= -std=c++11 -I..
SOURCES		= test.cpp

.PHONY: build
build:
	$(CXX) -o $(TARGET) $(CXXFLAGS) $(SOURCES)

.PHONY: debug
debug:
	$(CXX) -o $(TARGET) $(CXXFLAGS) -g $(SOURCES)

.PHONY: clean
clean:
	rm -f $(TARGET) *.o *.out
