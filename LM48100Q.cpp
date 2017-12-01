#include "Arduino.h"
#include "Wire.h"
#include "LM48100Q.h"

LM48100Q::LM48100Q() {}

void LM48100Q::begin() {
	Wire.begin();
	disable();
}

void LM48100Q::begin(const uint8_t address) {
	chipAddr = address;
	Wire.begin();
	disable();
}

uint8_t LM48100Q::enable() {
	modeRegisterShadow |= (1 << PWR_ON_BIT);
	return writeRegister(LM_REG_MODE, modeRegisterShadow);
}

uint8_t LM48100Q::disable() {
	modeRegisterShadow &= ~(1 << PWR_ON_BIT);
	return writeRegister(LM_REG_MODE, modeRegisterShadow);
}

uint8_t LM48100Q::setInput(uint8_t input) {

	if (input == IN_1) {
		modeRegisterShadow &= ~(1 << IN_2_BIT);
		modeRegisterShadow |= (1 << IN_1_BIT);
	}
	else if (input == IN_2) {
		modeRegisterShadow &= ~(1 << IN_1_BIT);
		modeRegisterShadow |= (1 << IN_2_BIT);
	}
	else if (input == MUX) {
		modeRegisterShadow |= (1 << IN_1_BIT);
		modeRegisterShadow |= (1 << IN_2_BIT);
	}
	else if (input == MUTE) {
		modeRegisterShadow &= ~(1 << IN_1_BIT);
		modeRegisterShadow &= ~(1 << IN_2_BIT);
	}	

	return writeRegister(LM_REG_MODE, modeRegisterShadow);
}

void LM48100Q::setVolume(uint8_t channel, uint8_t newVol) {

	uint8_t volRegister;

	if (newVol > 32 || newVol < 1) { return; } // out of range

	if (channel == IN_1) {
		volRegister = LM_VOL_1;
	}
	else if (channel == IN_2) {
		volRegister = LM_VOL_2;
	}
	else if (channel == MUX) {
		writeRegister(LM_VOL_1, newVol -1); // -1 since volume step one is 0x00
		volRegister = LM_VOL_2; // Write vol 1 and set register to vol 2, it'll be written later anyway
	}
	else { return; } // invalid channel


	writeRegister(volRegister, newVol -1); // -1 since volume step one is 0x00
}

/********** Private functions start ***********/

uint8_t LM48100Q::writeRegister(const uint8_t registerAddr, const uint8_t registerData) {

  	Wire.beginTransmission(chipAddr);
  	Wire.write(registerAddr);
  	Wire.write(registerData);
  	
	return Wire.endTransmission();
}
