#ifndef DEBUGMODE_H
#define DEBUGMODE_H

#define DEBUG_MODE 0
#define RELEASE_MODE 1

class Console {
    private:
        int mode;

    public:
        // constructor, destructor
        Console(int argc, char **argv);
        ~Console();
        void set(int argc, char **argv);
        void run();
        void log(ostream& stream);
};

#endif