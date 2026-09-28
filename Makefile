CC ?= riscv64-linux-gnu-gcc
CFLAGS = -Wall -g
LDFLAGS ?=

TARGET = ledblink
OBJS = main.o

USERNAME = root
TARGET_IP = 10.42.0.104
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

install:
	install -d $(DESTDIR)$(bindir)
	install -m 0755 $(TARGET) $(DESTDIR)$(bindir)

scp:
	scp $(TARGET) $(USERNAME)@$(TARGET_IP):/$(USERNAME)/exec/

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean install
