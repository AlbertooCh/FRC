//============================================================================
// ----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2025/26 --------------------------------
// ----------------------------- SESION1.CPP ---------------------------------
//============================================================================
//Autores: 
//Alberto Chamizo Barrio
//Daniel Montero Palomo

#include <stdio.h>
#include <iostream>
#include "linkLayer.h"

using namespace std;

void mostrarMAC(unsigned char *mac){
   for (int j = 0; j < 5; j++){
      printf("%.2x:", mac[j]);
   }
   printf("%.2x \n", mac[5]);
}

void imprimirMAC(interface_t &iface, char *vector[], int i){
   setDeviceName(&iface, vector[i]);
   GetMACAdapter(&iface);
   printf("Interfaz elegida: %s", vector[i]);
   printf("\n");
   printf("La MAC es: ");
   mostrarMAC(iface.MACaddr);
}

int main()
{
 interface_t iface;
 pcap_if_t *avail_ifaces=NULL;
 char *vector [20];
 int i = 0;
 
 printf("\n----------------------------\n");
 printf("------ SESION 1 - FRC ------\n");
 printf("----------------------------\n");
 printf("Interfaces disponibles: \n");
    
 avail_ifaces=GetAvailAdapters(); 

 while(avail_ifaces -> next != NULL){
    printf("[%i] %s \n", i, avail_ifaces -> name);
    vector[i] = avail_ifaces -> name;
    i+=1;
    avail_ifaces = avail_ifaces -> next;
 }
 if (i == 0){
   printf("No hay interfaces disponibles \n");
   return 1;
 }

 printf("Selecciona la interfaz: ");
 cin >> i;
 imprimirMAC(iface, vector, i);
 
 return 0;
}
