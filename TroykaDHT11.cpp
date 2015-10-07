/****************************************************************************/
//  Function:       Cpp file for TroykaDHT11
//  Hardware:       DHT11
//  Arduino IDE:    Arduino-1.6.5
//  Author:         Igor Dementiev
//  Date:           Oct 07,2015
//  Version:        v1.0
//  by www.amperka.ru
/****************************************************************************/

#include "TroykaDHT11.h"

DHT11::DHT11(uint8_t pin) {
    _pin = pin;
}

void DHT11::begin() {
}

uint8_t DHT11::read() {
    // буффер данных
    uint8_t bits[5];
    uint8_t cnt = 7;
    uint8_t idx = 0;

    // очистка буффера
    for (int i = 0; i < 5; i++) bits[i] = 0;

    // согласование с датчиком
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delay(18);
    digitalWrite(_pin, HIGH);
    delayMicroseconds(40);
    pinMode(_pin, INPUT);

    // проверка отвечает ли датчик
    unsigned int loopCnt = 10000;
    while (digitalRead(_pin) == LOW)
        if (loopCnt-- == 0) return DHT_ERROR_TIMEOUT;

    loopCnt = 10000;
    while (digitalRead(_pin) == HIGH)
        if (loopCnt-- == 0) return DHT_ERROR_TIMEOUT;

    // Считываем 40 бит
    for (int i = 0; i < 40; i++) {
        loopCnt = 10000;
        while (digitalRead(_pin) == LOW)
            if (loopCnt-- == 0) return DHT_ERROR_TIMEOUT;

        unsigned long t = micros();
        loopCnt = 10000;
        while (digitalRead(_pin) == HIGH)
            if (loopCnt-- == 0) return DHT_ERROR_TIMEOUT;

        if ((micros() - t) > 40) bits[idx] |= (1 << cnt);
        // следующий байт?
        if (cnt == 0) {
            cnt = 7;
            idx++;
        } else {
            cnt--;
        }
    }

    // запись данных
    _humidity    = bits[0];
    _temperatureC = bits[2];
    // проверка контрольной суммы
    uint8_t sum = bits[0] + bits[2];

    if (bits[4] != sum) return DHT_ERROR_CHECKSUM;
    return DHT_OK;
}
