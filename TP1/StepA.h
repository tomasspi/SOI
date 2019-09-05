#ifndef STEPA_H
#define STEPA_H

#include <stdio.h>    //Input-Output
#include <stdlib.h>   //Standard
#include <string.h>   //Strings
#include <stdbool.h>  //Booleanos
#include <unistd.h>   //Clocks and Sleep

#define JpS sysconf(_SC_CLK_TCK) //Jiffies/seconds (clock tics)

void convertTime(int seconds, bool jiffies);
void cpuinfo(void);
void filesystem(void);
void header(void);
void imprimirDefault(void);
void kernelversion(void);
char* obtenerInfo(char* key, FILE *archivo);
void uptime(void);

/**
 * Convierte el tiempo en segundos al formato dd D hh:mm:ss
 * @param time - Tiempo en a convertir
 * @param jiffies - Indica si el tiempo a convertir esta en
 *                  jiffies: true si, false no
*/
void convertTime(int time, bool jiffies)
{
  int dias, horas, minutos, segundos;

  /* Si son Jiffies, se los convierte a segundos */
  if(jiffies) time = time/JpS;

  /* Conversion de segundos a dd hh:mm:ss */
  dias = time / 86400;
  horas = (time % 86400) / 3600;
  minutos = (time % 3600) / 60;
  segundos = (time % 3600) % 60;

  printf("%02d D, %02d:%02d:%02d\n", dias, horas, minutos, segundos);
}

/**
 * Toma los datos pedidos usando 'cpuinfo' del directorio /proc
*/
void cpuinfo(void)
{
  char *tipo, *modelo;//, *cache, *cores;

  char path_info[] = "/proc/cpuinfo";

  /* Abre el archivo en modo lectura */
  FILE *archivo = fopen(path_info,"r");

  tipo = obtenerInfo("vendor_id", archivo);
  modelo = obtenerInfo("model name", archivo);
  //cache = obtenerInfo("cache size", archivo);
  //cores = obtenerInfo("cpu cores", archivo);

  fclose(archivo);

  printf("\nInformación del CPU:\n");
  printf(" - Tipo: %s\n - Modelo: %s\n",// - Cache: %s\n - Cores: %s\n",
        tipo, modelo);//, cache, cores);
}

/* Cuenta la cantidad de sistemas de archivos soportados por el kernel. */
void filesystem(void)
{
  char path_files[] = "/proc/filesystems";

  FILE *files = fopen(path_files,"r");

  int contador = 0;

  char linea[1000];

  /* Cuenta las lineas del archivo */
  while (fgets(linea, sizeof linea, files) != NULL) contador++;
  fclose(files);

  printf("Cantidad de archivos soportados: %d\n", contador);
}

/**
 * Toma el nombre de la máquina, la fecha y la hora del sistema.
*/
void header(void)
{
  char *nombre;
  char *fecha, *hora;

  char path_time[] = "/proc/driver/rtc";
  char path_nombre[] = "/proc/sys/kernel/hostname";

  FILE *nombre_file = fopen(path_nombre,"r");

  char linea[100];

  nombre = fgets(linea,sizeof linea, nombre_file);
  nombre[strlen(nombre)-1] = 0; // Quita el salto de linea
  fclose(nombre_file);

  FILE *time = fopen(path_time, "r");

  hora = obtenerInfo("rtc_time", time);
  fecha = obtenerInfo("rtc_date", time);
  fclose(time);

  printf("%s %s %s\n", nombre, fecha, hora);
}

/**
 * Imprime la información pedida en el primer Step:
 *    - Header con el nombre de la máquina, fecha y hora actual
 *    - Infromación sobre el CPU
 *    - Versión del kernel
 *    - Tiempo transcurrido desde el inicio
 *    - Sistema de archivos soportados
 */
void imprimirDefault(void)
{
  header();
  cpuinfo();
  kernelversion();
  uptime();
  filesystem();
}

/**
 * Toma la version del kernel.
*/
void kernelversion(void)
{
  char path_kernel[] = "/proc/sys/kernel/osrelease";

  FILE *kernel = fopen(path_kernel,"r");

  char *version;

  char linea[100];

  version = fgets(linea, sizeof linea, kernel);
  version[strlen(version)-1] = 0; // Quita el salto de linea
  fclose(kernel);

  printf(" - Version de kernel: %s\n", version);
}

/**
 * Esta funcion abre el archivo cpuinfo y busca la información pedida.
 * @param key - información que se desea obtener.
 * @param archivo - archivo del cual se desea obtener la key.
*/
char* obtenerInfo(char* key, FILE *archivo)
{
  char *valor;
  char *resultado;

  char linea[1000];

  /* Recorre el archivo linea por linea */
  while (fgets(linea, sizeof linea, archivo) != NULL)
  {
    /* Si en esa linea encuentra un matcheo, guarda el valor*/
    if(strncmp(linea, key, strlen(key)) == 0)
    {
      /* Encontré la key, me muevo 2 lugares luego de los : */
      if(strchr(linea, ':') != NULL)
      {
        valor = strchr(linea, ':');
        valor += 2;
        resultado = strdup(valor);
      } else
      {
        valor = strchr(linea, ' ');
        resultado = strdup(valor);
      }

      /* Si hay una nueva linea al final del valor, la quita */
      int len = strlen(resultado);
      if(resultado[len-1] == '\n') resultado[len-1] = 0;
      break;
    }
  }
  return resultado;
}

/**
 * Abre el archivo uptime del proc y toma el tiempo transcurrido
 * desde que se inicio el sistema y lo convierte a dias, horas,
 * minutos y segundos.
*/
void uptime(void)
{
  char path_uptime[] = "/proc/uptime";

  FILE *tiempo = fopen(path_uptime,"r");

  int uptime;

  fscanf(tiempo,"%d",&uptime);

  fclose(tiempo);

  printf("Tiempo transcurrido desde inicio: ");
  convertTime(uptime,false);
}

#endif
