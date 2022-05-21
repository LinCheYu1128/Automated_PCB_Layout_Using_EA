#ifndef MOEAD_PARAMETER_H
#define MOEAD_PARAMETER_H

class MOEAD_Parameter {
    private:
        int kExpTime = 1;
        int kGeneration = 80;
        int kPopSize = 200;
        // parent selection
        int k_Tournament = 5;
        // crossover
        double kCrossoverRate = 0.3;
        int kCrossoverTime = kPopSize / 2;
        // mutation
        double kMutationRate = 0.9;
        double kAngleChangeRate = 0.1;
        double kSideChangeRate = 0.3;
        // evaluation
        double kAreaUtilTarget = 0.95;
        // neighbor
        int kNeighborNumber = 5;

    public:
        // constructor, destructor
        MOEAD_Parameter();
        ~MOEAD_Parameter();

        // getter
        int getExpTime();
        int getGeneration();
        int getPopSize();
        int getTournamentNum();
        double getCrossoverRate();
        double getCrossoverTime();
        double getMutationRate();
        double getAngleChangeRate();
        double getSideChangeRate();
        double getAreaUtilTarget();
        int getNeighborNumber();
        
        // setter
        void setExpTime(int kExpTime);
        void setGeneration(int kGeneration);
        void setPopSize(int kPopSize);
        void setTournamentNum(int k_Tournament);
        void setCrossoverRate(double kCrossoverRate);
        void setCrossoverTime(double kCrossoverTime);
        void setMutationRate(double kCrossoverRate);
        void setAngleChangeRate(double kCrossoverRate);
        void setSideChangeRate(double kCrossoverRate);
        void setAreaUtilTarget(double kCrossoverRate);

        // printer
};

#endif