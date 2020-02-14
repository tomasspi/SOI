# Universidad Nacional De Córdoba
## Facultad de Ciencias Exactas, Físicas y Naturales
### Sistemas Operativos I
#### Trabajo Práctico N° 3: kernel modules
------
#### Oroná, Madeléin Ayelén - Año 2019
#### Piñero, Tomás Santiago - Año 2019
------


## Información importante:

El proyecto se encuentra realizado para el sistema
operativo de Linux, para una arquitectura de 64 bits.


### Guia de Instalación y Uso

El proyecto se encuentra contenido en formato .zip.
Luego de que descomprima se puede ejecutar el programa con los siguientes pasos:


* Desde la carpeta "encrypter":
```sh
$ make
$ insmod encrypter.ko
$ mknod -m 0666 /dev/encrypter c 100 0
```

* Desde la carpeta "decrypter":
```sh
$ make
$ insmod decrypter.ko
$ mknod -m 0666 /dev/decrypter c 101 0
```

## Funciones a realizar:

Escribir en el *device file* con **echo**:

```sh
$ echo abcde > /dev/encrypter
```

Leer el contenido del *device file* */dev/encrypter* con **cat**:

```sh
$ cat /dev/encrypter
```
La salida debería ser la cadena: **bcdef**

-----

Enviar la cadena encriptada al *device file* */dev/decrypter*:

```sh
$ echo /dev/encrypter > /dev/decrypter
```


Leer el contenido del *device file* */dev/decrypter*:

```sh
$ cat /dev/decrypter
```
La salida debería ser la cadena inicial: **abcde**


#### Si se desea remover el dispositivo, ejecutar los siguientes comandos como super usuario:

```sh
$ rrmod encrypter
```

```sh
$ rrmod decrypter
```
