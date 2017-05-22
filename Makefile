
#========================================
# toolchain
#========================================

# just modify this line to switch your llvm version
LLVM_CONF=llvm-config

CLANG_DIR = $(shell $(LLVM_CONF) --bindir)
LLVM_CXXFLAGS = $(shell $(LLVM_CONF) --cxxflags)

# leave empty to prevent error 'xxx is registerd more than once'.
# this is decided by how clang is installed in your system.
LLVM_LIBS = 
# LLVM_LIBS = $(shell $(LLVM_CONF) --libs)
LLVM_LDFLAGS = $(shell $(LLVM_CONF) --ldflags)

CXX = $(CLANG_DIR)/clang
C   = $(CLANG_DIR)/clang
LD  = $(CLANG_DIR)/clang
OPT = $(CLANG_DIR)/opt

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
	$(CXX) -o $@ $(LLVM_CXXFLAGS) -c $<

$(TARG): $(OBJS)
	$(LD) --shared -o $(TARG) $(OBJS) $(LLVM_LDFLAGS) $(LLVM_LIBS)

clean:
	rm -rf $(OBJS) $(TARG)

