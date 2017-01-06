#include "testapi.h"

test(api_i2c)
{
    int buffer;
    API_COMPILE(buffer=I2C_BUFFER_LENGTH);
    (void)buffer;
}

test(api_wiring_pinMode) {

    PinMode mode = PIN_MODE_NONE;
    API_COMPILE(mode=getPinMode(D0));
    API_COMPILE(pinMode(D0, mode));
    (void)mode;
}

test(api_wiring_analogWrite) {
    API_COMPILE(analogWrite(D0, 50));
    API_COMPILE(analogWrite(D0, 50, 10000));
}

test(api_wiring_wire_setSpeed) {
    API_COMPILE(Wire.setSpeed(CLOCK_SPEED_100KHZ));
}

void D0_callback() {
}

test(api_wiring_interrupt) {
    API_COMPILE(interrupts());
    API_COMPILE(noInterrupts());

    API_COMPILE(attachInterrupt(D0, D0_callback, RISING));
    API_COMPILE(detachInterrupt(D0));

    class MyClass {
        public:
            void handler() { }
    } myObj;

    API_COMPILE(attachInterrupt(D0, &MyClass::handler, &myObj, RISING));


    //API_COMPILE(attachSystemInterrupt(SysInterrupt_TIM1_CC_IRQ, D0_callback));

    API_COMPILE(attachInterrupt(D0, D0_callback, RISING, 14));
    API_COMPILE(attachInterrupt(D0, D0_callback, RISING, 14, 0));
    API_COMPILE(attachInterrupt(D0, &MyClass::handler, &myObj, RISING, 14));
    API_COMPILE(attachInterrupt(D0, &MyClass::handler, &myObj, RISING, 14, 0));
}

test(api_wiring_usartserial) {
    API_COMPILE(Serial.halfduplex(true));
    API_COMPILE(Serial.halfduplex(false));

    API_COMPILE(Serial.blockOnOverrun(false));
    API_COMPILE(Serial.blockOnOverrun(true));

    API_COMPILE(Serial.availableForWrite());

    API_COMPILE(Serial.begin(9600, SERIAL_8N1));
    API_COMPILE(Serial.end());
    API_COMPILE(Serial.begin(9600, SERIAL_8N2));
    API_COMPILE(Serial.end());

    API_COMPILE(Serial.begin(9600, SERIAL_8E1));
    API_COMPILE(Serial.end());
    API_COMPILE(Serial.begin(9600, SERIAL_8E2));
    API_COMPILE(Serial.end());

    API_COMPILE(Serial.begin(9600, SERIAL_8O1));
    API_COMPILE(Serial.end());
    API_COMPILE(Serial.begin(9600, SERIAL_8O2));
    API_COMPILE(Serial.end());


    API_COMPILE(Serial.begin(9600, SERIAL_9N1));
    API_COMPILE(Serial.end());
    API_COMPILE(Serial.begin(9600, SERIAL_9N2));
    API_COMPILE(Serial.end());
}

test(api_wiring_usbserial) {
    API_COMPILE(SerialUSB.blockOnOverrun(false));
    API_COMPILE(SerialUSB.blockOnOverrun(true));
    API_COMPILE(SerialUSB.availableForWrite());
}

void TIM3_callback()
{
}

test(api_wiring_system_interrupt) {
    //API_COMPILE(attachSystemInterrupt(SysInterrupt_TIM3_IRQ, TIM3_callback));
    //API_COMPILE(detachSystemInterrupt(SysInterrupt_TIM3_IRQ));
}

void externalLEDHandler(uint8_t r, uint8_t g, uint8_t b) {
}

class ExternalLed {
    public:
        void handler(uint8_t r, uint8_t g, uint8_t b) {
        }
} externalLed;

test(api_rgb) {
    bool flag; uint8_t value;
    API_COMPILE(flag=RGB.controlled());
    API_COMPILE(RGB.control(true));
    API_COMPILE(RGB.color(255,255,255));
    API_COMPILE(RGB.color(RGB_COLOR_WHITE));
    API_COMPILE(RGB.blink(255,255,255,1000));
    API_COMPILE(RGB.blink(RGB_COLOR_WHITE, 1000));
    API_COMPILE(RGB.breath(255,255,255,1000));
    API_COMPILE(RGB.breath(RGB_COLOR_WHITE, 1000));
    (void)flag; (void)value; // unused
}

test(api_servo_trim)
{
    Servo servo;
    servo.setTrim(234);
}

test(api_wire)
{
    API_COMPILE(Wire.begin());
    API_COMPILE(Wire.reset());
    API_COMPILE(Wire.end());
}

test(api_map)
{
    map(0x01,0x00,0xFF,0,255);
}

/**
 * Ensures that we can stil take the address of the global instances.
 *
 */
test(api_wiring_globals)
{
    void* ptrs[] = {
        &SPI,
#ifdef configWIRING_SPI1_ENABLE
        &SPI1,
#endif
#ifdef configWIRING_SPI2_ENABLE
        &SPI2,
#endif
        &Serial,
        &Wire,
#ifdef configWIRING_WIRE1_ENABLE
        &Wire1,
#endif
#ifdef configWIRING_WIRE2_ENABLE
        &Wire2,
#endif
#ifdef configWIRING_WIRE3_ENABLE
        &Wire3,
#endif
#ifdef configWIRING_USARTSERIAL1_ENABLE
        &Serial1,
#endif
#ifdef configWIRING_USARTSERIAL2_ENABLE
        &Serial2,
#endif
#ifdef configWIRING_USARTSERIAL3_ENABLE
        &Serial3,
#endif
#ifdef configWIRING_USARTSERIAL4_ENABLE
        &Serial4,
#endif
#ifdef configWIRING_USARTSERIAL5_ENABLE
        &Serial5,
#endif
        &EEPROM,
    };
    (void)ptrs;
}

