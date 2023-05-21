// Transceiver.cpp

#include "Transceiver.h"
#include "PHYLink.h"
#include <stdexcept>

Transceiver::Transceiver(uint8_t n, int x, int y) : xcoord(x), ycoord(y) {          // Constructor function, defines n ports and coordinate pair
    for (uint8_t i = 0; i < n; i++) {
        Port port;
        port.portnumber = i;
        ports.push_back(port);
    }
}

void Transceiver::connect_link(PHYLink* link, PortType type) {      // Connects transceiver to link and specifies which end 
    for (Port& port : ports) {
        if (port.type == PortType::EMPTY) {
            port.link = link;
            port.type = type;
            return;
        }
    }
    throw std::runtime_error("All ports are occupied (CL)");
}

void Transceiver::disconnect_port(uint8_t portnum) {                // Removes references to link from a port
    if (portnum < ports.size()) {
        ports[portnum].link = nullptr;
        ports[portnum].type = PortType::EMPTY;
    }
    else {
        throw std::out_of_range("Invalid port number (DP)");
    }
}

void Transceiver::push_to_port(uint8_t portnum, int8_t dataval) {               // Pushes data into a port to be sent across a link
    if (portnum < ports.size()) {
        if (ports[portnum].link != nullptr) {
            ports[portnum].link->push_to_end(ports[portnum].type, dataval);
        }
        else {
            throw std::runtime_error("Port is not connected or not a transmit port (PTP)");
        }
    }
    else {
        throw std::out_of_range("Invalid port number (PTP)");
    }
}

int8_t Transceiver::read_from_port(uint8_t portnum) {                   // Reads data from a port and pops its value 
    if (portnum < ports.size()) {
        if (ports[portnum].link != nullptr) {
            return ports[portnum].link->pop_from_end(ports[portnum].type);
        }
        else {
            throw std::runtime_error("Port is not connected or not a receive port (RFP)");
        }
    }
    else {
        throw std::out_of_range("Invalid port number (RFP)");
    }
}

int8_t Transceiver::port_read(uint8_t portnum) const{                       // Reads data without popping
    if (portnum < ports.size()) {
        if (ports[portnum].link != nullptr) {
            return ports[portnum].link->read_from_end(ports[portnum].type);
        }
        else {
            throw std::runtime_error("Port is not connected or not a receive port");
        }
    }
    else {
        throw std::out_of_range("Invalid port number (PR)");
    }
}


int8_t Transceiver::last_sent_bit(uint8_t portnum){                       // Reads data without popping
    if (portnum < ports.size()) {
        if (ports[portnum].link != nullptr) {
            return ports[portnum].link->read_from_front(ports[portnum].type);
        }
        else {
            throw std::runtime_error("Port is not connected or not a receive port (LSB)");
        }
    }
    else {
        throw std::out_of_range("Invalid port number (LSB)");
    }
}