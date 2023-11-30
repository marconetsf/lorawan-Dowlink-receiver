#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lora.h"

uint8_t buf[32];

void task_rx(void *p)
{
   int x;
   printf('Iniciando task de rx\n');
   for(;;) {
      lora_receive();    // put into receive mode
      while(lora_received()) {
         x = lora_receive_packet(buf, sizeof(buf));
         buf[x] = 0;
         for (int w = 0; w < x; w++)
         {
            printf(" %02X", buf[w]);
         }
         printf("\n");
         lora_receive();
      }
      vTaskDelay(1);
   }
}

void app_main()
{
   printf("INIT\n");
   lora_init();
   printf("1INIT\n");
   lora_set_frequency(9257e5);
   printf("2INIT\n");
   lora_enable_crc();
   printf("3INIT\n");
   lora_set_bandwidth(500000);
   printf("4INIT\n");
   //lora_set_spreading_factor(10);
   printf("5INIT\n");
   lora_set_coding_rate(5);
   printf("6INIT\n");
   lora_write_reg(0x33, 103); // RegInvertIQ (51, 103);
   printf("7INIT\n");
   lora_write_reg(0x0C, 0b00100011);
   lora_set_tx_power(27);
   printf("8INIT\n");
   printf("Iniciando task de rx\n");

   int x;
   for(;;) {

      lora_receive();    // put into receive mode
      while(lora_received()) {
         x = lora_receive_packet(buf, sizeof(buf));
         buf[x] = 0;
         for (int w = 0; w < x; w++)
         {
            printf(" %02X", buf[w]);
         }
         printf("\n");
         lora_receive();
      }
      vTaskDelay(1);
   }
}