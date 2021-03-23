VCNL4200 High Sensitivity Long Distance Proximity and Ambient Light Sensor Library
===========================================================

Th VCNL4200  integrates a high sensitivity long distance proximity sensor (PS), ambient light sensor (ALS), and 940 nm IRED into one small package. The 16-bit high resolution ALS offers excellent sensing capabilities with sufficient selections to fulfill most applications whether a dark or high transparency lens design. 
VCNL4200 offers individual programmable high and low threshold interrupt features for the best utilization of resources and power
saving on the microcontroller. For the 12-bit / 16-bit proximity sensing function, VCNL4200 has a built-in intelligent cancellation scheme that eliminates background light issues. The persistence feature prevents false judgment of proximity sensing due to ambient light noise.

You can find
-------------------

* **/examples** - TO DO
* **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - TO DO
* **library.properties** - TO DO

How it works?
------------------

start by including libraries and making VCNL4200 object

    #include <VCNL4200.h>
    #include <Wire.h>

    VCNL4200 sens;

VCNL4200 have single I2C address `0x51` that is used by default of the library, no need to specify it. 
If you use extra hardware to change I2C address, you can creat object like this ad specify new address e.g. 0x66: 

    VCNL4200 sens(0x66);
    
library doesn't call `Wire.begin()` you should do it yourself in `void setup()`.
    
    
### Basic functions

`sens.begin()` - must be called to initialize sensor, <br>
`sens.begin(true)` - can be used to rest all settings to default.<br>

`sens.wake()` - sensor is woken from sleep mode, once this function is called sensor starts performing measurements <br>

`sens.sleep()`- sensor is powered down in sleep mode.

`sens.readPSData()` - returns `unsigned int` value of last proximity sensor measurment value.<br>

`sens.readALSData()` - returns `unsigned int` value of last ambient light sensor measurment value.<br>

`sens.readWhiteData()` - returns `unsigned int` value of last ambient light white channel sensor measurment value.<br>


### Configuring sensor
There are many things you can configure on VCNL4200.<br> 
Vishay has made [app note](https://www.vishay.com/docs/84327/designingvcnl4200.pdf), about how to implement sensor in specific application.<br>

**Bolded** settings are default ones.
<br>

**Resolution**

There are low and high resoluiton modes for VCNL4200<br>
use function `sens.setPSResolution(value)` for choosing one

value | HEX | resolution
------|-----|-----------
**LOW** | 0x00 | 12-bit
HIGH | 0x01 | 16-bit

<br>

**LED current**

Use function `sens.setLedCurrent(value)` as an value you can use on of the specified values from list below <br>

value | HEX | LED current 
---------------|-----|------------
**LED_CURRENT_50mA** | 0x00 | 50mA
LED_CURRENT_75mA | 0x01 | 75mA
LED_CURRENT_100mA | 0x02 | 100mA
LED_CURRENT_120mA | 0x03 | 120mA
LED_CURRENT_140mA | 0x04 | 140mA
LED_CURRENT_160mA | 0x05 | 160mA
LED_CURRENT_180mA | 0x06 | 180mA
LED_CURRENT_200mA | 0x06 | 200mA

<br>

**PS duty**

set prefered PS duty using `sens.setPSDuty(value)` <br>

value | HEX | PS Duty | measurement time
------|-----|---------|-----------------
**PS_DUTY_160** | 0x00 | 1/160 | *unknown*
PS_DUTY_320 | 0x01 | 1/320 | *unknown*
PS_DUTY_640 | 0x02 | 1/640 | *unknown*
PS_DUTY_1280 | 0x03 | 1/1280 | *unknown* 

<br>

**Integration time**

set PS_IT using `sens.setPSIT(value)` <br>
value | HEX | PS_IT
------|-----|------
**PS_IT_1T0** | 0x00 | 1T
PS_IT_1T5 | 0x01 | 1.5T
PS_IT_2T0 | 0x02 | 2T
PS_IT_4T0 | 0x03 | 4T
PS_IT_8T0 | 0x04 | 8T
PS_IT_9T0 | 0x05 | 9T

<br>


<br>

TODO LIST
------------------
- [ ] Example code
- [ ] Arduino Library release
- [ ] ALS_CONF
- [ ] PS_CONF3 and PS_MS - sunlight immunity features
- [ ] PS_CANC
- [ ] ALS Interrupt
- [ ] PS Interrupt


License Information
-------------------

This code is _**open source**_! 

Please review the LICENSE.md file for license information.

Please use, reuse, and modify these files as you see fit. Please maintain attribution to my name - Andris Jenerts and release anything derivative under the same license.

Distributed as-is; no warranty is given.

