/****************************************************************************/
//  Function:       Header file for TroykaDHT11
//  Hardware:       DHT11
//  Arduino IDE:    Arduino-1.6.5
//  Author:         Igor Dementiev
//  Date:           Oct 07,2015
//  Version:        v1.0
//  by www.amperka.ru
/****************************************************************************/

#ifndef TROYKADHT11_H_
#define TROYKADHT11_H_

#include <Arduino.h>

#define DHT_OK                0
#define DHT_ERROR_CHECKSUM   -1
#define DHT_ERROR_TIMEOUT    -2

class DHT11
{
 public:
    explicit DHT11(uint8_t pin);
    void begin();
    uint8_t read();
    uint8_t getTemperatureC() const { return _temperatureC; }
    uint8_t getHumidity() const { return _humidity; }
 private:
    uint8_t _pin;
    uint8_t _temperatureC;
    uint8_t _humidity;
};
#endif  // TROYKADHT11_H_
