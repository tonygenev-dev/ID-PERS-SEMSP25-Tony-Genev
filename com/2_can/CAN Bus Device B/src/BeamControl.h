#pragma once
#include <Arduino.h>

enum BeamState : uint8_t {
    BEAM_OFF = 0x00,
    BEAM_ON  = 0x01
};

void beamInit(uint8_t pin);
void setBeamState(BeamState state);
