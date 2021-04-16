#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <string.h>

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "_ftoa.h"
#include "_atoi.h"
#include "_atof.h"


#define Vref 3.3
#define VperAmp 0.110               // 110mV/A ACS711KLCTR-12AB-T
#define ACS711Soffset 1.657         // 1.657
#define R1 390.0                    // K ohm
#define R2 2.285                    // 39 k ohm 2.39
#define R3 2.7                      // k ohm
#define R23 ((R2 * R3) / (R2 + R3)) // parallel
#define denominator (R2 / (R1 + R2))
// #define denominator (R23 / (R1 + R23))
#define AMC1200Gain 8.0
#define R1gain 1.15  // K ohm
#define R2gain 0.715 // K ohm
#define GAIN R1gain / R2gain

bool digit = 0;
uint8_t calibrate_mode = 0;
uint8_t incomingByte = 0;
// string incomingString = "";

float g_Voltage;
float g_Current;
float g_Number;
char g_Str[20];
const char *g_String;
char Str1[10];
char Str2[10];

struct Calibration {
        float incoming1;
        float incoming2;
        float volt1;
        float volt2;
        float slope;
        float intercept;
}; // Calibration

Calibration cali;

void InitConsole(void) {
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
  MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
  MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
  UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
  UARTStdioConfig(0, 115200, 16000000);
}
void InitADC(void) {
  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2);
  ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_D | ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
  ADCSequenceEnable(ADC0_BASE, 3);
  ADCIntClear(ADC0_BASE, 3);
}
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count) {
  while (ui32Count--) {
    MAP_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
  }
}

int main(void) {

  uint32_t pui32ADC0Value[1];

  // Setup the system clock to run at 40 MHz from PLL with crystal reference
  MAP_SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
  // Initialize the UART.
  InitConsole();
  InitADC();

  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

  InitConsole();
  MAP_IntMasterEnable();

  while (1) {
    ADCProcessorTrigger(ADC0_BASE, 3);
    while (!ADCIntStatus(ADC0_BASE, 3, false)) {
    }
    ADCIntClear(ADC0_BASE, 3);
    ADCSequenceDataGet(ADC0_BASE, 3, pui32ADC0Value);
    g_Voltage = (pui32ADC0Value[0] * (2 * Vref / 4096)) - Vref;
    g_Voltage = g_Voltage / (denominator);
    g_Voltage = (g_Voltage / (AMC1200Gain * GAIN));
    _ftoa(g_Voltage, Str1, 2);
    // printf("\"%s\"\n", res);
    // string a_Voltage = "pi is " + to_string(g_Voltage);
    // cout<< "pi = "<< pi << endl;
    // snprintf(Str1, sizeof(Str1), "%.3fA", g_Voltage);
    // sprintf(Str1,"%.3f", g_Voltage);
    // std::string orbits ("686.97 365.24");
    // std::string::size_type sz;     // alias of size_t
    // float mars = std::stof (orbits,&sz);
    // float earth = std::stof (orbits.substr(sz));
   
    // strcpy(g_Str, "98993489");
    strcpy(g_Str, "365.95");
    // int test = _atoi(g_Str);
    // int test = _atoi("365.65");
    g_Number = _atof(g_Str);
    _ftoa(g_Number, g_Str, 2);

    // UARTprintf("AIN0 - AIN1 =          \r");
    // UARTprintf("AIN0 - AIN1 = %s\r\n", Str1);
    UARTprintf("String %s\r\n", g_Str);
    // UARTprintf("String %s\r\n", ss);

    SysCtlDelay(SysCtlClockGet() / 12);

    while (MAP_UARTCharsAvail(UART0_BASE)) {
      //
      // Read the next character from the UART and write it back to the UART.
      //
      MAP_UARTCharPutNonBlocking(UART0_BASE, MAP_UARTCharGetNonBlocking(UART0_BASE));
      // strcpy(str, "Hello World");

      //
      // Blink the LED to show a character transfer is occuring.
      //
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

      //
      // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
      //
      SysCtlDelay(SysCtlClockGet() / (1000 * 3));

      //
      // Turn off the LED
      //
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
    }
  }
}
