
#include <Arduino.h>

#include "AS5600Encoder.h"


// Constructor
AS5600Encoder::AS5600Encoder(int pin, int adc_resolution, bool reverse)
{
    uint16_t encoder_val;

    _pin = pin;
    _reverse = reverse;
    _resolution = adc_resolution;

    pinMode(pin, INPUT_ANALOG);
    analogRead(_pin);   // Discard first result
    encoder_val = analogRead(_pin);

    noInterrupts();
    _encoder_val = encoder_val;
    _absolute_pos = 0;
    interrupts();
}


// Reset absolute pos
void AS5600Encoder::reset()
{
    noInterrupts();
    _absolute_pos = 0;
    interrupts();
}


// Update encoder value / absolute pos, should be called periodically
void AS5600Encoder::update()
{
    uint16_t encoder_val;
    int32_t pos;
    int16_t diff;

    encoder_val = analogRead(_pin);

    if (_reverse)
        encoder_val = _resolution - encoder_val;

    noInterrupts();
    diff = encoder_val - _encoder_val;
    pos = _absolute_pos;
    interrupts();

    if (diff > _resolution / 2)
    {
        pos += diff - _resolution;
    }
    else if (diff < -(_resolution / 2))
    {
        pos += diff + _resolution;
    }
    else
    {
        pos += diff;
    }

    noInterrupts();
    _encoder_val = encoder_val;
    _absolute_pos = pos;
    interrupts();
}


// Get buffered absolute pos
int32_t AS5600Encoder::getAbslutePos()
{
    uint32_t pos;

    noInterrupts();
    pos = _absolute_pos;
    interrupts();

    return pos;
}


// Get buffered encoder value 
uint16_t AS5600Encoder::getEncoderVal()
{
    uint16_t enc;

    noInterrupts();
    enc = _encoder_val;
    interrupts();

    return enc;
}
