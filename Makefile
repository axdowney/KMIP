# Add .d to Make's recognized suffixes.
# SUFFIXES += .d
CPP_FILES := $(wildcard ./*.cpp)
OBJ_FILES := $(addprefix ./obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := ...
CC_FLAGS := ...
CXX := g++ -g
CC := gcc -g
CPPFLAGS := -std=c++11
CFLAGS :=
#include ./boost.mk
INC := -I$(HOME)/KMIP/ -I$(HOME)/KMIP/types -I$(HOME)/common -I$(HOME)/KMIP/handlers -I$(HOME)/KMIP/handlers/operations -I/usr/include/partow/


LIBS := -lgtest -lgtest_main -lpthread -lpqxx -lpq -lcryptopp -lpugixml /usr/local/lib/libadios.so -lmpi

SRCDIR := .
OBJDIR := obj
DEPDIR := dep
TESTDIR := test

TEST_FILES := $(wildcard $(TESTDIR)/*.cpp)
SRCS     := $(shell find -L $(SRCDIR) -name "*.cpp")
OBJS     := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS     := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.d)

C_FILES    := $(shell find -L $(SRCDIR) -name "*.c")
C_OBJS     := $(C_FILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TREE     := $(sort $(patsubst %/,%,$(dir $(OBJS))))



#$(warning $(SRCS))
#$(warning $(OBJS))
#$(warning $(DEPS))
#$(warning $(TREE))

all: $(TREE) $(DEPS) $(OBJS) $(C_OBJS)

#Don't create dependencies when we're cleaning, for instance
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
    #Chances are, these files don't exist.  GMake will create them and
    #clean up automatically afterwards
    #$(warning $(DEPS))
    -include $(DEPS)
endif


$(TREE):
	mkdir -p $@

$(OBJDIR)/%.d : %.cpp 
	$(CXX) $(CPPFLAGS) ${INC} -MM -MT '$(patsubst %.cpp,obj/%.o,$<)' $< -MF $@

$(OBJDIR)/%.o : %.c 
	${CC} ${CFLAGS} ${INC} -o $@ -c $^

$(OBJDIR)/%.o : %.cpp $(OBJDIR)/%.d %.h
	${CXX} ${CPPFLAGS} ${INC} -o $@ -c $<

$(OBJDIR)/%.o : %.cpp $(OBJDIR)/%.d
	${CXX} ${CPPFLAGS} ${INC} -o $@ -c $<

clean:
	rm -r $(OBJDIR)/*

force: clean all


#$(warning $(TEST_FILES))

test: $(TESTDIR)/KMIPTest

$(TESTDIR)/KMIPTest: $(OBJS) 
	${CXX} ${CPPFLAGS} ${INC} -o $(TESTDIR)/KMIPTest $(C_OBJS) $(OBJS) $(LIBS)

testf: 
	${CXX} ${CPPFLAGS} ${INC} -o $(TESTDIR)/KMIPTest $(C_OBJS) $(OBJS) $(LIBS)

