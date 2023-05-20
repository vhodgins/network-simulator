#ifndef NETSIMDRAW_H
#define NETSIMDRAW_H


#include <SFML/Graphics.hpp>
#include "../libs/Transceiver.h"
#include "../libs/PHYLink.h"
#include "../libs/PortType.h"

void drawTransceiver(sf::RenderWindow& window, const Transceiver& transceiver, int id, const sf::Font& font);
void drawPHYLink(sf::RenderWindow& window, const PHYLink& phyLink, int id);

#endif // Include Guard