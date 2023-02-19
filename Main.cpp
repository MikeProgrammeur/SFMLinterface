#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.cpp"
#include "ScrollBar.cpp"
using namespace std;
int main()
{
    //making window
    sf::RenderWindow window(sf::VideoMode(800, 600), "PRO3600");

    //loading font
    sf::Font arialFont;

    if (!arialFont.loadFromFile("./src/arial.ttf"))
    {
        std::cout<<"impossible de charger la font";
    }
    //creating button
    Button testButton(14,sf::Color::White,false,10,10,80,40);
    testButton.setFont(arialFont);

    Button testButton2(14,sf::Color::White,false,10,70,80,40);
    testButton2.setFont(arialFont);
    ScrollBar testBar(sf::Color::White,false,10,130,400,20,0);

    //input
    bool mouseClick = false;
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen())
    {
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            mouseClick = (event.type == sf::Event::MouseButtonPressed);

        }
        mouseClick=sf::Mouse::isButtonPressed(sf::Mouse::Left);
        window.clear(sf::Color(20,20,20));

        bool pressed = testButton.render(mouseClick,window);
        bool pressed2 = testButton2.render(mouseClick,window);
        testBar.render(mouseClick,window);
        window.display();
        //std::cout<<pressed;
        if(pressed){
            std::cout<<"button 1 pressed\n";
        };
        if(pressed2){
            std::cout<<"button 2 pressed\n";
        };
        while (clock.getElapsedTime().asSeconds()<0.016)
        {
            int a = 2;
        }
    }
    std::cout<<"Hello world";
    return 0;
}