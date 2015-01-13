##
## Makefile for module list in /home/mesure_a/workspace/c/modules/list
## 
## Made by arnaud mesureur
## Login   <mesure_a@epitech.net>
## 
## Started on  Fri Mar 11 20:54:20 2011 arnaud mesureur
## Last update Sat Mar 12 17:53:36 2011 arnaud mesureur
##

# \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
#		** VARIABLES **
# //////////////////////////////////////////////////


SHELL	:=	/bin/sh


# //////////////////////////////////////////////////
# ** Directories & Path

SRCDIR		:=	src
HDRDIR		:=	inc
OBJDIR		:=	obj

VPATH		:=	$(SRCDIR):$(HDRDIR)


# //////////////////////////////////////////////////
# ** Compiler Configurations

CC		:=	gcc
CFLAGS		+=	-Wall -Wextra
CFLAGS		+=	$(INCLUDE)
CFLAGS		+=	$(if $(XF), $(XFLAGS),)
CFLAGS		+=	$(if $(DF), $(DFLAGS), $(OFLAGS))

XFLAGS		=	-Wunreachable-code
XFLAGS		+=	-Wstrict-prototypes -Wpointer-arith
XFLAGS		+=	-Wcast-qual -Wcast-align

DFLAGS		+=	-ggdb -DDEBUG_
OFLAGS		+=	-O3

INCLUDE		:=	-I. -I$(HDRDIR)

LDFLAGS		:=	-shared


# //////////////////////////////////////////////////
# ** Archiver Configurations

AR		:=	ar r
RANLIB		:=	ranlib


# //////////////////////////////////////////////////
# **  sources

LIB_STATIC	:=	liblist.a
LIB_SHARED	:=	liblist.so
SRCS		:=	list.c	\
			item.c
OBJS		=	$(SRCS:%.c=$(OBJDIR)/%.o)

HDRS		:=	list.h	\
			item.h


# \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
#		*** RULES ***
# //////////////////////////////////////////////////


all		: $(LIB_STATIC) $(LIB_SHARED)

$(LIB_STATIC)	: $(OBJS)
		$(AR) $(LIB_STATIC) $(OBJS)
		$(RANLIB) $(LIB_STATIC)

$(LIB_SHARED)	: $(OBJS)
		$(CC) $(LDFLAGS) -o $(LIB_SHARED) $(OBJS)

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(LIB_STATIC) $(LIB_SHARED)

re		: fclean all

.SUFFIXES	:
.SUFFIXES	: .c .o

$(OBJDIR)/%.o	: %.c
		$(CC) $(CFLAGS) -o $@ -c $<

.PHONY		: all clean fclean re
