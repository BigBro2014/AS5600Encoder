
#include <stdint.h>


class AS5600Encoder
{
public:
    // Constructor
    // resolution must be power of 2, e.g., 1024, 4096, etc. 
    AS5600Encoder(int pin, int resolution, bool reverse);

    // Reset absolute pos
    void reset();

    // Update encoder value / absolute pos, should be called periodically
    void update();

    // Get buffered absolute pos
    int32_t getAbslutePos();

    // Get buffered encoder value 
    uint16_t getEncoderVal();


private:
    int _resolution;   // Must be power of 2
    int _pin;
    bool _reverse;
    uint16_t _encoder_val;
    int32_t _absolute_pos;
};

