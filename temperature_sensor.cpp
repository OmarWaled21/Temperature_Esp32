#include <temperature_sensor.h>

// تعيين منفذ البيانات للمستشعر
#define ONE_WIRE_BUS 4  // استخدم نفس المنفذ المتصل بالـ DATA

// إنشاء كائنات المكتبة
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void sensorSetUp() {
  sensors.begin();
}

float measureTemperatureSensor() {
  sensors.requestTemperatures();  // طلب قراءة درجة الحرارة
  float tempC = sensors.getTempCByIndex(0);  // قراءة درجة الحرارة بالسلسيوس

  return tempC;
}