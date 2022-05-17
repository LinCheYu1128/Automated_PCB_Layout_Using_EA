#include "MOEAD_Parameter.h"
#include <iostream>
using namespace std;

MOEAD_Parameter::MOEAD_Parameter() {
}

MOEAD_Parameter::~MOEAD_Parameter() {
}

int MOEAD_Parameter::getExpTime() {
    return this->kExpTime;
}

int MOEAD_Parameter::getGeneration() {
    return this->kGeneration;
}

int MOEAD_Parameter::getPopSize() {
    return this->kPopSize;
}

int MOEAD_Parameter::getTournamentNum() {
    return this->k_Tournament;
}

double MOEAD_Parameter::getCrossoverRate() {
    return this->kCrossoverRate;
}

double MOEAD_Parameter::getCrossoverTime() {
    return this->kCrossoverTime;
}

double MOEAD_Parameter::getMutationRate() {
    return this->kMutationRate;
}

double MOEAD_Parameter::getAngleChangeRate() {
    return this->kAngleChangeRate;
}

double MOEAD_Parameter::getSideChangeRate() {
    return this->kSideChangeRate;
}

double MOEAD_Parameter::getAreaUtilTarget() {
    return this->kAreaUtilTarget;
}

int MOEAD_Parameter::getNeighborNumber() {
    return this->kNeighborNumber;
}