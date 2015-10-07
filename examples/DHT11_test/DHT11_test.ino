// библиотека для работы с датчиком DHT11
#include <TroykaDHT11.h>
// создаём объект класса DHT11 и пераём номер пина к которому подкючён датчик
DHT11 dht(11);

void setup()
{
  // открываем последовательный порт для мониторинга действий в программе
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  // переменная состояния датчика
  int check;
  // мониторинг ошибок
  // считывание данных с датчика DHT11
  check = dht.read();
  switch (check) {
    // всё OK
    case DHT_OK:
      // выводим показания влажности и температуры
      Serial.print("Temperature = ");
      Serial.print(dht.getTemperatureC());
      Serial.print("C \t");
      Serial.print("Humidity = ");
      Serial.print(dht.getHumidity());
      Serial.println("%");
      break;
    // ошибка контрольной суммы
    case DHT_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
    // превышение времени ожидания
    case DHT_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;
    // неизвестная ошибка
    default:
      Serial.println("Unknown error");
      break;
  }
  // ждём 1 секунду
  delay(1000);
}
