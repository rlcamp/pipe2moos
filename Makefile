# prior to attempting this Makefile, run the following to satisfy the core-moos dependency:
# cd ..
# git clone --depth 1 https://github.com/themoos/core-moos.git
# cd core-moos
# cmake -DCMAKE_INSTALL_PREFIX:PATH=build .
# make -j4
# make install
# cd ../moosline

# if you ever see a segfault or other unexpected nondeterminism in this (or any other) code,
# the immediate muscle memory response should be to recompile with the following, and then
# rerun the failing use case:
# make clean && make CFLAGS="-Og -g -fno-inline -fsanitize=address,undefined"

CFLAGS ?= -Os

LDFLAGS+=${CFLAGS}
CPPFLAGS += -Wall -Wextra -Wshadow -Wmissing-prototypes

# override this if necessary when invoking make
MOOS_INSTALL_PREFIX=../core-moos/build/

CXXFLAGS+=${CFLAGS}
CXXFLAGS += -std=c++0x -Wno-implicit-fallthrough -Wno-deprecated-declarations
CXXFLAGS += -I${MOOS_INSTALL_PREFIX}/include/

TARGETS=moos2pipe pipe2moos

all : ${TARGETS}

moos2pipe pipe2moos : LDFLAGS+=-L${MOOS_INSTALL_PREFIX}/lib/
moos2pipe pipe2moos : LDLIBS?=-lMOOS -lstdc++ -lpthread -lm

moos2pipe : moos2pipe.o
pipe2moos : pipe2moos.o

clean :
	${RM} *.o ${TARGETS}

*.o : Makefile
