#include "BeamControl.h"

static uint8_t beamPin;

void beamInit(uint8_t pin) {
    beamPin = pin;
    pinMode(beamPin, OUTPUT);
    digitalWrite(beamPin, LOW);
}

void setBeamState(BeamState state) {
    digitalWrite(beamPin, state == BEAM_ON ? HIGH : LOW);
}
