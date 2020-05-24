/*
 * MIT License
 */

/* 
 * File:   Servo.hpp
 * Author: josh - JKI757
 *
 * Created on May 24, 2020, 12:21 AM
 */

#pragma once 

#include <JetsonGPIO.h>
#include <memory>
#include <cmath>
class Servo {
public:
    Servo();
    Servo(const Servo& orig);
    virtual ~Servo();
    
    Servo(const unsigned char pin);
    Servo(const unsigned char pin, const unsigned short minUs, const unsigned short maxUs);
    Servo(const unsigned char pin, const unsigned short minUs, const unsigned short maxUs, const unsigned short mapMin, const unsigned short mapMax);
    unsigned char mapAngle(const short val);
    void writeAngle(const unsigned short angle);
    void writeUs(const unsigned short microseconds);
    void writeMappedValue(const short val);


private:
    unsigned char pin; 
    unsigned short angle;
    unsigned short microseconds;
    unsigned short minUs;
    unsigned short maxUs;
    short mapMin;
    short mapMax;
    std::shared_ptr<GPIO::PWM> Drive_PWM;
    unsigned char map(const short val);

};


