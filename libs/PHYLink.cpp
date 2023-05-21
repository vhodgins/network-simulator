#include "PHYLink.h"
#include "Transceiver.h"
#include <cstdlib>

// Contains methods for the PHYLink class, which are implemented as logical busses that carry voltage values


PHYLink::PHYLink(bool d, int v, int i, Transceiver& t1, Transceiver& t2) : duplex(d), vProp(v), impedance(i) {
        coords[0] = t1.xcoord; coords[1] = t2.xcoord;       // Define start and end points for drawing, and distance calculation
        coords[2] = t1.ycoord; coords[3] = t2.ycoord;
        double dx = t1.xcoord - t2.xcoord;
        double dy = t1.ycoord - t2.ycoord;
        distance = std::sqrt(dx*dx + dy*dy);

        for (int j = 0; j < std::round(distance*(10.0/vProp)); ++j) {           // Queue length proportional to distance
            rx.push(0);
            tx.push(0);
        }
    }

void PHYLink::push_to_end(PortType end, int8_t voltage) {       // Pushes a "voltage" value to the RX or TX end of the link. 
    if (end == PortType::RX) {                                      // Yes it is duplex so theyre both rx and tx but I started with these conventions
        rx.push(voltage);                                               // and now i am sticking with it
    }
    else if (end == PortType::TX) {
        tx.push(voltage);
    }
    else {
        throw std::invalid_argument("Invalid PortType (PTE)");
    }
}

int8_t PHYLink::pop_from_end(PortType end) {                    // Pops from the end of the link queue / removes. 
    int8_t value;                                              
    if (end == PortType::RX && !rx.empty()) {
        value = tx.front();
        tx.pop();
    }
    else if (end == PortType::TX && !tx.empty()) {
        value = rx.front();
        rx.pop();
    }
    else {
        throw std::invalid_argument("Invalid PortType or Port is empty (PFE)");
    }
    int random = (rand() % 1000);
    if (random>=999){
        value = ~value & 1;
    }
    return value;
}


int8_t PHYLink::read_from_end(PortType end){                    // Reads without pops
    int8_t value;
    if (end == PortType::RX && !rx.empty()) {
        value = tx.front();
    }
    else if (end == PortType::TX && !tx.empty()) {
        value = rx.front();
    }
    else {
        throw std::invalid_argument("Invalid PortType or Port is empty (RFE)");
    }
    return value;
}

int8_t PHYLink::read_from_front(PortType end){              // Reads from other end
    int8_t value;
    if (end == PortType::RX && !rx.empty()) {
        value = rx.back();
    }
    else if (end == PortType::TX && !tx.empty()) {
        value = tx.back();
    }
    else {
        throw std::invalid_argument("Invalid PortType or Port is empty (RFF)");
    }
    return value;
}

// Animates little balls on the links to show propogation velocity
void PHYLink::updateAnimation(float elapsedTime) {
    // Calculate how much to move the circle along the line based on the elapsed time and the link speed
    float moveAmount = elapsedTime * 10* vProp / (distance);
    // Update the circle's position
    animatedPos += moveAmount;
    // If the circle has reached the end of the link, wrap it back to the beginning
    if (animatedPos > 1.0f) {
        animatedPos = 0.0f;
    }
}
