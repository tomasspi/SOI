#include "alloc.h"

/* Variable inicial */
void *base = NULL;

/**
 * First Fit Malloc:
 * Comienza en la base de la dirección del heap
 * y verifica su tamaño. Si este es útil, devuelve
 * su dirección, sino, sigue buscando. En caso de
 * no encontrar uno bloque adecuado, devuelve NULL.
 */
t_block find_block(t_block *last, size_t size)
{
  t_block b = base;

  while(b && !(b->free && b->size >= size))
  {
    *last = b;
    b = b->next;
  }
  return b;
}

/* Obtiene el bloque a partir de la dirección */
t_block get_block(void *p)
{
  return (t_block) p-1;
}

/**
 * Si el siguiente trozo está libre, se suman los
 * tamaños del trozo actual y siguiente, y el
 * tamaño de la meta-data. Finalmente, reasigna
 * los predecesocer y sucesores.
 */
t_block fusion(t_block b)
{
  if(b->next && b->next->free)
  {
    b->size += BLOCK_SIZE + b->next->size;
    b->next = b->next->next;
    if(b->next)
      b->next->prev = b;
  }
  return (b);
}

/**
 * Añade un nuevo bloque al final del heap.
 */
t_block extend_heap(t_block last, size_t size)
{
  t_block b;
  b = sbrk(0);

  /* si sbrk falla, RIP*/
  if(sbrk(BLOCK_SIZE + size) == (void*)-1)
    return (NULL);

  /*
   * En caso de que sbrk no devuelva el break, se
   * lo guarda y se lo mueve.
   */
  if(last) last->next = b;

  b->size = size;
  b->next = NULL;
  b->prev = last;
  b->free = 0;

  return (b);
}

/**
 * Divide el bloque de acuerdo al tamaño,
 * el bloque 'b' debe existir.
 */
void split_block(t_block b, size_t size)
{
  t_block new = (t_block)(b->data + size);
  int     b_size = b->size;

  /*
   * Si tiene un bloque siguiente, pone el siguiente
   * del nuevo como el siguiente del anterior, y el
   * anterior del siguiente como el nuevo.
   */
  if(b->next)
  {
    new->next = b->next;
    new->next->prev = new;
  }

  b->size   = size;
  b->next   = new;

  new->size = b_size - size - BLOCK_SIZE;
  new->prev = b;
  new->free = 1;
}

/**
 * Primero alinea el tamaño pedido al múltiplo de 4 más
 * cercano. Luego, busca por un tronco de memoria lo
 * suficientemente grande. Si lo encuentra,
 * intenta dividirlo y lo marca como 'usado'.
 * Si no lo encuentra, se extiende el heap. En caso de
 * error se devuelve NULL.
 */
void *mem_alloc(size_t size)
{
  t_block b, last;
  size_t s;
  s = align4(size);

  if(s <= 0) return NULL;

  if(!base)
  {
    b = extend_heap(NULL, size);
    if(!b) return NULL;
    base = b;
  } else {
    last = base;
    b = find_block(&last, size);
    if(!b)
    {
      b = extend_heap(last, size);
      if(!b) return NULL;
    } else {
      if((b->size - size) > BLOCK_SIZE + 4) split_block(b, size);
      b->free = 0;
    }
  }
  return(b+1);
}

/**
 * Si el puntero es válido, se obtiene su dirección y
 * se lo libera. En caso que exista uno previo libre,
 * se lo fusiona.
 * Si no hay más espacio, se vuelve al estado inicial.
 */
void free_mem(void *p)
{
  if(!p) return;

  t_block b;

  b = get_block(p);
  b->free = 1;

  /* Fusiona con el anterior, si es posible */
  if(b->prev && b->prev->free)
    b = fusion(b->prev);
  /* Luego, fusiona con el siguiente */
  if(b->next) b = fusion(b);
  else
  {
    /* Libera el final del heap */
    if(b->prev) b->free = 1;
  }
}

void print_info()
{
  t_block b = base;

  if(b == NULL) return;

  int i = 1;

  while(b != NULL)
  {
    printf("\nBloque %d:\n", i);
    printf(" %s: %ld\n", "Tamaño", b->size);
    printf(" %s: %s\n", "Libre", (b->free) ? "Si" : "No");
    printf(" %s: %p\n", "Dirección", (void*) b);

    i++;
    b = b->next;
  }
}
