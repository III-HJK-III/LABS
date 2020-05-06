#
#	DKU Operating System Lab
#	    Lab2 (BST Synchronization)
#	    Student id : 32160320
#	    Student name : Kwon Hyeok Jun
#
#   Makfeile :
#       - Makefile for lab2 compilation.
#

CC = gcc
CFLAGS = -g
LDFLAGS = -lpthread
STD = -std=$(STANDARD)
STANDARD = c11

OBJS_LAB2 = bst.o insert.o remove.o seach.o main.o

SRCS = $(OBJS_LAB2:.o=.c)

TARGET_LAB2 = lab2_bst

.SUFFIXES : .c .o

.c.o:
	@echo "Compilingi lab2 BST synchronization $< ..."
	$(CC) -c $(CFLAGS) -o $@ $<

$(TARGET_LAB2) : $(OBJS_LAB2)
	$(CC) -o $(TARGET_LAB2) $(OBJS_LAB2) $(LDFLAGS) $(STD)

all : $(TARGET_LAB2)

dep : 
	gccmaedep $(INC) $(SRCS)

clean :
	@echo "Cleaning lab2 BST synchronization $< ..."
	rm -rf $(OBJS_LAB2) $(TARGET_LAB2)

new :
	$(MAKE) clean
	$(MAKE)
