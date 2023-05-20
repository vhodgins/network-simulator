#include "PHYLink.h"
#include "Transceiver.h"

PHYLink::PHYLink(bool d, int v, int i, Transceiver& t1, Transceiver& t2) : duplex(d), vProp(v), impedance(i) {
        coords[0] = t1.xcoord; coords[1] = t2.xcoord;
        coords[2] = t1.ycoord; coords[3] = t2.ycoord;
        double dx = t1.xcoord - t2.xcoord;
        double dy = t1.ycoord - t2.ycoord;
        distance = std::sqrt(dx*dx + dy*dy);

        for (int j = 0; j < std::round(distance); ++j) {
            rx.push(0);
            tx.push(0);
        }
    }

void PHYLink::push_to_end(PortType end, int8_t voltage) {
    if (end == PortType::RX) {
        rx.push(voltage);
    }
    else if (end == PortType::TX) {
        tx.push(voltage);
    }
    else {
        throw std::invalid_argument("Invalid PortType");
    }
}

int8_t PHYLink::pop_from_end(PortType end) {
    int8_t value;
    if (end == PortType::RX && !rx.empty()) {
        value = rx.front();
        rx.pop();
    }
    else if (end == PortType::TX && !tx.empty()) {
        value = tx.front();
        tx.pop();
    }
    else {
        throw std::invalid_argument("Invalid PortType or Port is empty");
    }
    return value;
}


int8_t PHYLink::read_from_end(PortType end){
    int8_t value;
    if (end == PortType::RX && !rx.empty()) {
        value = rx.front();
    }
    else if (end == PortType::TX && !tx.empty()) {
        value = tx.front();
    }
    else {
        throw std::invalid_argument("Invalid PortType or Port is empty");
    }
    return value;
}
