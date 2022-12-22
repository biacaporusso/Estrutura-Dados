ALUNO=beatrizbc
LINK_TARGET = ted

OBJECTS = figures.o geo.o main.o parameters.o qry.o SRBtree.o svg.o system.o list.o

# Make Macro defined by 3 macro expansions
REBUILDABLES = $(OBJECTS)

all: $(LINK_TARGET)
	echo All done

# Dependencies
figures.o: figures.h
geo.o: geo.h SRBtree.h figures.h
main.o: system.h
parameters.o: parameters.h 
qry.o: qry.h figures.h SRBtree.h
svg.o: svg.h geo.h figures.h SRBtree.h
system.o: system.h SRBtree.h geo.h parameters.h svg.h
list.o: list.h

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
	
pack: $(LINK_TARGET)
	rm -f ../$(ALUNO).zip
	echo $(ALUNO)
	date >> .entrega
	cd ..; zip $(ALUNO).zip -r src/*.c src/*.h src/makefile LEIA-ME.txt .entrega
