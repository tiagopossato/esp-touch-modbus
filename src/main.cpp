
#include "modbus-rtu.h"
// Define the GPIO pins for RS485 communication
#define RS485_GPIO_RX 43
#define RS485_GPIO_TX 44
#define RS485_GPIO_RTS -1

// Create an instance of ModbusRTU
ModbusRTU modbusrtu;

// Function prototype for getting data
void get_data(uint8_t unit_id, uint8_t fc, uint16_t address, uint16_t len);

// Function to convert Modbus RTU data to float
// This function assumes that the data is in little-endian format
// and that the float is represented by 4 bytes in the Modbus response.
// It takes a pointer to a byte array and returns the corresponding float value.
// Note: Ensure that the byte order matches the Modbus specification you are working with.
// If the byte order is different, you may need to adjust the byte assignments accordingly.
// This function is used to convert the received Modbus data into a float value.
// It reads 4 bytes from the Modbus response and converts them into a float value.
// The byte order is assumed to be little-endian, which is common in Modbus RT
float convertModbusFloat(uint8_t *data_bytes);

/**
 * @brief Main setup function
 * This function initializes the serial communication and sets up the Modbus RTU instance.
 * It configures the serial port for RS485 communication and sets the Modbus parameters.
 * It is called once at the beginning of the program to set up the environment.
 * It initializes the serial port, sets the Modbus parameters, and prepares the system for communication.
 * It is essential to call this function before attempting to read or write Modbus data.
 * @note Ensure that the serial port is correctly configured for RS485 communication.
 * @note The Modbus parameters such as unit ID, baud rate, and serial configuration should
 *       match the settings of the Modbus device you are communicating with.  
 */
void setup()
{
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("iniciando  rs485..");
  // Initialize Modbus RTU with the specified serial port and GPIO pins
  modbusrtu.setup(&Serial1, RS485_GPIO_RX, RS485_GPIO_TX, RS485_GPIO_RTS);
  // Begin Modbus RTU communication with the specified parameters
  modbusrtu.begin(1, 9600, SERIAL_8N1);
}

void loop()
{
  // Get data from Modbus RTU
  // This function reads data from the Modbus device with unit ID 100, function code 4,
  // starting from address 0, and reading 2 registers (4 bytes).
  // The received data is then converted to a float value and printed to the serial monitor.
  get_data(100, 4, 0, 2);
  get_data(100, 4, 2, 2);

  delay(3000);
}

void get_data(uint8_t unit_id, uint8_t fc, uint16_t address, uint16_t len)
{
  uint16_t size = 32;
  uint8_t *data = (uint8_t *)malloc(size);
  if (data == nullptr)
  {
    Serial.println("Memory allocation failed");
    return;
  }
  uint8_t error = modbusrtu.rs485_read(unit_id, fc, address, len, data, &size);
  if (error == 0)
  {
    // Serial.print("res: ");
    // uint8_t i = 0;
    // while (i < size)
    // {
    //   Serial.printf("0x%x ", data[i++]);
    // }
    // Serial.println();
    // Função de conversão
    float received_value = convertModbusFloat(data);
    Serial.printf("Received Float Value: %.3f\n", received_value);
  }
  else
  {
    Serial.printf("error: 0x%x \n", error);
    String error_msg = modbusrtu.getLastError();
    if (error_msg != "")
      Serial.println("error msg: " + error_msg);
  }

  free(data);
}

/**
 * Converts a 4-byte array to a float value.
 * The byte order is assumed to be little-endian.
 * @param data_bytes Pointer to the 4-byte array.
 * @return The converted float value.
 */
float convertModbusFloat(uint8_t *data_bytes)
{
  // Ensure the input is valid
  if (data_bytes == nullptr)
  {
    Serial.println("Invalid data bytes");
    return 0.0f; // Return 0.0f or handle error as needed
  }
  // Create a union to convert the byte array to float
  // This assumes the byte order is little-endian, which is common in Modbus RTU
  // If the byte order is different, you may need to adjust the byte assignments accordingly
  // Note: This is a simple way to convert bytes to float, but it may not be portable across different architectures.
  // If you need portability, consider using memcpy or similar functions.
  union
  {
    uint8_t bytes[4];
    float value;
  } float_converter;

  float_converter.bytes[0] = data_bytes[1]; // LSB do float (corresponde a data_bytes[1])
  float_converter.bytes[1] = data_bytes[0]; // (corresponde a data_bytes[0])
  float_converter.bytes[2] = data_bytes[3]; // (corresponde a data_bytes[3])
  float_converter.bytes[3] = data_bytes[2]; // MSB do float (corresponde a data_bytes[2])

  return float_converter.value;
}