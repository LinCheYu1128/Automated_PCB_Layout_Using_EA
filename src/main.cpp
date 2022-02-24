<<<<<<< HEAD
#include "Layout.h"
#include "GA/GA.h"
#include <iostream>
#include <ctime>
using namespace std;



int main () {
    srand((unsigned)time(0));
    
    GA* GA_optimizer = new GA();

    cout << "complete GA_optimizer" << endl;

    cout << "Hello we are testing git pull upstream" << endl;
    
    vector<Layout*> parent = GA_optimizer->selectParent();
    
    delete GA_optimizer;

    return 0;
=======
#include "Layout.h"
#include "GA.h"
#include "console.h"
#include <iostream>
#include <ctime>
using namespace std;

int main (int argc, char **argv) {
    srand((unsigned)time(0));
    
    Console::set(argc, argv);
    Console::run();

    return 0;
>>>>>>> f52d2a3388d715e43ca5329c86d0f7be7a975b05
}