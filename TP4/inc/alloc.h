#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/*
 * Declaración del bloque de memoria.
 */
struct mem_block
{
  size_t               size;
  struct mem_block    *next;
  struct mem_block    *prev;
  int                  free;
  /* Puntero al bloque asignado */
  char                 data[1];
};
typedef struct mem_block *t_block;

/* Dado que 'sizeof' falla, se define un tamaño */
#define BLOCK_SIZE sizeof(struct mem_block)
/* Macro para alinear los punteros */
#define align4(x) (((((x)-1)>>2)<<2)+4)

t_block find_block(t_block *last, size_t size);
t_block get_block(void *p);
t_block fusion(t_block b);
t_block extend_heap(t_block last, size_t size);
void    split_block(t_block b, size_t size);
void    *mem_alloc(size_t size);
void    free_mem(void *p);
void    print_info();
