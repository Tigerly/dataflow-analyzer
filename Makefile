
#========================================
# toolchain
#========================================

# just modify this line to switch your llvm version
LLVM_CONF=llvm-config

CLANG_DIR = $(shell $(LLVM_CONF) --bindir)
CXXFLAGS = -I $(CLANG_DIR)/../include -fPIC -Wall -std=c++11 -g -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS

CXX = g++
C   = g++
LD  = g++

#========================================
# targets
#========================================

OBJS :=
OBJS += Analyzer.o
OBJS += DumpGraph.o
OBJS += llvm_util.o

TARG := libdfa.so


all: $(TARG)

%.o: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) -c $<

$(TARG): $(OBJS)
	$(LD) --shared -o $(TARG) $(OBJS)

clean:
	rm -rf $(OBJS) $(TARG)

