# Smooth for Arduino
Functions for smoothing data, especially good for analogRead().
##Description
Smooth has 7 simple function objects.

+ "Smooth" : returns exponential moving average(double) from incoming data(long).
+ "SchmittRound", "SchmittCeil", "SchmittFloor" : almost same as round,ceil,or floor, but they ignore small change of data like the Shmitt triger. input:double, return:long.
+ "IsCHANGED" : returns whether incoming data(long) is changed from previous data.
+ "IsINCREASED" : returns whether incoming data(long) is larger than previous data.
+ "IsDECREASED" : returns whether incoming data(long) is less than previous data.


## Installation
[Download ZIP](https://github.com/ttatsf/Smooth/archive/master.zip) and [follow instructions here.](https://www.arduino.cc/en/Guide/Libraries)

## Typical usage

```
#include <Smooth.h>

//  set reaction rate :
const double REACT_RATE_0 = 0.2;  // from 0.0 (no reaction)
                            //  up to 1.0 (just current data, no average)

//  Instantiate function objects :
Smooth smooth0(REACT_RATE_0);
SchmittRound schmittRound0;
SchmittCeil schmittCeil0;
SchmittFloor schmittFloor0;
IsCHANGED isCHANGED0;  

//  set reaction rate :
const double REACT_RATE = 0.2;

//  Instantiate object arrays :
Smooth smooth[4] = { REACT_RATE
    , REACT_RATE
    , REACT_RATE
    , REACT_RATE
};
SchmittRound schmittRound[4];
SchmittCeil schmittCeil[4];
SchmittFloor schmittFloor[4];
IsCHANGED isCHANGED[4];

const int PIN_0 = 0;
const int PIN[4]={1, 2, 3, 4};

void setup(){
    Serial.begin(115200);
}
void loop(){
  //  regular pattern :
  const int RAW = analogRead(PIN_0);
  const double SMOOTHED = smooth0(RAW);
  if (isCHANGED0(long(SMOOTHED))) {
    //  Do anything you want only when the data changed.
    printData(PIN_0, RAW, SMOOTHED
        , schmittRound0(SMOOTHED)
        , schmittCeil0(SMOOTHED)
        , schmittFloor0(SMOOTHED)
    );
  }

  //  regular pattern for array :
  for (int i = 0; i < 4; i++) {
    const int RAW = analogRead(PIN[i]);
    const double SMOOTHED = smooth[i](RAW);
    if (isCHANGED[i](long(SMOOTHED))) {
      //  Do anything you want only when the data changed.
        printData(PIN[i], RAW, SMOOTHED
            , schmittRound[i](SMOOTHED)
            , schmittCeil[i](SMOOTHED)
            , schmittFloor[i](SMOOTHED)
        );
    }
  }
  delay(2);
}

void printData(int n, int raw, double smoothed, long rounded, long ceiled, long floored){
    Serial.print(n);
    Serial.print(" : ");
    Serial.print(raw);
    Serial.print(", ");
    Serial.print(smoothed);
    Serial.print(", ");
    Serial.print(rounded);
    Serial.print(", ");
    Serial.print(ceiled);
    Serial.print(", ");
    Serial.print(floored);
    Serial.println();
    
}
```




# License
This code is available under the [MIT License](http://opensource.org/licenses/mit-license.php).
