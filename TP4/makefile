# Compilador con sus flags
CC=gcc
CFLAGS= -Wall -pedantic -I$(IDIR)

# Directorios a utilizar
IDIR =./inc
ODIR=obj

# Dependencias
_DEPS = alloc.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Objetos
_OBJ = alloc.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Compila las dependencias
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Compila el programa principal
malloc: malloc.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Elimina los objetos creados
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ malloc
