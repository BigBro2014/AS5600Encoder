
#include <stdint.h>


class AS5600Encoder
{
public:
    // Constructor
    AS5600Encoder(int pin, bool reverse);

    // Reset absolute pos
    void reset();

    // Update encoder value / absolute pos
    void update();

    // Get buffered absolute pos
    int32_t getAbslutePos();

    // Get buffered encoder value 
    uint16_t getEncoderVal();


private:
    int _pin;
    bool _reverse;
    uint16_t _encoder_val;
    int32_t _absolute_pos;
};

