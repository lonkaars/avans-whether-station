all: client stm32

clean:
	make -C client clean
	make -C stm32f091 clean

client_makefile:
	qmake client/client.pro -o client/makefile

client: client_makefile
	make -C client

client_compile_commands: client_makefile
	compiledb -o client/compile_commands.json make -C client

stm32:
	make -C stm32f091
