CC:=gcc
CFLAGS:=-Wall -Wextra -Wformat=2 -Wundef -Wpointer-arith -Wcast-align\
	    -Wstrict-prototypes -Wwrite-strings -Wswitch-default -Werror\
		-pedantic -std=c11 -g
DEPFLAGS:=-MMD -MP

TST_DIR:=test
SRC:=$(wildcard $(TST_DIR)/*.c)

BDIR:=build
OBJ:=$(patsubst $(TST_DIR)/%.c, $(BDIR)/%.o, $(SRC))
DEP:=$(patsubst $(BDIR)/%.o, $(BDIR)/%.d, $(OBJ))

INCFLAG:=-I$(TST_DIR) -I.
INC:=$(wildcard $(TST_DIR)/*.h) tst_utils.h

.PHONY: test
test: $(OBJ)
	$(CC) $^ -o $(PROG)

.PHONY: clean
clean:
	rm $(BDIR)/*

# Maps all source files to object files, creating the build directory when needed
$(BDIR)/%.o: */%.c
	mkdir -p $(@D)
	$(CC) -c $(INCFLAG) $(DEPFLAGS) $(CFLAGS) $< -o $@ 

# Prevents errors when changing header names
$(INC):

-include $(DEP)
