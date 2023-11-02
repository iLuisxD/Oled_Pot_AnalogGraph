#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Definiciones4
#define ANCHO_PANTALLA 128
#define ALTO_PANTALLA 64
// Variables globales de configuracion de pantalla
Adafruit_SSD1306 pantalla(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

// Funciones
void setup()
{
  // Inicializar la pantalla OLED
  pantalla.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pantalla.clearDisplay();  //limpiamos la pantalla
  pantalla.setTextColor(SSD1306_WHITE);  //configuramos el color de texto
  pantalla.setTextSize(1);  //tamaño del texto
  pantalla.drawPixel(22, 30, SSD1306_WHITE);  //"encendemos un pixel en la posicción establecida"
  pantalla.drawLine(5, 5, 100, 50, SSD1306_WHITE);  //dibujamos una linea desde la posición x=5,y=5, hasta x=100,y=50
  pantalla.drawCircle(55,25,20,SSD1306_WHITE);  //dibujamos un circulo con origen x=55,y=25 radio 20
  pantalla.drawRoundRect(10,5,30,25,5,SSD1306_WHITE);  //dibujamos un rectángulo con origen x=10,y=5, ancho de 30 y alto de 25 con un radio en sus esquinas de 5grados
  pantalla.display();  //enviamos todos los parametros previamente configurados a la pantalla
}
void loop()
{

}
