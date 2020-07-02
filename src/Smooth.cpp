#include "Smooth.h"

Smooth::Smooth(double rate): RATE(rate)
        , previous(0.0) {}

double Smooth::operator()(long current){
  return previous = previous + RATE * ( double(current) - previous ) ;
}

SchmittRound::SchmittRound(): previous(0.0) {
}

long SchmittRound::operator()(double current){
    if( abs( current - previous ) < 0.75 ) return previous;
    return previous = long(round(current));
}

SchmittCeil::SchmittCeil(): previous(0.0){
}

long SchmittCeil::operator()(double current){
    const auto DIFF = current - previous;
    if( -1.0 < DIFF &&  DIFF  < 0.5 ) return previous;
    return previous = long(ceil(current));
}

SchmittFloor::SchmittFloor(): previous(0.0) {
}

long SchmittFloor::operator()(double current){
    const auto DIFF = current - previous;
    if( -0.5 < DIFF &&  DIFF  < 1.0  ) return previous;
    return previous = long(floor(current));
}

IsCHANGED::IsCHANGED(): previous(0) {
}

boolean IsCHANGED::operator()(long current) {
  const boolean IS_CHANGED = current != previous;
  previous = current;
  return IS_CHANGED;
}

IsINCREASED::IsINCREASED(): previous(0) {
}

boolean IsINCREASED::operator()(long current) {
  const boolean IS_INCREASED = current > previous;
  previous = current;
  return IS_INCREASED;
}

IsDECREASED::IsDECREASED(): previous(0) {
}

boolean IsDECREASED::operator()(long current) {
  const boolean IS_DECREASED = current < previous;
  previous = current;
  return IS_DECREASED;
}