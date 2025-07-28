# esp-touch-modbus

funciona com a placa ESP32-S3-Touch-LCD-4.3B

Teste básico da comunicação MODBUS.

É preciso mover `ESP32Logger Log;` para o lugar certo em ESP32Logger.cpp

# Log no monitor serial

```
rs485 - [>>]: 64 4 0 0 0 2 78 3e 
E (215481) gpio: gpio_set_level(227): GPIO output gpio_num error
E (215492) gpio: gpio_set_level(227): GPIO output gpio_num error
00000215596 DBG write:  >> 64 4 0 0 0 2 78 3e 
00000215646 DBG read:  << 64 4 4 f9 2c 41 87 4f e5 
rs485 - [<<]: 64 4 4 f9 2c 41 87 4f e5 
Received Float Value: 16.997
rs485 - [>>]: 64 4 0 2 0 2 d9 fe 
E (215543) gpio: gpio_set_level(227): GPIO output gpio_num error
E (215553) gpio: gpio_set_level(227): GPIO output gpio_num error
00000215657 DBG write:  >> 64 4 0 2 0 2 d9 fe 
00000215708 DBG read:  << 64 4 4 83 69 42 87 47 d8 
rs485 - [<<]: 64 4 4 83 69 42 87 47 d8 
Received Float Value: 67.757
```

# Log no USR-TCP232-410s
```
Receive HEX: 0x64 0x4 0x0 0x0 0x0 0x2 0x78 0x3e 
Receive HEX: 0x64 0x4 0x4 0xf9 0x2c 0x41 0x87 0x4f 0xe5 
Receive HEX: 0x64 0x4 0x0 0x2 0x0 0x2 0xd9 0xfe 
Receive HEX: 0x64 0x4 0x4 0x83 0x69 0x42 0x87 0x47 0xd8 
```