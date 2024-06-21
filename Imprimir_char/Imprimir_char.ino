#define FCPU 16000000                                // Define la frecuencia de la CPU del Arduino Uno (16 MHz).
#define USART_BAUDRATE 9600                          // Define la velocidad en baudios para la comunicación serie (9600 baudios).
#define UBRR_VALUE ((FCPU/(USART_BAUDRATE*16UL))-1)  // Calcula el valor del registro UBRR para configurar la velocidad en baudios de la UART a 9600.

void setup() {
  //Serial.begin(9600); // Inicializa la comunicación serial a 9600 baudios

  //-------------- Configuracion de UART0 para comunicación serie---------------------------------------

  UBRR0H = (uint8_t)(UBRR_VALUE >> 8);                    // Configura los bits altos del registro UBRR0
  UBRR0L = (uint8_t)UBRR_VALUE;                           // Configura los bits bajos del registro UBRR0
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);                // Configura el tamaño del dato a 8 bits
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);  // Habilita la recepción, transmisión y la interrupción al recibir un dato
  UCSR0A = 0x00;                                          // Limpia las banderas del registro UCSR0A

}

void loop() {
  char caracter = 'A'; // Carácter a imprimir 0 - 255 char = 1 byte
  
  // Envía el carácter a través de UART
  UDR0 = caracter;
  while (!(UCSR0A & (1 << UDRE0)));  // Espera a que el buffer de transmisión esté listo, tambien puedo usar un "delay(10)"
  UDR0 = '\r';
  delay(1000); // Espera 1 segundo
}
