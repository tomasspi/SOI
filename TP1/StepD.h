#include "StepA.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void file_descriptors(int pid);
void limits(int pid);
void stack(int pid);

/*
 * Muestra los permisos, el tipo de archivo y el path de los file
 * descriptors del proceso.
 * @param pid - process id del cual se desea obtener la información.
 */
void file_descriptors(int pid)
{
  DIR *descriptor;
  struct dirent *entry;
  struct stat mystats;

  int files = 0;
  char direccion[100];
  char linea[300];
  char *path;

  sprintf(direccion,"/proc/%d/fd",pid);

  descriptor = opendir(direccion);

  /* Para cada entrada del directorio imprime lo pedido en el enunciado */
  while( (entry=readdir(descriptor)) )
  {
    if(files >= 2) /* Las dos primeras son los directorios padre */
    {
      /* Toma el file descriptor, genera los stats y el path */
      sprintf(linea,"/proc/%d/fd/%s",pid,entry->d_name);

      stat(linea, &mystats);

      path = malloc(mystats.st_size + 1);

      /* Muestra los permisos de lectura, escritura y ejecución */
      printf( (mystats.st_mode & S_IRUSR) ? "r" : "-");
      printf( (mystats.st_mode & S_IWUSR) ? "w" : "-");
      printf( (mystats.st_mode & S_IXUSR) ? "x" : "-");
      printf( (mystats.st_mode & S_IRGRP) ? "r" : "-");
      printf( (mystats.st_mode & S_IWGRP) ? "w" : "-");
      printf( (mystats.st_mode & S_IXGRP) ? "x" : "-");
      printf( (mystats.st_mode & S_IROTH) ? "r" : "-");
      printf( (mystats.st_mode & S_IWOTH) ? "w" : "-");
      printf( (mystats.st_mode & S_IXOTH) ? "x" : "-");

      /* Muestra el tipo de archivo */
      switch (mystats.st_mode & S_IFMT)
      {
        case S_IFBLK:  printf(" BLK "); break; /* Block */
        case S_IFCHR:  printf(" CHR "); break; /* Character */
        case S_IFDIR:  printf(" DIR "); break; /* Directory */
        case S_IFIFO:  printf(" FIF "); break; /* FIFO/pipe */
        case S_IFLNK:  printf(" LNK "); break; /* Symbolic link */
        case S_IFREG:  printf(" REG "); break; /* Regular file */
        case S_IFSOCK: printf(" SOK "); break; /* Socket */
        /* Archivo desconocido */
        default:       printf(" ??? "); break; /* Unknown */
      }

      /* Obtiene el directorio al cual está apuntando el descriptor */
      readlink(linea,path,100);
      printf("%s\n", path);

      printf("\n");
    }
    files++;
  }
  closedir(descriptor);
}

/*
 * Muestra los soft y hard limits del proceso pedido.
 * @param pid - process id del cual se desea obtener información.
 */
void limits(int pid)
{
  char limits[45];
  sprintf(limits,"/proc/%d/limits",pid);

  FILE *limites = fopen(limits,"r");

  int soft,hard;
  char *linea;

  linea = obtenerInfo("Max open files",limites);
  fclose(limites);

  sscanf(linea, "%*s %*s %d %d", &soft, &hard);

  printf("Soft limits / Hard limits: %d / %d\n", soft, hard);
}

/*
 * Imprime el kernel stack trace del proceso pedido.
 * @param pid - process id del cual se desea obtener información.
 */
void stack(int pid)
{
  char stack[45];
  sprintf(stack,"sudo cat /proc/%d/stack",pid);

  /* Con 'system' se pueden ejecutar comandos */
  system(stack);

  /*char linea[1000];

  FILE *trace = fopen(stack,"r");

  if(trace == NULL) printf("No se pudo acceder al stack. ¿Es root?");

  while (fgets(linea, sizeof linea, trace) != NULL)
  {
    printf("%s", linea);
  }
  fclose(trace);*/
}
