LINK_TARGET = ted
OBJECTS = main.o parametros.o arvore.o geo.o figuras.o svg.o system.o qry.o

# Make Macro defined by 3 macro expansions
REBUILDABLES = $(OBJECTS)

all: $(LINK_TARGET)
	echo All done

# Dependencies
main.o: parametros.h system.h
parametros.o: parametros.h
arvore.o: arvore.h
geo.o: geo.h figuras.h arvore.h
figuras.o: figuras.h
svg.o: svg.h figuras.h arvore.h
system.o: system.h arvore.h geo.h svg.h parametros.h qry.h
qry.o: qry.h arvore.h svg.h

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

run:
	./$(LINK_TARGET) -e /home/vfsilva/estudo/repositories/Projeto2/src/entrada -o /home/vfsilva/estudo/repositories/Projeto2/src/saidas -f 01-int-05.geo -q 01-int-05/007-muitas-bomb.qry