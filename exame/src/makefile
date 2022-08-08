LINK_TARGET = ted

OBJECTS = main.o parametros.o listadinamica.o geo.o svg.o figuras.o qry.o fila.o yxxtree.o paramqry.o

# Make Macro defined by 3 macro expansions
REBUILDABLES = $(OBJECTS)

all: $(LINK_TARGET)
	echo All done

# Dependencies
main.o: parametros.h figuras.h lista.h geo.h svg.h qry.h yxxtree.h 
parametros.o: parametros.h
listadinamica.o: lista.h
geo.o: geo.h figuras.h lista.h yxxtree.h
svg.o: svg.h geo.h figuras.h lista.h 
figuras.o: figuras.h
qry.o: qry.h yxxtree.h figuras.h svg.h fila.h
fila.o: fila.h
yxxtree.o: yxxtree.h lista.h fila.h figuras.h
paramqry.o: paramqry.h 

$(LINK_TARGET): $(OBJECTS) 
# $@ expands to the rule's target (LINK_TARGET)
# $^ expands to the rule's dependencies (OBJECTS)
# Note that -lm is used because of the dependency on math.h
# gcc -fstack-protector-all -std=c99 -g -o $@ $^ -lm
	gcc -std=c99 -Wall -o $@ $^ -lm

%.o : %.c
# $@ for the pattern-matched target
# $< for the pattern-matched dependency
# gcc -fstack-protector-all -std=c99 -g -o $@ -c $<
	gcc -std=c99 -Wall -g -o $@ -c $<
# Cleaning build environment
clean:
# -f forced deletion 
# -i interacts with the user
# -r recursive removal
# -rf (DO NOT USE!)
# touch is just to prevent error message when file doesn’t exist
	touch $(REBUILDABLES)
	rm $(REBUILDABLES)
	echo done cleaning
	