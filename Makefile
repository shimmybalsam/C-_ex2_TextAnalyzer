CC = g++
CCFLAGS = -c -Wall -std=c++14
LDFLAGS = -lm

# add your .cpp files here  (no file suffixes)
CLASSES = ex2 TextAnalyzer

# Prepare object and source file list using pattern substitution func.
OBJS = $(patsubst %, %.o,  $(CLASSES))
SRCS = $(patsubst %, %.c, $(CLASSES))

all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o find_the_author

%.o: %.c
	$(CC) $(CCFLAGS) $*.c

depend:
	makedepend -- $(CCFLAGS) -- $(SRCS)
# DO NOT DELETE
