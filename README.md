# esp-touch-modbus

funciona com a placa ESP32-S3-Touch-LCD-4.3B

Teste básico da comunicação MODBUS.

É preciso mover `ESP32Logger Log;` para o lugar certo em ESP32Logger.cpp

# Esse é log no monitor serial:

```
rs485 - [>>]: 64 4 0 0 0 2 78 3e 
E (9382) gpio: gpio_set_level(227): GPIO output gpio_num error
E (9393) gpio: gpio_set_level(227): GPIO output gpio_num error
00000009483 DBG write:  >> 64 4 0 0 0 2 78 3e 
00000009533 DBG read:  << 64 4 4 5f 93 41 88 1c 8d 
rs485 - [<<]: 64 4 4 5f 93 41 88 1c 8d 
Received Float Value: 17.047
rs485 - [>>]: 64 4 0 2 0 2 d9 fe 
E (9444) gpio: gpio_set_level(227): GPIO output gpio_num error
E (9454) gpio: gpio_set_level(227): GPIO output gpio_num error
00000009544 DBG write:  >> 64 4 0 2 0 2 d9 fe 
00000009594 DBG read:  << 64 4 4 a3 d7 42 83 2d ff 
rs485 - [<<]: 64 4 4 a3 d7 42 83 2d ff 
Received Float Value: 65.820
```