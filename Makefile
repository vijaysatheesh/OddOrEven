CC ?= riscv64-linux-gnu-gcc-13
CFLAGS ?= -Wall -g
LDFLAGS ?=

TARGET = helloworld
OBJS = main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

install:
	install -d $(DESTDIR)$(bindir)
	install -m 0755 $(TARGET) $(DESTDIR)$(bindir)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean install