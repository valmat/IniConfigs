# CC 	 = clang++
CC 	 = g++

NAME	 = libiniconfig

OPT_FLAGS = -O3

#compiler flags
CPP_FLAGS  = -std=c++17 ${OPT_FLAGS} -I. -I../include -fPIC -c -pedantic -Wall -Wextra -fno-rtti -fno-exceptions
LD_FLAGS   = -std=c++17 ${OPT_FLAGS} -shared

CP  = cp -f
CPR = cp -fR
#CPR = ln -sf
#CP  = ln -sf
SRC = `pwd`

ifeq ($(BUILD),lto)   
	CPP_FLAGS := ${CPP_FLAGS} -flto
	LD_FLAGS  := ${LD_FLAGS} -flto
endif

SOURCES    = $(wildcard *.cpp)
OBJECTS    = $(SOURCES:%.cpp=o/%.tmp.o)

all: obj
	$(CC) $(LD_FLAGS) -o $(NAME).so $(OBJECTS)
	ar rs $(NAME).a $(OBJECTS)
	@echo
	@echo "\033[1;33mBuild complite\033[0m"

.PHONY: clean install uninstall uninstall-clean lto

lto:
	make "BUILD=lto" -j`nproc`

fast:
	make -j`nproc`


o/IniConfigs.tmp.o: IniConfigs.cpp
	$(CC) IniConfigs.cpp $(CPP_FLAGS) -c -o o/IniConfigs.tmp.o

o/IniValue.tmp.o: IniValue.cpp
	$(CC) IniValue.cpp   $(CPP_FLAGS) -c -o o/IniValue.tmp.o

.PHONY: obj
obj: $(OBJECTS)


clean:
	rm -f o/*.o *.a *.so

install:
	$(CP) ${SRC}/libiniconfig.so /usr/local/lib/libiniconfig.so
	$(CP) ${SRC}/libiniconfig.a  /usr/local/lib/libiniconfig.a
	ldconfig
	#
	mkdir -p /usr/local/include/vlm/iniconfigs
	$(CPR) ${SRC}/../include/* /usr/local/include/vlm/iniconfigs/

uninstall:
	rm -rf /usr/local/include/vlm/iniconfigs
	rm -f /usr/local/lib/libiniconfig.so
	rm -f /usr/local/lib/libiniconfig.a
