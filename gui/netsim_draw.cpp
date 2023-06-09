#include "netsim_draw.h"
#include <cmath>

#define XBIAS 100
#define YBIAS 100
#define SIZEX 80
#define SIZEY 80

void drawTransceiver(sf::RenderWindow& window, Transceiver& transceiver, int id, const sf::Font& font){
    sf::RectangleShape rectangle(sf::Vector2f(SIZEX,SIZEY));     // Create a RectangleShape class object from the sf library called rectangle
    rectangle.setPosition(sf::Vector2f(transceiver.xcoord+XBIAS - SIZEX/2, transceiver.ycoord+YBIAS - SIZEY/2));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1);
    rectangle.setFillColor(sf::Color::White);
    window.draw(rectangle);


    for (auto p : transceiver.ports){
        if (p.type==PortType::EMPTY){
            break;
        }

        PHYLink phyLink = *p.link;
        int location = (p.type==PortType::TX)?1:-1;

        float direction = atan2(phyLink.coords[3] - phyLink.coords[2], phyLink.coords[1] - phyLink.coords[0]);
        float ybias = location*sin(direction) * (SIZEY / 2  );
        float xbias = location*cos(direction) * (SIZEX/2 );

        // Convert the int ID to string
        std::string id_str = std::to_string(transceiver.last_sent_bit(p.portnumber)) + " | " + std::to_string(transceiver.port_read(p.portnumber));

        // Create a text object
        sf::Text text;
        text.setFont(font);
        text.setString(id_str);
        text.setCharacterSize(16);  // in pixels, not points!
        text.setFillColor(sf::Color::Blue);

        // Center the text inside the rectangle
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        text.setPosition(sf::Vector2f(transceiver.xcoord+XBIAS+xbias, transceiver.ycoord+YBIAS+ybias));
        // Draw the text
        window.draw(text);

    }




    // Convert the int ID to string
    std::string id_str = std::to_string(id);

    // Create a text object
    sf::Text text;
    text.setFont(font);
    text.setString(id_str);
    text.setCharacterSize(18);  // in pixels, not points!
    text.setFillColor(sf::Color::Red);

    // Center the text inside the rectangle
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(transceiver.xcoord+XBIAS, transceiver.ycoord+YBIAS));

    // Draw the text
    window.draw(text);
}


void drawPHYLink(sf::RenderWindow& window, PHYLink& phyLink, int id){
    float direction = atan2(phyLink.coords[3] - phyLink.coords[2], phyLink.coords[1] - phyLink.coords[0]);
    float ybias = sin(direction) * (SIZEY / 2);
    float xbias = cos(direction) * (SIZEX / 2);
    sf::Vertex line[] = {
            {{phyLink.coords[0] + XBIAS + xbias, phyLink.coords[2] + YBIAS + ybias}, sf::Color::Black},
            {{phyLink.coords[1] + XBIAS - xbias, phyLink.coords[3] + YBIAS - ybias}, sf::Color::Black}};
    window.draw(line, 2, sf::Lines);

    // Calculate the current position of the circle along the line
    float x = phyLink.coords[0] + (phyLink.coords[1] - phyLink.coords[0]) * phyLink.animatedPos;
    float y = phyLink.coords[2] + (phyLink.coords[3] - phyLink.coords[2]) * phyLink.animatedPos;

    // Draw the circle at the current position
    sf::CircleShape circle(5);
    circle.setPosition(x + XBIAS - 5, y + YBIAS - 5);
    circle.setFillColor(sf::Color::Red);
    window.draw(circle);

        // Calculate the current position of the circle along the line
    x = phyLink.coords[0] + (phyLink.coords[1] - phyLink.coords[0]) * (1-phyLink.animatedPos);
    y = phyLink.coords[2] + (phyLink.coords[3] - phyLink.coords[2]) * (1-phyLink.animatedPos);

    circle.setPosition(x + XBIAS - 5, y + YBIAS - 5);
    circle.setFillColor(sf::Color::Green);
    window.draw(circle);


}