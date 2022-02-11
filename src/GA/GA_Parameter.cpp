#include "GA/GA_Parameter.h"
#include <iostream>
using namespace std;

GA_Parameter::GA_Parameter() {
}

GA_Parameter::~GA_Parameter() {
}

int GA_Parameter::getExpTime() {
    return this->kExpTime;
}

int GA_Parameter::getGeneration() {
    return this->kGeneration;
}

int GA_Parameter::getPopSize() {
    return this->kPopSize;
}

int GA_Parameter::getTournamentNum() {
    return this->k_Tournament;
}

double GA_Parameter::getCrossoverRate() {
    return this->kCrossoverRate;
}

double GA_Parameter::getCrossoverTime() {
    return this->kCrossoverTime;
}

double GA_Parameter::getMutationRate() {
    return this->kMutationRate;
}

double GA_Parameter::getAngleChangeRate() {
    return this->kAngleChangeRate;
}

double GA_Parameter::getSideChangeRate() {
    return this->kSideeChangeRate;
}

double GA_Parameter::getAreaUtilTarget() {
    return this->kAreaUtilTarget;
}