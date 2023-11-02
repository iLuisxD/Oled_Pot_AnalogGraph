#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definiciones4
#define ANCHO_PANTALLA 128
#define ALTO_PANTALLA 64

// se llama a la instancia de la oled para definir ancho alto 
Adafruit_SSD1306 pantalla(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);
// se define en que pin se conectará la señal analógica
uint16_t potentiometerPin = 34;

const int sampleRate = 200;  // Tasa de muestreo en milisegundos
const int graphWidth = 105; // Ancho de la gráfica en píxeles
const int graphHeight = 43; // Altura de la gráfica en píxeles
const int Yinit = 16;  //se define el valor inicial en Y para la gráfica
static int xinit = 4;  //se define el valor inicial en X para la gráfica
static int prevX , prevY = 0;  //se define valor en cero paraa utilizarse mas adelante

//variable que almacenará el valor a graficar
int y;

//variable de almacena el valor leído
int sensorValue;

void drawejes()
{
  //se grafica una linea vertical desde xinit,Yinit-10  hasta  xinit,Yinit+35 y se establece un color de línea blanca
  pantalla.drawLine(xinit, Yinit - 10, xinit, Yinit + 35, SSD1306_WHITE);
  //se grafica una linea horizontal desde xinit,Yinit+35  hasta  xinit+105,Yinit+35 y se establece un color de línea blanca
  pantalla.drawLine(xinit, Yinit + 35, xinit+104, Yinit + 35, SSD1306_WHITE);
  //se fija el cursor en la pantalla en 4,5 conociendo que el máximo es 128,64 por la resolucion de la pantalla oled
  pantalla.setCursor(6, 5);
  //se establece el tamaño del texto a escribri
  pantalla.setTextSize(1);
  //se escribe el texto en la posicion 4,5
  pantalla.print("Analog Value: ");
  //se fija el cursor en la pantalla en 95,Yinit+40 conociendo que el máximo es 128,64 por la resolucion de la pantalla oled
  pantalla.setCursor(95, Yinit + 40);
  //se escribe el texto en la posicion 95, Yinit + 40
  pantalla.print("(t)");
  //se fija el cursor en la pantalla en 95,Yinit+40 conociendo que el máximo es 128,64 por la resolucion de la pantalla oled
  pantalla.setCursor(0,Yinit + 40 );
  //se escribe el texto en la posicion 95, Yinit + 40
  pantalla.print("0");
  //se refresca la pantalla con lo valores establecidos previamente para todos los pixeles
  pantalla.display();
}

// Funciones
void setup()
{
  Serial.begin(9600);
  // Inicializar la pantalla OLED con su respectiva dirección I2C
  pantalla.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //se limpia la pantalla
  pantalla.clearDisplay();
  //se establece el color del texto en la pantalla
  pantalla.setTextColor(SSD1306_WHITE);
  //se establece el tamaño del texto a mostrarse en la pantalla
  pantalla.setTextSize(1);

  // Se llama a la función que dibujará los ejes de coordenadas en la pantalla oled
  drawejes();
}
void loop()
{

  //se guarda en la variable sensorValue el valor leído por el pin de entrada analógico
  sensorValue = analogRead(potentiometerPin);
  //se escala dicho valor a valores para que quede dentro del espacio de nuestro "plotter"
  y = map(sensorValue, 0, 4095, graphHeight+5, Yinit);
  //se dibuja un rectángulo con el fondo negro para "borrar" lo previamente escrito 
  //desde la posición 83,4 hasta 113,15 con un arco en las esquina de 1grados 
  pantalla.fillRoundRect(83, 4,30,11,1,SSD1306_BLACK);
  //se setea el cursor en 85,6
  pantalla.setCursor(85, 6);
  //se muestra el valor del dato leído analógico
  pantalla.print(sensorValue);
  //  Dibuja la lectura en la pantalla OLED
  //se verifica que el primer dato sea cero para graficar solo un pixel de inicio
  if (prevY==0) pantalla.drawPixel(xinit, Yinit, SSD1306_WHITE);
  //caso contrario se grafica una línea desde el valor X,Y anterior hasta el nuevo valor X,Y
  else pantalla.drawLine(prevX, prevY, xinit, y, SSD1306_WHITE);
  //se refresca la pantalla
  pantalla.display();
  //se establece que el valor anterior de Y sea el último leído
  prevY = y;
  //se establece que el valor anterior de X sea el último leído
  prevX = xinit;
  //se autmenta de 1 en 1 el valor de x para poder graficar
  xinit++;
  //se verifica si el valor de x es mayor o igual al ancho máximo de mi "plotter"
  if (xinit >= graphWidth)
  {
    //se pone el valor de x inicial en el valor establecido originalmente
    xinit = 4;
    //se limpia la pantalla
    pantalla.clearDisplay();
    //se llama a la función para volvera graficar los ejes
    drawejes();
    //se establece el valor de prevY en cero
    prevY=0;
  }
  //se establece el tiempo de espera entre una toma de datos y otra
  delay(sampleRate);
}
