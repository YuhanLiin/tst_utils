CC?=gcc
CFLAGS:=-Wall -Wextra -Wformat=2 -Wundef -Wpointer-arith -Wcast-align\
		-Wstrict-prototypes -Wwrite-strings -Wswitch-default -Werror\
		-Wshadow -pedantic -std=c99 -O2 -g
DEPFLAGS:=-MMD -MP

TST_DIR:=test
SRC:=$(wildcard $(TST_DIR)/*.c)

BDIR:=build
OBJ:=$(patsubst $(TST_DIR)/%.c, $(BDIR)/%.o, $(SRC)) $(BDIR)/tst_utils.o
DEP:=$(patsubst $(BDIR)/%.o, $(BDIR)/%.d, $(OBJ))

O_PASS:=$(BDIR)/main.o
O_FAIL:=$(BDIR)/fail_main.o
O_XPASS:=$(BDIR)/xpass_main.o
O_MAINS:=$(O_PASS) $(O_FAIL) $(O_XPASS)

# Redefine OBJ as all object files except for the ones with main()
OBJ:=$(filter-out $(O_MAINS), $(OBJ))

INCFLAG:=-I$(TST_DIR) -I.
INC:=$(wildcard $(TST_DIR)/*.h) tst_utils.h

PROG_MAIN:=$(BDIR)/main
PROG_FAIL:=$(BDIR)/fail
PROG_XPASS:=$(BDIR)/xpass

# Actually run all tests. If make finishes successfully, then the tests pass
.PHONY: all
all: $(PROG_FAIL) $(PROG_MAIN) $(PROG_XPASS)
	./$(PROG_MAIN)
	./check_fail.sh $(PROG_FAIL)
	./check_fail.sh $(PROG_XPASS)

$(PROG_MAIN): $(OBJ) $(O_PASS)
	$(CC) $^ -o $@

$(PROG_FAIL): $(OBJ) $(O_FAIL)
	$(CC) $^ -o $@

$(PROG_XPASS): $(OBJ) $(O_XPASS)
	$(CC) $^ -o $@

.PHONY: clean
clean:
	rm $(BDIR)/*

VPATH:=test .

# Maps all source files to object files, creating the build directory when needed
$(BDIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) -c $(INCFLAG) $(DEPFLAGS) $(CFLAGS) $< -o $@

# Prevents errors when changing header names
$(INC):

-include $(DEP)
