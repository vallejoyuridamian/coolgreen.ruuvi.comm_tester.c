mkfile_path := $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
mkfile_dir := $(shell cd $(shell dirname $(mkfile_path)); pwd)

CFLAGS	:= -I$(mkfile_dir)/../lib -Wall -O2 -L$(mkfile_dir)/../lib -Wl,-R$(mkfile_dir)/../lib
LDFLAGS	:= -lgatewayuart -lpthread
REMOBJ	:= comm_tester.o

all: gatewayuartctrl

gatewayuartctrl: $(REMOBJ)
	$(CC) $(CFLAGS) -o gatewayuartctrl $(REMOBJ) $(LDFLAGS)
 
clean:
	rm -f gatewayuartctrl *.o


