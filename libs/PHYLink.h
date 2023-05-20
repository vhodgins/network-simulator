#ifndef PHYLINK_H
#define PHYLINK_H

#include <queue>
#include <iostream>
#include <cstdint>
#include <cmath>
#include "PortType.h"
using namespace std;

class Transceiver;

class PHYLink {             // Link Class
    private:
        // Member parameters
        bool duplex;
        int vProp;
        int impedance;
        double distance;

        // PHYLink Queue Defs
        queue<int8_t> rx;
        queue<int8_t> tx;

    public:
        PHYLink(bool d, int v, int i, Transceiver& t1, Transceiver& t2);      // Constructor
        void push_to_end(PortType end, int8_t voltage);  // Push values through link
        int8_t pop_from_end(PortType end);
        float coords[4] =  {0,0,0,0};
        int8_t read_from_end(PortType end);

};

#endif // Include Guard