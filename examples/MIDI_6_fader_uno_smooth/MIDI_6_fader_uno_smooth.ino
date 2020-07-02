// MIDI faders using A-curve VRs to make B-curve outputs.
// input pins : A0 ~ A5
// output pin : 1 (Serial TX) for DIN MIDI OUT, or you can use USB MIDI with MOCO-LUFA.
// output MIDI CC: 25 ~ 30 


#include <Smooth.h>

constexpr byte CHANNEL = 0;
constexpr double REACT_RATE = 0.2;

constexpr auto INS_N = 6;

struct Fader{
  const int PIN;
  const byte CC;
  Smooth smooth;
  SchmittFloor schmittFloor;
  IsCHANGED isCHANGED;
  
  Fader(int pin, byte cc) : PIN(pin)
    , CC(cc)
    , smooth( REACT_RATE )
    , schmittFloor()
    , isCHANGED()
    {}
};

Fader FADERS[ INS_N ] {
  Fader(0, 25)
  , Fader(1, 26)
  , Fader(2, 27)
  , Fader(3, 28)
  , Fader(4, 29)
  , Fader(5, 30)
};

long mapAToB(long v ) {
  if(v <=  14) return map(v,   0,   17,   0,  136);
  if(v <=  39) return map(v,  17,   39, 136,  290);
  if(v <= 188) return map(v,  39,  189, 290,  515);
  if(v <= 479) return map(v, 189,  479, 515,  752);
  if(v <= 991) return map(v, 479,  991, 752,  991);
  return v;
}

int doWhenChanged(Fader& f, const long DATA ) {
  if( f.isCHANGED(DATA) ){
    txMidi( 0xB0|CHANNEL, f.CC, byte(DATA) );
  }
  return DATA;
}

void txMidi(const byte& MESSAGE, const byte& CC_NUM, const byte& VALUE){

    Serial.write( MESSAGE );
    Serial.write( CC_NUM );
    Serial.write( VALUE );
    Serial.flush();
}

void setup() {
  Serial.begin(31250);
}

void loop() {
  for( auto&& f : FADERS ){
    doWhenChanged(f,  
      f.schmittFloor(  
        f.smooth( mapAToB( analogRead(f.PIN) ) ) / 8.0 
      ) 
    );
    
    
  }
  delay(2);
}
