//============================================================================
// ----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2025/26 --------------------------------
// ----------------------------- SESION2.CPP ---------------------------------
//============================================================================
//Autores: 
//Alberto Chamizo Barrio
//Daniel Montero Palomo

#include <stdio.h>
#include <iostream>
#include <fstream>   
#include "linkLayer.h"
#include "stdio_ext.h"

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

//Envia un caracter desde mac_src a mac_dst
void EnviarCaracter(interface_t  &iface, char car, unsigned char* mac_src, unsigned char* mac_dst, unsigned char* type){
  unsigned char *caracter = (unsigned char *)malloc(1 * sizeof(unsigned char));
  unsigned char *trama ;
  *caracter = car;
  trama = BuildFrame(mac_src ,mac_dst, type, caracter);
  SendFrame(&iface, trama, 1);
  free(trama);
  free(caracter);
}

//Devuele el dato recibido por una trama si existe
char RecibirCaracter(interface_t &iface, unsigned char * type){
  char dato;
  apacket_t paquete;
  paquete = ReceiveFrame(&iface);
  if(paquete.packet != NULL ){
     dato = paquete.packet[14];
     return dato;
    }
  else{
    return 0;
  }
}

//Envia y recibe tramas
void EnvioInteractivo(interface_t &iface, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type){
  char tecla, car;
  while(tecla != 27){
  car = RecibirCaracter(iface, type);
  if(car)
    printf("\nRecibido : %c \n", car);
  if (kbhit()){
  tecla = getch();
    if (tecla != 27){
    EnviarCaracter(iface, tecla, mac_src, mac_dst, type);
    }
  }
  }
}

int main()
{
 interface_t iface;
 pcap_if_t *avail_ifaces=NULL;
 char *vector [20];
 int i = 0;
 char car = 'M';

 unsigned char mac_src[6];
 unsigned char mac_dst[6] = {0X00, 0X00, 0x00,0X00, 0X00, 0X00};
 unsigned char type[2]={0x30, 0X00};
  
 printf("\n----------------------------\n");
 printf("------ SESION 1 - FRC ------\n");
 printf("----------------------------\n");
 printf("Interfaces disponibles: \n");
    
 avail_ifaces=GetAvailAdapters(); 

 while(avail_ifaces -> next != NULL && avail_ifaces != NULL){
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
printf("La MAC destino es: ");
for(int j = 0; j <5; j++){  
printf("%.2x:", mac_dst[j]);
}

 int Puerto = OpenAdapter(&iface);
 if (Puerto != 0){
   printf("\nError al abrir el puerto\n");
   getch();
   return(1);
 }
 else{
   printf("\nPuerto abierto correctamente \n");
 }
__fpurge(stdin);

  for(int j = 0; j < 6; j++){
  mac_src[j] = iface.MACaddr[j];
  }
  printf("Pulse los caracteres a enviar: \n");

  EnvioInteractivo(iface, mac_src, mac_dst, type);

  CloseAdapter(&iface);
  printf("Puerto cerrado\n");
}
