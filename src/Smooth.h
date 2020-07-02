#ifndef SMOOTH_H
#define SMOOTH_H
#include <Arduino.h>

class Smooth{
  private:
    const double RATE;
    double previous;
  public:
    Smooth(double rate);
    double operator()(long current);
};

class SchmittRound{
    private:
        long previous;
    public:
        SchmittRound();
        long operator()(double current);
};

class SchmittCeil{
    private:
        long previous;
    public:
        SchmittCeil();
        long operator()(double current);
};

class SchmittFloor{
    private:
        long previous;
    public:
        SchmittFloor();
        long operator()(double current);
};

class IsCHANGED{
  private:
    long previous;
  public:
    IsCHANGED();
    boolean operator()(long current);
};

class IsINCREASED{
  private:
    long previous;
  public:
    IsINCREASED();
    boolean operator()(long current);
};

class IsDECREASED{
  private:
    long previous;
  public:
    IsDECREASED();
    boolean operator()(long current);
};

#endif