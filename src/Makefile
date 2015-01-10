CXXFLAGS += -O3 -flto
LDFLAGS += $(CXXFLAGS)

test: test.o
	$(CXX) -o $@ test.o $(LDFLAGS)
