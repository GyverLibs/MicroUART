This is an automatic translation, may be incorrect in some places. See sources and examples!

# Microuart
Easy UART implementation for Atmega328 and similar from this generation
- Full analogue of Serial
- optionally work with the buffer/without
- Optionally inherits Print.h
- optionally inherits Stream.h

## compatibility
Atmega328 and similar from this generation

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** microuart ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/microuart/archive/refs/heads/main.zip). Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
`` `CPP
Micruart Uart;
`` `

<a id="usage"> </a>
## Usage
`` `CPP
void mu_serialevent ();// is called in interruption when taking a byte (see example)
The rest of the methods are like Serial

// defines of settings.Bend before connecting the library
#define mu_stream // Connect Stream.h (Readstring, Readbytes ...)
#define mu_print // Connect Print.h (Print, Println)
#define mu_tx_buf 64 // Boofer Sending.By the silence.8. You can turn off (0)
#define mu_rx_buf 64 // Reception buffer.By the silence.8. You can turn off (0)
`` `

<a id="EXAMPLE"> </a>
## Example
The rest of the examples look at ** Examples **!
`` `CPP
//# Define mu_stream // Connect Stream.h (Readstring, Readbytes ...)
#define mu_print // Connect Print.h (Print, Println)
//# Define mu_tx_buf 64 // Boofer Sending.By the silence.8. You can turn off (0)
//# Define mu_rx_buf 64 // Reception buffer.By the silence.8. You can turn off (0)

#include <microuart.h>
Micruart Uart;

VOID setup () {
  uart.begin (9600);
  Pinmode (13, 1);
}

VOID loop () {
  While (uart.availble ()) uart.write (uart.read ());
  UART.PRINTLN ("123456789");
  DELAY (1000);
}

// is called in interruption when receiving a byte
void mu_serialevent () {
  Static Bool Val = 0;
  digitalWrite (13, val =! Val);
  //uart.write (uart.read ());
}
`` `

<a id="versions"> </a>
## versions
- V1.0

<a id="feedback"> </a>
## bugs and feedback
When the bugs are createdE ** Issue **, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code