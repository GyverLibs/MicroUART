//#define MU_STREAM     // подключить Stream.h (readString, readBytes...)
#define MU_PRINT      // подключить Print.h (print, println)
//#define MU_TX_BUF 64  // буфер отправки. По умолч. 8. Можно отключить (0)
//#define MU_RX_BUF 64  // буфер приёма. По умолч. 8. Можно отключить (0)

#include <MicroUART.h>
MicroUART uart;

void setup() {
  uart.begin(9600);
  pinMode(13, 1);
}

void loop() {
  while (uart.available()) uart.write(uart.read());
  uart.println("123456789");
  delay(1000);
}

// вызывается в прерывании при приёме байта
void MU_serialEvent() {
  static bool val = 0;
  digitalWrite(13, val = !val);
  //uart.write(uart.read());
}
