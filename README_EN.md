This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/MicroUART.svg?color=brightgreen)](https://github.com/GyverLibs/MicroUART/releases/latest/download/MicroUART.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/MicroUART.svg)](https://registry.platformio.org/libraries/gyverlibs/MicroUART)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/MicroUART?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# MicroUART
Easy implementation of UART for ATmega328 and similar from this generation
- Full analogue of Serial
- Optionally work with a buffer / without
- Optionally inherits Print. h h
- Optionally inherits Stream. h h

### Compatibility
ATmega328 and similar from this generation

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **MicroUART** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/MicroUART/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="init"></a>
## Initialization
```cpp
MicroUART uart;
```

<a id="usage"></a>
## Use of use
```cpp
void MU_serialEvent();  // is called in interruption when receiving a byte (see example)
Остальные методы - как у Serial

// Defile settings. Prescribe before connecting the library
#define MU_STREAM     // Connect Stream.h (readString, readBytes...)
#define MU_PRINT      // Connect Print.h (print, println)
#define MU_TX_BUF 64  // Shipping buffer. Shut up. 8. You can turn off (0)
#define MU_RX_BUF 64  // Reception buffer. Shut up. 8. You can turn off (0)
```

<a id="example"></a>
## Example
For more examples see **examples**!
```cpp
//#define MU STREAM // connect Stream.h (readString, readBytes...)
#define MU_PRINT      // Connect Print.h (print, println)
//#define MU TX BUF 64 // send buffer. Shut up. 8. You can turn off (0)
//#define MU RX BUF 64 // Reception buffer. Shut up. 8. You can turn off (0)

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

// Called in interruption when receiving byte
void MU_serialEvent() {
  static bool val = 0;
  digitalWrite(13, val = !val);
  //uart.write(uart.read());
}
```

<a id="versions"></a>
## Versions
- v1.0
- v1.0.1 - small fixtures

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
