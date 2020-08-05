mkfile_path := $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
mkfile_dir := $(shell cd $(shell dirname $(mkfile_path)); pwd)

SYSROOT := $(shell $(CC) -print-sysroot)
CFLAGS	+= -I$(mkfile_dir) -I/usr/include -pthread -Wall -c -std=gnu99 -fPIC
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=libgatewayuart.so

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -shared -o $@ $(LDFLAGS) 

.c.o:
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) 

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

