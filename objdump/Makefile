##
## Makefile for nm in /home/mesure_a/workspace/c/nm-objdump/nm
## 
## Made by arnaud mesureur
## Login   <mesure_a@epitech.net>
## 
## Started on  Tue Mar  1 18:02:17 2011 arnaud mesureur
## Last update Sun Mar 13 22:31:04 2011 arnaud mesureur
##


# \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
#		** VARIABLES **
# //////////////////////////////////////////////////


SHELL	:=	/bin/sh


# //////////////////////////////////////////////////
# ** Directories & Path

SRCDIR	:=	src
HDRDIR	:=	inc
LIBDIR	:=	lib
OBJDIR	:=	obj

VPATH	:=	$(SRCDIR):$(HDRDIR):$(LIBDIR)


# //////////////////////////////////////////////////
# ** Compiler Configurations

CC	:=	gcc
CFLAGS	+=	-Wall -Wextra -ansi
CFLAGS	+=	$(INCLUDE)
CFLAGS	+=	$(if $(XF), $(XFLAGS),)
CFLAGS	+=	$(if $(DF), $(DFLAGS), $(OFLAGS))

XFLAGS	=	-Wunreachable-code
XFLAGS	+=	-Wstrict-prototypes -Wpointer-arith
XFLAGS	+=	-Wcast-qual -Wcast-align

DFLAGS	+=	-ggdb -DDEBUG_
OFLAGS	+=	-O3

INCLUDE	:=	-I. -I$(HDRDIR)

# LDFLAGS	:=	-L$(LIBDIR) -llist

# //////////////////////////////////////////////////
# ** sources

NAME	:=	my_objdump
SRCS	:=	objdump.c		\
		map_file.c		\
		init_elf_data.c		\
		check_file_format.c	\
		main.c
OBJS	:=	$(SRCS:%.c=$(OBJDIR)/%.o)

HDRS	:=	objdump.h


# //////////////////////////////////////////////////
# ** modules

LIST	:=	liblist.a
LISTDIR	:=	list



# //////////////////////////////////////////////////
# ** tools

CP	:=	cp


# \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
#		*** RULES ***
# //////////////////////////////////////////////////


$(NAME)		: $(OBJS) $(HDRS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(LIST)		:
		$(MAKE) -C $(LIBDIR)/$(LISTDIR)
		$(CP) $(LIBDIR)/$(LISTDIR)/$(LIST) $(LIBDIR)

list		:
		$(RM) $(LIBDIR)/$(LIST) $(LIBDIR)/$(LISTDIR)/$(LIST)
		$(MAKE) -C $(LIBDIR)/$(LISTDIR) re
		$(CP) $(LIBDIR)/$(LISTDIR)/$(LIST) $(LIBDIR)

all		: $(NAME)

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAME)

re		: fclean all

.SUFFIXES	:
.SUFFIXES	: .c .o

$(OBJDIR)/%.o	: %.c
		$(CC) $(CFLAGS) -o $@ -c $<

.PHONY		: all clean fclean re list
