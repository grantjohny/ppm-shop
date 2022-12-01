#CONFIG
CC=gcc
CFLAGS=-Wall -g
LFLAGS=-lm
TARGET=ppm-shop

#Generate source and object lists, also just string variables
C_SRCS := \
	$(wildcard *.c) \
	$(wildcard PA1Files/*.c) \
	$(wildcard PA1Files/**/*.c)

HDRS := \
       	$(wildcard *.h) \
	$(wildcard PA1Files/*.h) \
	$(wildcard PA1Files/**/*.h)

OBJS := $(patsubst %.c, bin/%.o, $(wildcard *.c))
OBJS += $(filter %.o, $(patsubst src/%.c, bin/%.o, $(C_SRCS)))


all: build
	@echo "All Done"


#Link all  built objects
build: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)


#Catch root ridrectory src files
bin/%.o: %.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


#Catch all nested directory files
bin/%.c: src%.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(TARGET)
	rm -rd bin

run: build
	./$(TARGET) ClemsonPaw.ppm Disney.ppm

which:
	
		@echo "FOUND SOURCES: ${C_SRCS}"
		@echo "FOUND HEADERS: ${HDRS}"
		@echo "TARGET OBJS: ${OBJS}"
