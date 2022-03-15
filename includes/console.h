#ifndef DEBUGMODE_H
#define DEBUGMODE_H

#include <string.h>
#include <iostream>
using namespace std;

#define DEBUG_MODE 0
#define RELEASE_MODE 1

class Console {
    private:
        static int mode;
        static Console* instance;
        Console(){};

    public:
        static Console* set(int argc, char **argv) {
            for (int i = 0; i < argc; i++) {
                if (strcmp(argv[i], "--debug") == 0 || strcmp(argv[i], "-d") == 0) {
                    cout << "Debug Mode On" << endl;
                    mode = 0;
                    return instance;
                }
            }
            cout << "Debug Mode Off" << endl;
            mode = 1;
            return instance;
        };
        static Console* getInstance() {
            if (instance == 0) {
                instance = new Console();
            }
            return instance;
        }
        static void run();
        static void log(string message);
};

#endif