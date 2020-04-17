#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

uint8_t test[8] ={11,12,13,14,15,16,17,18}; // MAC
char* MAC2Hex(uint8_t mac[8]) { 
  uint64_t mac_int = ((uint64_t)mac);
  char result[8*2+1];
  sprintf(result, "%0lX", mac_int);
  return strdup(result);
}
int main(void) {
  
  char* hex;
  hex = MAC2Hex(test);
  printf("%s", hex);
  return 0;
}