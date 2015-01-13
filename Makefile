##
## Makefile for nm in /home/mesure_a/workspace/c/nm-objdump/nm
## 
## Made by arnaud mesureur
## Login   <mesure_a@epitech.net>
## 
## Started on  Tue Mar  1 18:02:17 2011 arnaud mesureur
## Last update Sun Mar 13 15:42:47 2011 arnaud mesureur
##


# \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
#		** VARIABLES **
# //////////////////////////////////////////////////

SHELL	:=	/bin/sh


# //////////////////////////////////////////////////
# ** Directories & Path

NM		:=	my_nm
OBJDUMP		:=	my_objdump

NM_DIR		:=	nm
OBJDUMP_DIR	:=	objdump


# //////////////////////////////////////////////////
# ** tools

CP	:=	cp


# \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
#		*** RULES ***
# //////////////////////////////////////////////////

all		: $(NM) $(OBJDUMP)

$(NM)		:
		$(MAKE) -C $(NM_DIR)
		-$(CP) $(NM_DIR)/$(NM) .

$(OBJDUMP)	:
		$(MAKE) -C $(OBJDUMP_DIR)
		-$(CP) $(OBJDUMP_DIR)/$(OBJDUMP) .

clean		:
		$(MAKE) -C $(NM_DIR) clean
		$(MAKE) -C $(OBJDUMP_DIR) clean

fclean		:
		$(MAKE) -C $(NM_DIR) fclean
		$(MAKE) -C $(OBJDUMP_DIR) fclean
		$(RM) $(NM)
		$(RM) $(OBJDUMP)

re		:
		$(RM) $(NM)
		$(RM) $(OBJDUMP)
		$(MAKE) -C $(NM_DIR) re
		$(MAKE) -C $(OBJDUMP_DIR) re
		-$(CP) $(NM_DIR)/$(NM) .
		-$(CP) $(OBJDUMP_DIR)/$(OBJDUMP) .

.PHONY	: all clean fclean re