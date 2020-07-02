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
    const int SMOOTHED = smooth[i](RAW);
    if (isCHANGED[i](SMOOTHED)) {
      //  Do anything you want only when the data changed.
        printData(PIN[i], RAW, SMOOTHED
            , schmittRound[i](SMOOTHED)
            , schmittCeil[i](SMOOTHED)
            , schmittFloor[i](SMOOTHED)
        );
    }
  }
  delay(10);
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
