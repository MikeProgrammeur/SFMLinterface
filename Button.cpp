#include <SFML/Graphics.hpp>
#include <iostream>
class Button{
    public:
    //initialisation
    Button(){}
    Button(int tsize,sf::Color color,bool sel,int loc0,int loc1, int siz0, int siz1){
        //conversion
        sf::Vector2f x(loc0,loc1);
        //textbox
        textbox.setColor(color);
        textbox.setCharacterSize(tsize);
        isSelected=sel;
        textbox.setString("text de test");
        textbox.setPosition(x);
        //affectation
        sf::Vector2f v(siz0,siz1);
        size=v;
        location[0]=loc0;
        location[1]=loc1;
        //rectangle
        initRectangle(loc0,loc1);
    };

    void initRectangle(int loc0, int loc1){
        contour = sf::RectangleShape(size);
        contour.setPosition(loc0, loc1);
        contour.setFillColor(sf::Color(80,220,155));
        contour.setOutlineColor(sf::Color::White);
    };

    //getter & setter
    void setFont(sf::Font &font){
        textbox.setFont(font);
    };
    void changePosition(float pos[2]){
        sf::Vector2f v1(pos[0],pos[1]);
        textbox.setPosition(v1);
        contour.setPosition(v1);
    };

    //render function
    void chooseColor(bool b){
        //if selected we choose the brighter color
        if(b){
            contour.setFillColor(sf::Color(25,205,65));
        }
        else{
            contour.setFillColor(sf::Color(25,150,65));
        };

    };
    void drawTo(sf::RenderWindow &window){
        window.draw(contour);
        window.draw(textbox);
    };

    bool render(bool clicked,sf::RenderWindow &window){
        bool detected = detect(window);
        chooseColor(detected);
        bool result = (clicked && detected && not(isSelected));
        isSelected=clicked;
        drawTo(window);
        return result;
    };
    bool detect(sf::RenderWindow &window){
        bool result = true;
        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;
        //coordinate of corners
        float minX = location[0];
        float minY = location[1];
        float maxX = minX+size.x;
        float maxY = minY+size.y;
        //we check if the mouse is inside the frame
        result&=(minX<mouseX);
        result&=(mouseX<maxX);
        result&=(minY<mouseY);
        result&=(mouseY<maxY);
        return result;
    };
    
    private:
    int textSize;
    sf::Vector2f size;
    int location[2];
    sf::Text textbox;
    sf::Color color;
    bool isSelected = false;
    sf::RectangleShape contour;

};