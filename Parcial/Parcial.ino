#define FCPU 16000000                                // Frecuencia de la CPU del Arduino Uno (16 MHz).
#define USART_BAUDRATE 9600                          // Velocidad en baudios para la comunicación serie.
#define UBRR_VALUE ((FCPU/(USART_BAUDRATE*16UL))-1)   // Calcula el valor del registro UBRR para configurar la velocidad en baudios de la UART a 9600.

char buffer[10];   // Buffer para almacenar la cadena recibida
int index = 0;     // Índice para el buffer
int numero = 0;
//HOLAAA SOY ALEXIA
void setup() {
  // Configuración de UART para transmisión y recepción
  UBRR0H = (uint8_t)(UBRR_VALUE >> 8);                    // Configura los bits altos del registro UBRR0
  UBRR0L = (uint8_t)UBRR_VALUE;                           // Configura los bits bajos del registro UBRR0
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);                 // Configura el tamaño del dato a 8 bits
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);                   // Habilita la recepción y transmisión
  
  // Limpia las banderas del registro UCSR0A
  UCSR0A = 0x00;
}

void loop() {
  // Manejo de recepción de datos
  if (UCSR0A & (1 << RXC0)) {
    char dato_recibido = UDR0;  // Lee el dato recibido desde UDR0
    
    // Agrega el carácter al buffer si no es un retorno de carro o salto de línea
    if (dato_recibido != '\r' && dato_recibido != '\n') {
      buffer[index] = dato_recibido;
      index++;
      
      // Verifica si el buffer está lleno para evitar desbordamiento
      if (index >= sizeof(buffer)) {
        index = sizeof(buffer) - 1;  // Ajusta el índice al tamaño máximo del buffer
      }
    } 
    else {
      // Fin de la transmisión, convierte la cadena en un número entero
      buffer[index] = '\0';  // Añade el terminador nulo al final de la cadena
      numero = atoi(buffer);  // Convierte la cadena a un número entero
      
      // Imprime el número entero en el monitor serial (para depuración)
      while (!(UCSR0A & (1 << UDRE0)));  // Espera a que el buffer de transmisión esté listo
      UDR0 = '\r';
      while (!(UCSR0A & (1 << UDRE0)));  // Espera a que el buffer de transmisión esté listo
      int i = 0;
         // Recorre cada carácter en la cadena hasta llegar al terminador nulo
      UDR0=numero;                  // Envía el carácter actual a través de UART

      // Reinicia el buffer y el índice para la próxima recepción
      index = 0;
    }
    
    // Envía de vuelta el dato recibido
    while (!(UCSR0A & (1 << UDRE0)));  // Espera a que el buffer de transmisión esté listo
    UDR0 = dato_recibido;
  }
  // Tu código adicional aquí

  delay(100);  // Retardo para evitar lecturas innecesarias
}
