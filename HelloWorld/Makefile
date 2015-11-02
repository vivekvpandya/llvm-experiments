LLVM_CONFIG ?= llvm-config

ifndef VERBOSE
QUITE := @
endif

SRC_DIR ?= $(PWD)

LDFLAGS += $(shell $(LLVM_CONFIG) --ldflags)
COMMON_FLAGS = -Wall -Wextra -std=c++11
CXXFLAGS += $(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags)
CPPFLAGS += $(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR)

HELLO=helloWorld
HELLO_OBJECTS=helloWorld.o

default: $(HELLO)	

%.o : $(SRC_DIR)/%.cpp
	@echo Compiling $*.cpp
	$(QUIET) $(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(HELLO) : $(HELLO_OBJECTS)
	@echo Linking $@
	$(QUIET) $(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^ `$(LLVM_CONFIG) --libs bitreader core support --system-libs`




