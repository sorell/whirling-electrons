CC := sdcc
CFLAGS ?= -mstm8 --std-sdcc99
LDFLAGS ?= -mstm8
OBJDIR ?= obj

INCFLAGS := $(foreach d, $(INCDIR), -I$d)
OBJECTS := $(foreach d, $(SOURCES:.c=.rel), $(OBJDIR)/$(notdir $d))


$(TARGET): $(OBJDIR) $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

$(OBJDIR)/%.rel: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: flash
flash:
	stm8flash -c stlinkv2 -p stm8l101f3 -w $(TARGET)
	stm8flash -c stlink -p stm8l101f3 -w $(TARGET)

.PHONY: clean
clean:
	rm -fr $(OBJDIR)/ $(basename $(TARGET)).*
