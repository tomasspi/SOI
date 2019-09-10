# Universidad Nacional De Córdoba
## Facultad de Ciencias Exactas, Físicas y Naturales
### Sistemas Operativos I
#### Trabajo Práctico N° 1: rdproc
------
#### Piñero, Tomás Santiago - Año 2019
------

#### Objetivos
Con el desarrollo del siguiente Trabajo Práctico (TP), se busca:
- Realizar un primer programa en C para GNU/Linux.
- Aprender sobre /proc: qué es, qué información contiene, cómo se puede utilizar.
- Aprender a compilar con GNU gcc, debuggear con GNU gdb.
- Dirigir el proceso de compilación a través de GNU Make.

#### Desarrollo

Se decidió modularizar el programa para una mejor utilización y mantenimiento del mismo. Por lo tanto se realizó cada funcionalidad pedida en su *header* correspondiente y un archivo *.c* que en el cual se realiza el parseo de los argumentos pasados, quedando así las siguientes dependencias:
1.  rpdoc.c
2.  StepA.h
2.  StepB.h
3.  StepC.h
4.  StepD.h
------

#### rdproc.c
Programa principal. Aquí se identifican los argumentos pasados mediante un "*switch-case*".

------

#### StepA.h
 Es la versión inicial del programa, que muestra el nombre de la máquina y la fecha y hora actuales a modo de cabereca, y como cuerpo infromación sobre el sistema.

##### Funciones implementadas
- "*obtenerInfo*(key, FILE)", que recibe como argumentos la información que se desea obtener y el archivo desde el cual obtenerla. Esta función es prácticamente el core del TP, ya que se utiliza para tomar información necesaria desde distintos archivos.
- "*convertTime(tiempo,jiffies)*", convierte un tiempo dado al formato ddD, hh:mm:ss. El tiempo puede estar en segundos o *jiffies*, por lo que el proósito del segundo argumento es indicar si el tiempo pasado es en segundos (*false*) o jiffies (*true*).
- "*cpuinfo*" imprime el tipo y modelo del CPU obtenido desde "*/proc/cpuinfo*".
- "*kernelversion*" imprime la versión del kernel obtenido desde "*/proc/sys/kernel/osrelease*".
- "*uptime*" imprime el tiempo transucrrido desde el inicio del SO obtenido desde "*/proc/uptime*".
- "*filesystem*" imprime la cantidad de sistemas de archivos soportados por el kernel obtenido desde "*/proc/filesystems*".

------

#### StepB.h
Si se invoca el programa con la opción *-s*, se ejecutará la función "*cputimes*", que mostrará adicionalmente al "*StepA*" los siguientes datos obtenidos de "*/proc/stat*":
- Cantidad de tiempo de CPU utilizado para usuarios, sistema y proceso idle.
- Cantidad de cambios de contexto.
- Número de procesos creados desde el inicio del sistema.

------

#### StepC.h
Si se invoca el programa con la opción *-l a b*, se mostrará adicionalmente al "*StepA*" y durante **b** segundos y cada **a** segundos, la siguiente información:
- Número de peticiones a disco realizadas, obtenido de "*/proc/diskstats*".
- Cantidad de memoria configurada en el hardware, obtenida de "*/proc/meminfo*".
- Cantidad de memoria disponible, obtenida de "*/proc/meminfo*".
- Lista de los promedios de carga de 1 minuto, obtenido de "*/proc/loadavg*".

Esto se realiza por medio de  la función "*memstats*", en la cual se muestra la información, se manda al hilo a dormir **a** segundos y lueg se vuelve a imprimir la información. Esto se repite por un total de **b** segundos.

------

#### StepD.h
- Si se invoca el programa con la opción *-p* <pid>, se imprime información sobre los *file descriptors* a los que tiene acceso el proceso. Esto se lleva a cabo mediante la funcion "*file_descriptors*", en la que se abren y leen los directorios de los file descriptors mediante las estructuras *entry* y *mystats*, respectivamente, para mostrar los permisos, el tipo de archivo y el *path* al que se encuentra vinculado.
- La opción *-f* <pid> imprime los límites de archivos abiertos para el proceso, obtenidos de "*/proc/<pid>/limits*" mediante la función "*limits*".
- La opción *-t* <pid> para imprimir el kernel stack trace del proceso, obtenido de "*/proc/<pid>/stack*" mediante la función "*stack*".
