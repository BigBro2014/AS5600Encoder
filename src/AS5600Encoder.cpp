
#include <Arduino.h>

#include "AS5600Encoder.h"


#define TICKS_PER_TURN 4096


// Constructor
AS5600Encoder::AS5600Encoder(int pin, bool reverse)
{
    _pin = pin;
    _reverse = reverse;

    pinMode(pin, INPUT_ANALOG);
    analogRead(_pin);   // Discard first result

    noInterrupts();
    _encoder_val = analogRead(_pin);
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
        encoder_val = TICKS_PER_TURN - encoder_val;

    noInterrupts();
    diff = encoder_val - _encoder_val;
    pos = _absolute_pos;
    interrupts();

    if (diff > TICKS_PER_TURN / 2)
    {
        pos += diff - TICKS_PER_TURN;
    }
    else if (diff < -(TICKS_PER_TURN / 2))
    {
        pos += diff + TICKS_PER_TURN;
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
