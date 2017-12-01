#ifndef LM48100Q_h
#define LM48100Q_h


#define LM_REG_MODE 0x00
#define LM_REG_DIAG 0x01
#define LM_REG_FAULT 0x02
#define LM_VOL_1 0x03
#define LM_VOL_2 0x04

#define IN_1_BIT 2
#define IN_2_BIT 3
#define PWR_ON_BIT 4 

#define IN_1	0
#define IN_2	1
#define MUX	2
#define MUTE 3

class LM48100Q {

  public:

		LM48100Q();

		void begin();
		void begin(const uint8_t address);
		uint8_t enable();
		uint8_t disable();
		uint8_t setInput(uint8_t input);
		void setVolume(uint8_t channel, uint8_t newVol);

	private:
		uint8_t chipAddr = 0x7C;	// Default to address 0x7C (Address pin low)
		uint8_t modeRegisterShadow = 0;

		uint8_t writeRegister(const uint8_t registerAddr, const uint8_t registerData);
		
};

#endif
