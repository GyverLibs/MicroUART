This is an automatic translation, may be incorrect in some places. See sources and examples!

# MicroUART
Lightweight UART implementation for ATmega328 and similar from this generation
- Complete analogue of Serial
- Optional work with/without buffer
- Optionally inherits Print.h
- Optionally inherits Stream.h

### Compatibility
ATmega328 and similar from this generation

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **MicroUART** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/MicroUART/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
MicroUART uart;
```

<a id="usage"></a>
## UseCranberries
```cpp
void MU_serialEvent(); // called in an interrupt when a byte is received (see example)
Other methods - like Serial

// defines settings. Prescribe BEFORE connecting the library
#define MU_STREAM // connect Stream.h (readString, readBytes...)
#define MU_PRINT // connect Print.h (print, println)
#define MU_TX_BUF 64 // send buffer. By default 8. Can be disabled (0)
#define MU_RX_BUF 64 // receive buffer. By default 8. Can be disabled (0)
```

<a id="example"></a>
## Example
See **examples** for other examples!
```cpp
//#define MU_STREAM // connect Stream.h (readString, readBytes...)
#define MU_PRINT // connect Print.h (print, println)
//#define MU_TX_BUF 64 // send buffer. By default 8. Can be disabled (0)
//#define MU_RX_BUF 64 // receive buffer. By default 8. Can be disabled (0)

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

// called in an interrupt when a byte is received
void MU_serialEvent() {
  static bool val = 0;
  digitalWrite(13, val = !val);
  //uart.write(uart.read());
}
```

<a id="versions"></a>
## Versions
- v1.0

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!