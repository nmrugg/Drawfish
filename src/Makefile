CXXFLAGS += -Wall -Wcast-qual -fno-exceptions -fno-rtti
CXXFLAGS += -O3
CXXFLAGS += -flto
LDFLAGS += $(CXXFLAGS)

test: test.o
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)
