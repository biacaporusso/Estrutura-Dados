#nome do projeto
PROJETO = t2

#arquivos .c
ARQUIVOS_C = $(wildcard *.c)

#wildcard é usado para listar todos os arquivos-fonte no diretório atual

#arquivos .h
ARQUIVOS_H = $(wildcard *.h)

#gera a lista de arquivos-objeto usando a lista de arquivos-fonte
OBJ = $(ARQUIVOS_C:.c=.o)

#compilador
CC = gcc

#flags para o compilador
FLAGS = -Wall -ansi -pedantic -std=c99 -fstack-protector-all -g

#-w : omite todas as mensagens de advertência da compilação.
#-Wall: ativa vários avisos que não são ativados normalmente. Pode dar alguns conselhos úteis.
#-ansi: compila seu programa estritamente de acordo com o padrão ANSI, desativando qualquer extensão específica do gcc.
#-pedantic: ativa alguns avisos que existem de acordo com o padrão C mas que são desativados normalmente por extensões do gcc.
#-o: tells the compiler to save the compiled program under the name . So, typing "gcc myfile.c -o myfile.x" will take the source code of file "myfile.c" and create program "myfile.x" rather than the default program "a.out".
#-g: inclui no arquivo executável os elementos utilizados pelos programas de depuração, como o gdb ou ddd.
#-o1, -o2, -o3: esses parâmetros realizam otimizações para melhorar o desempenho da execução do código. Variam de 1 a 3, sendo 3 o melhor processo de otimização.

#ligação com as bibliotecas
LINKER_FLAGS = -lm

#linking e compilaçao

all: $(PROJETO)

$(PROJETO): $(OBJ)
	$(CC) -o $@ $^ $(FLAGS) $(LINKER_FLAGS)

%.o: %.c %.h
	$(CC) -o $@ $< -c $(FLAGS) $(LINKER_FLAGS)

main.o: main.c $(ARQUIVOS_H)
	$(CC) -o $@ $< -c $(FLAGS)

clean:
	rm -rf *.o $(PROJETO) *~

run: $(PROJETO)
	./$(PROJETO)

#$@ (full target name of the current target)
#$? (returns the dependencies that are newer than the current target)
#$* (returns the text that corresponds to % in the target)
#$< (name of the first dependency)
#$^ (name of all the dependencies with space as the delimiter)
#when the % character can be used for wildcard pattern-matching, to provide generic targets
