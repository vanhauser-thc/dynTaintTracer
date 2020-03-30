CFLAGS=-Wno-pointer-to-int-cast -O3
TYPE=$(`uname -m`)

all:	test
	mkdir -p build
	cd build && cmake .. -DDynamoRIO_DIR="$(DYNAMORIO_HOME)/cmake" && make

test:	test.c
	echo $(TYPE)
	gcc -o test test.c

install: all
	install -d /usr/local/lib/dynamorio
	install build/libmyTaintTracer.so /usr/local/lib/dynamorio
	install myTaintTracer.sh /usr/local/bin

save:	all
	mkdir -p bin/`uname -m`
	cp -v build/libmyTaintTracer.so bin/`uname -m`
	-@svn add bin/`uname -m` 2> /dev/null
	-@svn add bin/`uname -m`/*.so 2> /dev/null
	-svn commit -m "`uname -m`"

clean:
	rm -rf build test
