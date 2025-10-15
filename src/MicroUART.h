/*
    Лёгкая реализация UART для ATmega328 и подобных из этого поколения
    Документация:
    GitHub: https://github.com/GyverLibs/MicroUART
    Возможности:
    - Полный аналог Serial
    - Опционально работа с буфером/без
    - Опционально наследует Print.h
    - Опционально наследует Stream.h

    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
*/

#ifndef _MicroUART
#define _MicroUART

#if defined(__AVR_ATmega2560__)
#define USARTx_RX_vect USART0_RX_vect
#define USARTx_UDRE_vect USART0_UDRE_vect

#elif defined(USART_RX_vect) && defined(USART_UDRE_vect)
#define USARTx_RX_vect USART_RX_vect
#define USARTx_UDRE_vect USART_UDRE_vect
#else

#error "AVR USART not defined"
#endif

#ifndef MU_TX_BUF
#define MU_TX_BUF 8
#endif

#ifndef MU_RX_BUF
#define MU_RX_BUF 8
#endif

#if (MU_TX_BUF > 0)
static volatile uint8_t _bufTX[MU_TX_BUF];
static volatile uint8_t _headTX, _tailTX;
#endif
#if (MU_RX_BUF > 0)
static volatile uint8_t _bufRX[MU_RX_BUF];
static volatile uint8_t _headRX, _tailRX;
#else
static volatile uint8_t _byteBufRX = 0, _availFlag = 0;
#endif

void MU_serialEvent() __attribute__((weak));

class MicroUART
#ifdef MU_STREAM
#undef MU_PRINT
    : public Stream
#endif
#ifdef MU_PRINT
    : public Print
#endif
{
   public:
    // ================= BEGIN ==================
    void begin(const uint32_t baud) {
        UBRR0 = (F_CPU / (8ul * baud)) - 1;                    // скорость
        UCSR0A = (1 << U2X0);                                  // скорость
        UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);  // подрубаем rx tx и rx isr
        UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);                // 8 бит байт
#if (MU_TX_BUF > 0)
        _headTX = _tailTX = 0;
#endif
#if (MU_RX_BUF > 0)
        _headRX = _tailRX = 0;
#endif
    }

    void end() {
        UCSR0B = 0;
    }

    // ================= WRITE ==================
#if defined(MU_STREAM) || defined(MU_PRINT)
    virtual size_t
#else
    size_t
#endif
    write(uint8_t data) {
#if (MU_TX_BUF > 0)                             // если есть буфер на отправку
        uint8_t i = (_headTX + 1) % MU_TX_BUF;  // позиция нового байта в буфере
        while (i == _tailTX);                   // ждать освобождения места в буфере
        _bufTX[_headTX] = data;   // пишем в буфер
        _headTX = i;              // двигаем
        UCSR0B |= (1 << UDRIE0);  // на отправку
        return 1;
#else                             // нет буфера
        while (!(UCSR0A & (1 << UDRE0)));   // ждём отправку
        UDR0 = data;                        // пишем
#endif
    }

    size_t write(const uint8_t *buffer, size_t size) {
        for (size_t i = 0; i < size; i++) write(buffer[i]);
        return size;
    }


    // ================= AVAILABLE ==================
#if defined(MU_STREAM)
    virtual int
#else
    int
#endif
    available() {
#if (MU_RX_BUF > 0)
        return ((uint16_t)(MU_RX_BUF + _headRX - _tailRX) % MU_RX_BUF);
#else
        return _availFlag;
#endif
    }

    int availableForWrite() {
#if (MU_TX_BUF > 0)
        if (_headTX >= _tailTX) return MU_TX_BUF - 1 - _headTX + _tailTX;
        return _tailTX - _headTX - 1;
#else
        return 1;
#endif
    }

    // ================= READ ==================
#if defined(MU_STREAM)
    virtual int
#else
    uint8_t
#endif
    read() {
#if (MU_RX_BUF > 0)
        if (_headRX == _tailRX) return -1;  // буфер пуст
        uint8_t c = _bufRX[_tailRX];
        _tailRX = (_tailRX + 1) % MU_RX_BUF;  // хвост двигаем
        return c;
#else
        _availFlag = 0;
        return _byteBufRX;
#endif
    }

#if defined(MU_STREAM)
    virtual int
#else
    uint8_t
#endif
    peek() {
#if (MU_RX_BUF > 0)
        return (_headRX != _tailRX) ? _bufRX[_tailRX] : -1;
#else
        return _byteBufRX;
#endif
    }

   private:
};

// ================= ISR VECT ==================
// прерывание на приём
ISR(USARTx_RX_vect) {
    uint8_t data = UDR0;
    if (!(UCSR0A & (1 << UPE0))) {  // не parity error
#if (MU_RX_BUF > 0)
        uint8_t i = (_headRX + 1) % MU_RX_BUF;
        if (i != _tailRX) {
            _bufRX[_headRX] = data;
            _headRX = i;
        }
#else
        _byteBufRX = data;
        _availFlag = 1;
#endif
    }
    MU_serialEvent();
}

// прерывание на отправку
#if (MU_TX_BUF > 0)
ISR(USARTx_UDRE_vect) {
    UDR0 = _bufTX[_tailTX];
    _tailTX = (_tailTX + 1) % MU_TX_BUF;
    if (_headTX == _tailTX) UCSR0B &= ~(1 << UDRIE0);
}
#endif
#endif
