CPP_FILES := $(wildcard ./*.cpp)
OBJ_FILES := $(addprefix ./obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := ...
CC_FLAGS := ...
CXX := g++ -g
CC := gcc -g
CPPFLAGS := -std=c++11
CFLAGS :=
INC := -I/home/alexander/KMIP/ -I/home/alexander/KMIP/types -I/home/alexander/common
LIBS := -lgtest -lgtest_main -lpthread -lpqxx -lpq

SRCDIR := .
OBJDIR := obj
DEPDIR := dep
TESTDIR := test

TEST_FILES := $(wildcard $(TESTDIR)/*.cpp)
SRCS     := $(shell find -L $(SRCDIR) -name "*.cpp")
OBJS     := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

C_FILES    := $(shell find -L $(SRCDIR) -name "*.c")
C_OBJS     := $(C_FILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TREE     := $(sort $(patsubst %/,%,$(dir $(OBJS))))



all: $(TREE) $(OBJS) $(C_OBJS)
#main.exe: $(OBJ_FILES)
#   g++ $(LD_FLAGS) -o $@ $^

#$(warning $(SRCS))
#$(warning $(OBJS))
#$(warning $(TREE))

$(TREE):
	mkdir -p $@

$(OBJDIR)/%.o : %.c 
	${CC} ${CFLAGS} ${INC} -o $@ -c $^

$(OBJDIR)/%.o : %.cpp 
	${CXX} ${CPPFLAGS} ${INC} -o $@ -c $^

clean:
	rm -r $(OBJDIR)/*

force: clean all


$(warning $(TEST_FILES))

test: $(TESTDIR)/KMIPTest

$(TESTDIR)/KMIPTest: $(OBJS) 
	${CXX} ${CPPFLAGS} ${INC} -o $(TESTDIR)/KMIPTest $(C_OBJS) $(OBJS) $(LIBS)

