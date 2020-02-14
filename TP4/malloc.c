#include <stdio.h>
#include "alloc.h"

int main(int argc, char const *argv[])
{
  printf("|---|-------------------------------------------|---|\n");
  printf("|---|---------- SISTEMAS OPERTAIVOS I ----------|---|\n");
  printf("|---|---------- Trabajo Práctico N° 4 ----------|---|\n");
  printf("|---|----------        malloc         ----------|---|\n");
  printf("|---|---------- Tomás Santiago Piñero ----------|---|\n");
  printf("|---|-------------------------------------------|---|\n\n");

  void *p1, *p2, *p3, *p4;

  printf("\n|--------------------- malloc ----------------------|\n\n");
  p1 = mem_alloc(1);
  p2 = mem_alloc(10);
  p3 = mem_alloc(100);

  print_info();

  printf("\n|------------------------ free ---------------------|\n\n");

  free_mem(p1);
	free_mem(p2);
	free_mem(p3);

  print_info();

  printf("\n|---------------- malloc nuevamente ----------------|\n\n");

	p4 = mem_alloc(50);

  print_info();

  free_mem(p4);

  return 0;
}
