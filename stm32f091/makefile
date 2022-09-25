CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OC = arm-none-eabi-objcopy
RM = rm -f

TARGET = main

SHARED_FLAGS += -g
SHARED_FLAGS += -D STM32F091xC
SHARED_FLAGS += -Wall
SHARED_FLAGS += -Wextra
# SHARED_FLAGS += -Wno-register
SHARED_FLAGS += -Wa,--defsym,CALL_ARM_SYSTEM_INIT=1
SHARED_FLAGS += -I./lib/STM32-base-STM32Cube/CMSIS/ARM/inc
SHARED_FLAGS += -I./lib/STM32-base-STM32Cube/CMSIS/STM32F0xx/inc
SHARED_FLAGS += -I./lib/STM32-base/startup
SHARED_FLAGS += -ffunction-sections
SHARED_FLAGS += -fdata-sections
SHARED_FLAGS += -mlittle-endian
SHARED_FLAGS += -mthumb
# SHARED_FLAGS += -masm-syntax-unified
SHARED_FLAGS += -specs=nosys.specs
# SHARED_FLAGS += -fno-threadsafe-statics
# SHARED_FLAGS += -fno-rtti
SHARED_FLAGS += -fno-exceptions
SHARED_FLAGS += -fno-unwind-tables
SHARED_FLAGS += -Wl,-L./lib/STM32-base/linker,-T./lib/STM32-base/linker/STM32F0xx/STM32F091xC.ld
SHARED_FLAGS += -mcpu=cortex-m0
SHARED_FLAGS += -march=armv6-m

CFLAGS += $(SHARED_FLAGS)
LFLAGS += $(SHARED_FLAGS)
AFLAGS += $(SHARED_FLAGS)

OBJS += $(patsubst %.c,%.o, $(wildcard *.c))
OBJS += ./lib/STM32-base/startup/STM32F0xx/STM32F091xC.o
OBJS += ./lib/STM32-base-STM32Cube/CMSIS/STM32F0xx/src/system_stm32f0xx.o

.PHONY: flash clean

$(TARGET).bin: $(TARGET).elf
	$(OC) -O binary $< $@

%.o: %.s
	$(CC) -c $(AFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJS)
	$(LD) $(LFLAGS) $^ -o $@

flash: $(TARGET).bin
	st-flash write $(TARGET).bin 0x08000000

compile_commands: clean
	compiledb make

clean:
	$(RM) $(TARGET).bin $(TARGET).elf $(OBJS)

