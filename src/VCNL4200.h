/**
    This is a library written for the VCNL4200
    
    Written by Andris Jenerts @ MB, March 2021

    VCNL4200 integrates a high sensitivity long distance
    proximity sensor (PS), ambient light sensor (ALS), and
    940 nm IRED into one small package.

    This library handles the VCNL4200 register setup and is able to
    make proximity and ambient light  readings

    Development environment specifics:
    Arduino IDE 1.8.10

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY

    Copyright (c) 2021 Andris Jenerts. All rights reserved.

    This work is licensed under the terms of the MIT license.  
    For a copy, see <https://opensource.org/licenses/MIT>.
*/

#ifndef VCNL4200_H

#define VCNL4200_H
#include <Arduino.h>
#include <Wire.h>

//// VCNL4200 PARAMATETERS ////
enum VCNL4200_PARAM
{
    VCNL4200_DEV_ADDRESS = 0x51,

    ALS_ON = 0x00,
    ALS_SD = 0x01, //ALS shut down

    ///Ambent light sensor integration time in ms
    ///for more info check datasheet page 13
    ALS_IT_50 = 0x00,
    ALS_IT_100 = 0x01,
    ALS_IT_200 = 0x02,
    ALS_IT_400 = 0x03,

    ///ALS interrupt settings
    ALS_INT_SW_ALS = 0x00,   //ALS channel interrupt
    ALS_INT_SW_WCH = 0x01,   //White channel interrupt
    ALS_INT_DISABLED = 0x00, //ALS disabled
    ALS_INT_EN = 0x01,       // ALS enabled

    ///ALS interrupt persistance setting - how much consecutive measuremnts
    ///have to be made in interrupt rnge to trigger ALS interrupt
    ALS_PERS_1 = 0x00,
    ALS_PERS_2 = 0x01,
    ALS_PERS_4 = 0x02,
    ALS_PERS_8 = 0x03,

    PS_ON = 0x00,
    PS_SD = 0x01,

    ///LED current settings
    LED_CURRENT_50mA = 0x00,
    LED_CURRENT_75mA = 0x01,
    LED_CURRENT_100mA = 0x02,
    LED_CURRENT_120mA = 0x03,
    LED_CURRENT_140mA = 0x04,
    LED_CURRENT_160mA = 0x05,
    LED_CURRENT_180mA = 0x06,
    LED_CURRENT_200mA = 0x07,

    ///On / Off duty ratio for IRED
    PS_DUTY_160 = 0x00,
    PS_DUTY_320 = 0x01,
    PS_DUTY_640 = 0x02,
    PS_DUTY_1280 = 0x03,

    ///Measurement integration time
    PS_IT_1T0 = 0x00,
    PS_IT_1T5 = 0x01,
    PS_IT_2T0 = 0x02,
    PS_IT_4T0 = 0x03,
    PS_IT_8T0 = 0x04,
    PS_IT_9T0 = 0x05,

    ///Interupt persistance setting - how many consecutive measruements
    ///have to be made in interupt range to trigger PS interupt
    PS_PERS_1 = 0x00,
    PS_PERS_2 = 0x01,
    PS_PERS_3 = 0x02,
    PS_PERS_4 = 0x03,

    /// PS iterupt modes
    PS_INT_DISABLED = 0x00,
    PS_INT_CLOSING = 0x01,
    PS_INT_AWAY = 0x02,
    PS_INT_CLOSING_AWAY = 0x03

};

class VCNL4200
{
public:
    VCNL4200();
    VCNL4200(uint8_t newDevAddr);

    /**
     * check if sensor is connected with option to reset all settings
     * @return true if sensor is connected
     */
    bool begin(bool resetToDefault = false);

    /**
     * check if sensor is conected
     * @return true if sensor is connected
     */
    bool isConnected();

    /**
     * Set ALS Power Mode
     * @param alsPowerModeSetting ALS_CONF (0x00 Low byte) 0 bit
     */
    void setALSPowerMode(bool alsPowerModeSetting);

    /**
     * Set PS Power Mode
     * @param psPowerModeSetting PS_CONF1 (0x03 Low byte) 0 bit
     */
    void setPSPowerMode(bool psPowerModeSetting);

    /**
     * Set PS Reolution
     * @param psResolutionSetting PS_CONF2 (0x03 High byte) 3 bit
     *                            HIGH -> 16 bit output
     *                            LOW -> 12 bit output
     */
    void setPSResolution(bool psResolutionSetting);

    /**
     * Set PS Duty on / off ratio
     * @param psDutySetting PS_CONF1 (0x03 Low byte) 7:6 bits
     */
    void setPSDuty(uint8_t psDutySetting);

    /**
     * Set PS Integration Time
     * @param psITSetting PS_CONF1 (0x03 Low byte) 3:1 bits
     */
    void setPSIT(uint8_t psITSetting);

    /**
     * Set PS Led current
     * @param psLEDISetting PS_MS (0x04 High byte) 2:0 bits
     */
    void setPSLEDI(uint8_t psLEDISetting);

    

    

    /**
     * Read PS output data from PS_DATA
     */
    uint16_t readPSData();

    /**
     * Read ALS output data from ALS_DATA
     */
    uint16_t readALSData();

    /**
     * Read White output data from WHITE_DATA
     */
    uint16_t readWhiteData();

    /**
     * Read 16 bits (two 8-bit registers)
     * @param cmdCode Command code from which to request data
     * @return return 16-bits with DataByteHigh first and then DataByteLow
     */
    uint16_t readCommand(int8_t cmdCode);

    /**
     * Write 16 bits (two 8-bit registers)
     * @param cmdCode Command code to which write data
     * @param value 16-bit value to write in command
     */
    void writeToCommand(uint8_t cmdCode, uint16_t value);

private:
    int8_t _devAddr = VCNL4200_DEV_ADDRESS; //default if not changed
    uint16_t _currentSetting;
};

#endif