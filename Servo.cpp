/*
 * MIT License
 */


/* 
 * File:   Servo.cpp
 * Author: josh  - JKI757
 * 
 * Created on May 24, 2020, 12:21 AM
 */

#include "Servo.hpp"

Servo::Servo() = default;

Servo::~Servo() {
    this->Drive_PWM->stop();
    GPIO::cleanup();

}
 Servo::Servo(const unsigned char pin){
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(this->pin, GPIO::OUT, GPIO::HIGH);
    this->Drive_PWM = std::make_shared<GPIO::PWM>(pin, 1500);
    //1500 is centered for a normal steering servo for RC car
    this->minUs = 1000;
    this->maxUs = 2000;


}
 Servo::Servo(const unsigned char pin, const unsigned short minUs, const unsigned short maxUs){
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(this->pin, GPIO::OUT, GPIO::HIGH);
    this->Drive_PWM = std::make_shared<GPIO::PWM>(pin, 1500);
    //1500 is centered for a normal steering servo for RC car
    this->minUs = minUs;
    this->maxUs = maxUs;
    
}
Servo::Servo(const unsigned char pin, const unsigned short minUs, const unsigned short maxUs, 
                                        const unsigned short mapMin, const unsigned short mapMax){
    //mapMin and mapMax are the expected range of values coming in as commands 
    //if you use these values, use the writeMappedValue method with a value in the range (mapMin, mapMax)
    //and the value will be mapped to (minUs, maxUs)
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(this->pin, GPIO::OUT, GPIO::HIGH);
    this->Drive_PWM = std::make_shared<GPIO::PWM>(pin, 1500);
    //1500 is centered for a normal steering servo for RC car
    this->minUs = minUs;
    this->maxUs = maxUs;
    this->mapMin = mapMin;
    this->mapMax = mapMax;
    
}

void Servo::writeAngle(const unsigned short angle){\
    const unsigned char mappedVal = mapAngle(angle);
    this->Drive_PWM->ChangeFrequency(1.0/mappedVal);
    this->Drive_PWM->start(.5);
}
void Servo::writeUs(const unsigned short microseconds){
     this->Drive_PWM->ChangeFrequency(1.0/microseconds);
     this->Drive_PWM->start(.5);
     
}

unsigned char Servo::map(const short val){
        if ((val <= mapMax) && (val >= mapMin) && (mapMax != mapMin)) {\
            return round(((float) val - (float) mapMin) / ((float) mapMax - (float) mapMin) * ((float) minUs - (float) maxUs) + (float) minUs);
        } else return -1;
    }
unsigned char Servo::mapAngle(const short val){
        if ((val <= 360) && (val >= 0)) {\
            return round(((float) val - (float) 0) / ((float) 360 - (float) 0) * ((float) minUs - (float) maxUs) + (float) minUs);
        } else return -1;
    }

void Servo::writeMappedValue(const short val){
    //takes a value mapped between minRange and maxRange to minUs and maxUs and calculates a microsecond value from there
    const unsigned char mappedVal = map(val);
    this->Drive_PWM->ChangeFrequency(1.0/mappedVal);
    this->Drive_PWM->start(.5);
}
