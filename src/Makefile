CXXFLAGS += -O3
CXXFLAGS += -flto
LDFLAGS += $(CXXFLAGS)

test: test.o
	$(CXX) -o $@ test.o $(LDFLAGS)
