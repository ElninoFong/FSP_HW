# makefile to build library and testdriver
.SUFFIXES:.cc
.cc.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@ -w

# assign your compiler name to CC if not g++
CC = g++
# where your header files are (. is same directory as the makefile)
INCLUDES=-I.
# turn on debugging symbols
CFLAGS=-g
# where your object files are (. is the same directory as the makefile)
LDFLAGS=-L.

# when "make" is typed at command line with no args "default" will get executed and do "all"
default: 	all

#
# assign source and headers for our "utility" lib to variables below
#
# replace "SBB" (my initials) with yours or use the same filenames
LIB_UTIL_SRC = SBB_util.cc
LIB_UTIL_SRC_HDR = SBB_util.h

LIB_DATE_SRC = SBB_date.cc
LIB_DATE_SRC_HDR = SBB_date.h

LIB_IO_SRC = SBB_io.cc
LIB_IO_SRC_HDR = SBB_io.h

LIB_RATINGS_SRC = SBB_ratings.cc
LIB_RATINGS_HDR = SBB_ratings.h

#
LIB_UTIL_OBJ = $(LIB_UTIL_SRC:.cc=.o) $(LIB_DATE_SRC:.cc=.o) $(LIB_IO_SRC:.cc=.o) $(LIB_RATINGS_SRC:.cc=.o)
$(LIB_UTIL_OBJ) : $(LIB_UTIL_SRC_HDR) $(LIB_DATE_SRC_HDR) $(LIB_IO_SRC_HDR) $(LIB_RATINGS_SRC_HDR)
LIB_UTIL_TARGET = libutil.a

LIB_CAL_SRC = Calculator.cc
LIB_CAL_SRC_HDR = Calculator.h

LIB_BOND_SRC = Bond.cc
LIB_BOND_SRC_HDR = Bond.h

LIB_TB_SRC = TB_Collection.cc
LIB_TB_SRC_HDR = TB_Collection.h

LIB_YC_SRC = YieldCurve.cc
LIB_YC_SRC_HDR = YieldCurve.h

#
LIB_TB_OBJ = $(LIB_TB_SRC:.cc=.o) $(LIB_CAL_SRC:.cc=.o) $(LIB_BOND_SRC:.cc=.o) $(LIB_YC_SRC:.cc=.o)
$(LIB_TB_OBJ) : $(LIB_TB_SRC_HDR) $(LIB_CAL_SRC_HDR) $(LIB_BOND_SRC_HDR) $(LIB_YC_SRC_HDR)
LIB_TB_TARGET = libtb.a

#=============
# 
# the file where main() is
MAIN_SRC = mmain.cc
MAINOBJ = $(MAIN_SRC:.cc=.o) 
$(MAINOBJ) : $(LIB_UTIL_TARGET) $(LIB_TB_TARGET)
MAINTARGET=testdriver

ARCHIVE_OPTIONS = rucsv

$(LIB_UTIL_TARGET) : $(LIB_UTIL_OBJ)
	ar $(ARCHIVE_OPTIONS) $(LIB_UTIL_TARGET) $(LIB_UTIL_OBJ)

$(LIB_TB_TARGET) : $(LIB_TB_OBJ)
	ar $(ARCHIVE_OPTIONS) $(LIB_TB_TARGET) $(LIB_TB_OBJ)

$(MAINTARGET) : $(MAINOBJ) $(LIB_UTIL_TARGET) $(LIB_TB_TARGET)
	$(CC) $(LDFLAGS) $(MAINOBJ) $(LIB_UTIL_TARGET) $(LIB_TB_TARGET) -o $(MAINTARGET)

all : util libtb test

test: $(MAINTARGET)

util: $(LIB_UTIL_TARGET)

libtb: $(LIB_TB_TARGET)

clean:
	rm -f *.o 

clobber:
	-rm -f *.o *.a $(MAINTARGET)

backup: clobber
	tar cvf ./nyu.tar *.*
