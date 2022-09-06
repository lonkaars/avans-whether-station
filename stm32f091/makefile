CC = arm-none-eabi-g++
LD = arm-none-eabi-g++
OC = arm-none-eabi-objcopy
RM = rm -f

TARGET = main
MCU_SPEC = cortex-m0

CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Os
CFLAGS += -mcpu=$(MCU_SPEC)
CFLAGS += -mthumb
CFLAGS += --specs=nosys.specs
CFLAGS += -I./lib/STM32CubeF0/Drivers/CMSIS/DSP/Include
CFLAGS += -I./lib/STM32CubeF0/Drivers/CMSIS/Core/Include
CFLAGS += -I./lib/STM32CubeF0/Drivers/CMSIS/Device/ST/STM32F0xx/Include
CFLAGS += -I./lib/STM32CubeF0/Drivers/CMSIS/RTOS2/Include
CFLAGS += -I./lib/STM32CubeF0/Drivers/CMSIS/Core_A/Include
CFLAGS += -I./lib/STM32CubeF0/Drivers/CMSIS/Include
CFLAGS += -I./lib/STM32CubeF0/Drivers/CMSIS/NN/Include
CFLAGS += -I./lib/STM32-base/startup
CFLAGS += -D STM32F091xC

LFLAGS += -Wl,-u,vfprintf
LFLAGS += -lm
LFLAGS += -Wl,-relax
LFLAGS += -Wl,-gc-sections
LFLAGS += -mcpu=$(MCU_SPEC)
LFLAGS += -mthumb
LFLAGS += -Wall
LFLAGS += --specs=nosys.specs
LFLAGS += -nostartfiles
LFLAGS += -nostdlib
LFLAGS += -lgcc
LFLAGS += -Wl,-L./lib/STM32-base/linker,-T./lib/STM32-base/linker/STM32F0xx/STM32F091xC.ld

LFLAGS += -Wa,--defsym,CALL_ARM_SYSTEM_INIT=1
LFLAGS += -march=armv6-m
LFLAGS += -mlittle-endian
LFLAGS += -mthumb
LFLAGS += -masm-syntax-unified
LFLAGS += -fno-threadsafe-statics
LFLAGS += -fno-rtti
LFLAGS += -fno-exceptions
LFLAGS += -fno-unwind-tables

# AFLAGS += -ffunction-sections -fdata-sections

SRCS += $(wildcard *.cpp)
OBJS += $(patsubst %.cpp,%.o, $(SRCS))

# SRCS += ./lib/STM32-base/startup/STM32F0xx/STM32F091xC.s
SRCS += ./lib/STM32CubeF0/Drivers/CMSIS/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.o
OBJS += ./lib/STM32-base/startup/STM32F0xx/STM32F091xC.o

%.o: %.s
	$(CC) -x assembler-with-cpp -c $(CFLAGS) $(AFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJS)
	$(LD) $^ $(LFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OC) -O binary $< $@

flash: $(TARGET).bin
	st-flash write $(TARGET).bin 0x08000000

compile_commands: clean
	compiledb make

clean:
	$(RM) $(TARGET).bin $(TARGET).elf $(OBJS)

