# Universidad Nacional De Córdoba
## Facultad de Ciencias Exactas, Físicas y Naturales
### Sistemas Operativos I
#### Trabajo Práctico N° 4: malloc
------
#### Piñero, Tomás Santiago - Año 2019
------

#### Objetivos
Con el desarrollo del siguiente Trabajo Práctico (TP), se busca implementar la asignación y liberación de memoria dinámica, la cual se reserva en tiempo de ejecución.

#### Desarrollo

- *void *mem_alloc(size_t size)*: reserva un bloque de memoria mediante la técnica *first fit*, y devuelve un puntero void al inicio del mismo.

 El parámetro *size* especifica el número de *bytes* a reservar. En caso de que no se pueda realizar la asignación, devuelve *NULL*.

- *void *free_mem(void *ptr)*: libera la memoria que se asignó. Si el puntero es nulo, la función no hace nada. El parámetro *ptr* es el puntero a la memoria que se desea liberar.

 Una vez liberada la memoria, si se quiere volver a utilizar el puntero, se debe utilizar nuevamente la función *mem_alloc*.

#### Compilación y ejecución del proyecto

1. Ir al directorio donde se encuentra el proyecto, por ejemplo:

```shell
 $ cd Documentos/malloc
```

2. Compilarlo con el siguiente comando:

```shell
  $ make
```

3. Ejecutarlo:

```shell
  $ ./malloc
```

4. Si se desea eliminar los archivos generados por el *makefile*, simplemente ingresar en consola:

```shell
  $ make clean
```
