#include "MAX485.h"


MAX485::MAX485(
	HardwareSerial& hwSerial,
	uint8_t         transmissionEnablePin,
	uint32_t        baudrate  = 9600,
	uint16_t        config    = SERIAL_8N1,
	uint16_t        predelay  = 50,
	uint16_t        postdelay = 50
) :
	serial(hwSerial),
	transmissionEnablePin(transmissionEnablePin),
	serialBaudrate(baudrate),
	serialConfig(config),
	predelay(predelay),
	postdelay(postdelay)
{
}

void MAX485::begin()
{
	pinMode(transmissionEnablePin, OUTPUT);
	digitalWrite(transmissionEnablePin, LOW);

	serial.begin(serialBaudrate, serialConfig);
}

void MAX485::end()
{
	serial.end();

	digitalWrite(transmissionEnablePin, LOW);
	pinMode(transmissionEnablePin, INPUT);
}

int MAX485::available()
{
	return serial.available();
}

int MAX485::peek()
{
	return serial.peek();
}

int MAX485::read()
{
	return serial.read();
}

void MAX485::flush()
{
	return serial.flush();
}

size_t MAX485::write(uint8_t byte)
{
	if (!transmissionActive) {
		// setWriteError(); //TODO
		return 0;
	}

	return serial.write(byte);
}

void MAX485::beginTransmission()
{
	if (transmissionActive) return;

	setTransmitterMode();
	if (predelay) delayMicroseconds(predelay);

	transmissionActive = true;
}

void MAX485::endTransmission()
{
	if (!transmissionActive) return;

	serial.flush();
	if (postdelay) delayMicroseconds(postdelay);
	setReceiverMode();

	transmissionActive = false;
}

void MAX485::setReceiverMode()
{
	digitalWrite(transmissionEnablePin, LOW);
}

void MAX485::setTransmitterMode()
{
	digitalWrite(transmissionEnablePin, HIGH);
}
