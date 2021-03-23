/**
    This is a library written for the VCNL4200
    
    Written by Andris Jenerts @ MB, March 2021

    VCNL4200 integrates a high sensitivity long distance
    proximity sensor (PS), ambient light sensor (ALS), and
    940 nm IRED into one small package.

    This library handles the VCNL4200 register setup and is able to
    make proximity and ambient light readings

    Development environment specifics:
    Arduino IDE 1.8.10

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY

    Copyright (c) 2021 Andris Jenerts. All rights reserved.

    This work is licensed under the terms of the MIT license.  
    For a copy, see <https://opensource.org/licenses/MIT>.
*/

#include "VCNL4200.h"

VCNL4200::VCNL4200() {}
VCNL4200::VCNL4200(uint8_t _newDevAddr)
{
    _devAddr = _newDevAddr;
}

bool VCNL4200::begin(bool _resetToDefault)
{
    if (isConnected())
    {
        if (_resetToDefault)
        {
            setPSResolution(0x00);
            setPSDuty(PS_DUTY_160);
            setPSIT(PS_IT_1T0);
            setPSLEDI(LED_CURRENT_100mA);
        }
        return true;
    }
    return false;
}

void VCNL4200::wake()
{
    _currentSetting = readCommand(0x03);
    _currentSetting = _currentSetting & 0xFFFE;
    _currentSetting = _currentSetting | 0x00;
    writeToCommand(0x03, _currentSetting);
}

void VCNL4200::sleep()
{
    _currentSetting = readCommand(0x03);
    _currentSetting = _currentSetting & 0xFFFE;
    _currentSetting = _currentSetting | 0x01;
    writeToCommand(0x03, _currentSetting);
}

void VCNL4200::setALSPowerMode(bool _alsPowerModeSetting)
{
    _currentSetting = readCommand(0x00);
    _currentSetting = _currentSetting & 0xFFFE;
    _currentSetting = _currentSetting | _alsPowerModeSetting;
    writeToCommand(0x00, _currentSetting);
}


void VCNL4200::setPSResolution(bool _psResolutionSetting)
{
    _currentSetting = readCommand(0x03);
    _currentSetting = _currentSetting & 0xF7FF;
    _currentSetting = _currentSetting | (_psResolutionSetting << 11);
}

void VCNL4200::setPSDuty(uint8_t _psDutySetting)
{
    _currentSetting = readCommand(0x03);
    _currentSetting = _currentSetting & 0xFF3F;
    _currentSetting = _currentSetting | (_psDutySetting << 6);
    writeToCommand(0x03, _currentSetting);
}

void VCNL4200::setPSIT(uint8_t _psITSetting)
{
    _currentSetting = readCommand(0x03);
    _currentSetting = _currentSetting & 0xFFFD;
    _currentSetting = _currentSetting | (_psITSetting << 1);
    writeToCommand(0x03, _currentSetting);
}

void VCNL4200::setLedCurrent(uint8_t _psLEDISetting)
{
    _currentSetting = readCommand(0x04);
    _currentSetting = _currentSetting & 0xF8FF;
    _currentSetting = _currentSetting | (_psLEDISetting << 8);
    writeToCommand(0x04, _currentSetting);
}




uint16_t VCNL4200::readPSData()
{
    return readCommand(0x08);
}

uint16_t VCNL4200::readALSData()
{
    return readCommand(0x09);
}

uint16_t VCNL4200::readWhiteData()
{
    return readCommand(0x0A);
}




bool VCNL4200::isConnected()
{
    Wire.beginTransmission(_devAddr);
    if (Wire.endTransmission() == 0) //ack
    {
        if (readCommand(0x0E) == 0x1058) //compare ID
        {
            return true;
        }
        return false;
    }
    return false;
}

uint16_t VCNL4200::readCommand(int8_t _cmdCode)
{

    Wire.beginTransmission(_devAddr);
    Wire.write(_cmdCode);
    Wire.endTransmission(false);

    Wire.requestFrom(_devAddr, 0x02); // request 2 bytes (each command contains 2 registers)

    if (Wire.available() != 0x02)
    {
        //TO DO throw some kind of error
        return 0;
    }

    byte Lbyte = Wire.read();
    byte Hbyte = Wire.read();

    uint16_t value = (Hbyte << 8) | Lbyte; // compose two bytes in 16-bit variable with High Byte first
    return value;                          // return 16-bits
}

void VCNL4200::writeToCommand(uint8_t _cmdCode, uint16_t _value)
{
    Wire.beginTransmission(_devAddr);
    Wire.write(_cmdCode);

    Wire.write(uint8_t(_value & 0xff)); // LOW byte
    Wire.write(uint8_t(_value >> 8));   //HIGH byte
    Wire.endTransmission();
    //delay(5);
}
