OBJS += $(patsubst %.c,%-stm.o, $(wildcard ../shared/*.c))
