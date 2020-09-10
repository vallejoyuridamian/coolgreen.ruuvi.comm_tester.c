CXX=gcc

PROJ_DIR := src
PROJ_OUTPUT_DIR := output

RUUVI_APP_SOURCES= \
  $(PROJ_DIR)/app/comm_tester.c

RUUVI_LIB_SOURCES= \
  $(PROJ_DIR)/lib/api.c \
  $(PROJ_DIR)/lib/parser.c \
  $(PROJ_DIR)/lib/dbuscontroller.c \
  $(PROJ_DIR)/lib/formated_output.c \
  $(PROJ_DIR)/ruuvi.endpoints.c/src/ruuvi_endpoint_ca_uart.c

RUUVI_DRV_SOURCES= \
  $(PROJ_DIR)/drv/terminal.c

RUUVI_PRJ_SOURCES= \
  $(RUUVI_APP_SOURCES) \
  $(RUUVI_DRV_SOURCES) \
  $(RUUVI_LIB_SOURCES)

COMMON_INCLUDES= \
  /usr/include \
  /usr/include/dbus-1.0 \
  /usr/lib/x86_64-linux-gnu/dbus-1.0/include \
  $(PROJ_DIR) \
  $(PROJ_DIR)/app \
  $(PROJ_DIR)/lib \
  $(PROJ_DIR)/drv \
  $(PROJ_DIR)/ruuvi.endpoints.c/src/

CFLAGS  = -c -Wall -pedantic -Wno-variadic-macros -Wno-long-long -Wno-shadow -std=c11
LDFLAGS= -lpthread -ldbus-1
DFLAGS= -D_BSD_SOURCE
INCLUDES=${COMMON_INCLUDES}
INC_PARAMS=$(foreach d, $(INCLUDES), -I$d)
SOURCES=${RUUVI_PRJ_SOURCES}
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=ruuvi_comm_tester

# Tag on this commit
TAG := $(shell git describe --tags --exact-match)
# Commit hash from git
COMMIT := $(shell git rev-parse --short HEAD)
VERSION := $(if $(TAG),$(TAG),$(COMMIT))

.PHONY: clean all

all: $(SOURCES) $(EXECUTABLE)  

$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(PROJ_OUTPUT_DIR)
	$(CXX) $(OBJECTS) -o $(PROJ_OUTPUT_DIR)/$@ $(LDFLAGS)

.c.o:
	$(CXX) $(CFLAGS) $< $(DFLAGS) $(INC_PARAMS) $(OFLAGS) -o $@

clean:
	rm -f $(OBJECTS) $(IOBJECTS) $(POBJECTS)
	rm -rf $(PROJ_OUTPUT_DIR)
