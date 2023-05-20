#include <iostream>
#include "libs/Transceiver.h"
#include "libs/PHYLink.h"

int main() {
    // Create two transceivers
    Transceiver t1(1, 0, 0);
    Transceiver t2(1, 5, 0);

    // Create a link between transceivers
    PHYLink link(true, 1, 0, t1, t2);

    // Connect the link to transceivers
    t1.connect_link(&link, PortType::TX);
    t2.connect_link(&link, PortType::RX);

    int8_t t1val, t2val;


    for (int i = 0; i < 10; i++) {
        // t1 pushes a value to its port
        t1.push_to_port(0, i);
        // t2 pushes a different value to its port
        t2.push_to_port(0, i+10);

        t2val = t2.read_from_port(0);
        std::cout << "Received value at T2: " << static_cast<int>(t2val) << "\n";
   
        // Check if t1's port has data to read
        t1val = t1.read_from_port(0);
        std::cout << "Received value at T1: " << static_cast<int>(t1val) << "\n";
        
    }

    return 0;
}
