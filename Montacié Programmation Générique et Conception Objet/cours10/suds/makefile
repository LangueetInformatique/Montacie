CC = g++
CPPFLAGS = -Wall -ansi -pedantic -O3

objects = lcss.o SSTree.o Tools.o CSA.o BitRank.o \
  ReplacePattern.o wtreebwt.o bittree.o rbtree.o CHgtArray.o CRMQ.o \
  SubblockRMQ.o Parentheses.o Hash.o LcpToParentheses.o

all: $(objects)
	ar -q ../suds.a $(objects)

clean:
	rm -f core *.o *~ 

depend:
	g++ -MM *.cpp > dependencies.mk

include dependencies.mk
