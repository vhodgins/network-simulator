#ifndef NETSIMDRAW_H
#define NETSIMDRAW_H


#include <SFML/Graphics.hpp>
#include "../libs/Transceiver.h"
#include "../libs/PHYLink.h"
#include "../libs/PortType.h"

void drawTransceiver(sf::RenderWindow& window, const Transceiver& transceiver);
void drawPHYLink(sf::RenderWindow& window, const PHYLink& phyLink);

#endif // Include Guard