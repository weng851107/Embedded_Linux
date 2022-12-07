TARGET  = output
SRC_DIR = ./
INC_DIR = ./

CFLAGS += -I$(INC_DIR)
SRC     = $(wildcard $(SRC_DIR)*.c)
OBJ     = $(SRC:%.c=%.o) #$(patsubst %.c, %.o, $(SRC))
DEP     = $(SRC:%.c=%.d) #$(patsubst %.o, %.d, $(OBJ))

.PHONY: clean

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Include all .d files
-include $(DEP)

# Build target for every single object file.
# The potential dependency on header files is covered by calling `-include $(DEP)`.
%.o : %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

## clean
clean:
	rm -f $(TARGET) $(OBJ) $(DEP)
