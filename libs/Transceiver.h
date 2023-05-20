#ifndef TRANSCIEVER_H
#define TRANSCIEVER_H

#include <vector>
#include <cstdint>
#include "PortType.h"
using namespace std;

class PHYLink;  // Forward declaration

struct Port {
    uint8_t portnumber;
    PHYLink* link;
    PortType type;

    Port() : link(nullptr), type(PortType::EMPTY){}
};


class Transceiver {
    private: 
    public:
        std::vector<Port> ports; 
        int xcoord;
        int ycoord;
        Transceiver(uint8_t n, int x, int y);

        // Connect link to next available port in ports vector
        void connect_link(PHYLink* link, PortType type);
        void disconnect_port(uint8_t portnum);
    
        void push_to_port(uint8_t portnum, int8_t dataval);
        int8_t read_from_port(uint8_t portnum);

        int8_t port_read(uint8_t portnum) const;
};


#endif  // Include Guard
