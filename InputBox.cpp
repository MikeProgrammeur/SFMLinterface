#include <SFML/Graphics.hpp>
#include <iostream>
#define proportion 0.6
class InputBox{
    public:
    //initialisation
    InputBox(){}
    InputBox(sf::Color colorarg,int loc0,int loc1, int siz0, int siz1,sf::Font &font){
        //conversion
        sf::Vector2f x(loc0,loc1);
        sf::Vector2f v(siz0,siz1);
        isSelected=false;
        //affectation
        size=v;
        location=x;
        //textbox
        initTexts(font);
        //rectangle
        color=colorarg;
        initRectangles(loc0,loc1);

    };

    void initRectangles(int loc0, int loc1){// we init all the 3 rectangles that compose the widget
        //contour text init
        sf::Vector2f v1(size.x*proportion,size.y);
        contourText = sf::RectangleShape(v1);
        contourText.setPosition(loc0, loc1);
        contourText.setFillColor(color);
        contourText.setOutlineColor(sf::Color::Black);
        contourText.setOutlineThickness(2);
        //other buttons
        sf::Vector2f v2(size.x*(1-proportion),0.5*size.y);//both incr and decr have the same size
        //increase button init
        boxIncr = sf::RectangleShape(v2);
        boxIncr.setPosition(loc0+proportion*size.x, loc1);
        boxIncr.setFillColor(color);
        boxIncr.setOutlineColor(sf::Color::Black);
        boxIncr.setOutlineThickness	(2);
        //decrease button init
        boxDecr = sf::RectangleShape(v2);
        boxDecr.setPosition(loc0+proportion*size.x, loc1+0.5*size.y);
        boxDecr.setFillColor(color);
        boxDecr.setOutlineColor(sf::Color::Black);
        boxDecr.setOutlineThickness(2);
        //arrow increase init
            //for the proportion the height is 1/3 and the width is 1/3 and the triagnle is centered
        sf::ConvexShape arrowIncr(3);
        arrowIncr.setFillColor(sf::Color::Black);
            //we need to create the sf vector for the 3 points
        sf::Vector2f arrow0(location.x+size.x*(5/6),location.y+1/6*size.y);
        sf::Vector2f arrow1(location.x+size.x*(5/9),location.y+2/6*size.y);
        sf::Vector2f arrow2(location.x+size.x*(5/6),location.y+2/6*size.y);
        arrowIncr.setPoint(0,arrow0);
        arrowIncr.setPoint(1,arrow1);
        arrowIncr.setPoint(2,arrow2);


    };
    
    void initTexts(sf::Font &font){
        // the size of the text will be 80% of the height and the texts location is the corner + 10% of height
        valueText.setFont(font);
        unityText.setFont(font);
        valueText.setFillColor(sf::Color::Black);
        unityText.setFillColor(sf::Color::Black);
        valueText.setCharacterSize(0.8*size.y);
        unityText.setCharacterSize(0.8*size.y);
        sf::Vector2f tpos(location.x,location.y+0.10*size.y);
        valueText.setPosition(tpos);
        valueText.setString(std::to_string(value));

    };

    //getter & setter
    void setFont(sf::Font &font){
        valueText.setFont(font);
        unityText.setFont(font);
    };

    //render function
    void chooseColor(int i){
        //if selected we choose the brighter color
        if(i==0){
            contourText.setFillColor(color);
            boxIncr.setFillColor(color);
            boxDecr.setFillColor(color);
        }
        else if (i==1){
            contourText.setFillColor(sf::Color::White);
            boxIncr.setFillColor(color);
            boxDecr.setFillColor(color);
        }
        else if(i==2){
            contourText.setFillColor(color);
            boxIncr.setFillColor(sf::Color::White);
            boxDecr.setFillColor(color);
        }
        else{
            contourText.setFillColor(color);
            boxIncr.setFillColor(color);
            boxDecr.setFillColor(sf::Color::White);
        };

    };
    
    void drawTo(sf::RenderWindow &window){
        window.draw(contourText);
        window.draw(boxDecr);
        window.draw(boxIncr);
        window.draw(arrowIncr);
        window.draw(valueText);
        //window.draw(unityText);
    };

    float render(bool clicked,sf::RenderWindow &window){
        //this function render the button and return the current value of the button
        int detected = detect(window);
        chooseColor(detected);
        if(detected == 2 && clicked && not(isSelected==2)){
            value+=1;
        }
        else if(detected==3 && clicked && not(isSelected==3)){
            value-=1;
        }
        else if(detected==0&&clicked){
            //we need to read the input from the user
            isReading=true;
        };


        if(isReading){

        };


        if (clicked==0){
            isSelected=0;
        }
        else{
            isSelected=detected;
        };
        valueText.setString(std::to_string(value));//updating the value displayed
        drawTo(window);
        return value;
    };

    int detect(sf::RenderWindow &window){
        //detect which area of the button is selected
        //we define {0=unselected,1=text,2=increase,3=decrease}
        int result = 0;
        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;
        //coordinate of corners
        float minX = location.x;
        float minY = location.y;
        float frontiereX = location.x+proportion*size.x;//it is where the two incr/decr button start
        float frontiereY = location.y+0.5*size.y;//it is middle of the whole widget on y axis
        float maxX = minX+size.x;
        float maxY = minY+size.y;
        //we decide if the mouse is inside of one of the areas
        if(minX<=mouseX && mouseX<=frontiereX){//in the left part of the button
            if(minY<=mouseY && mouseY<=maxY){
                return 1;
            }
            else{
                return 0;
            };
        }
        else if(frontiereX<mouseX && mouseX<=maxX){//we are on the second half of the button
            if(minY<=mouseY && mouseY<frontiereY){//we are on incr
                return 2;
            }
            else if (frontiereY<=mouseY && mouseY<=maxY){//we are on decr
                return 3;
            }
            else{//we are out of the button
                return 0;
            };
        }
        else{//we are out of the button
            return 0;
        };

    };
    
    private:
    //geometric properties
    sf::Vector2f size;
    sf::Vector2f location;
    //texts
    int textSize;
    sf::Text unityText;
    sf::Text valueText;
    int isSelected = 0;
    bool isReading=false;// is true when the text area is clicked so the button read the input to change the value
    //value contained in the widget
    float value=0;
    float borneValue[2];
    //shapes and color
    sf::Color color;
    sf::RectangleShape contourText;//text input
    sf::RectangleShape boxIncr;//background for increase
    sf::RectangleShape boxDecr;//background for decrease 
    sf::RectangleShape arrowIncr;//arrow to increase by one the value
    sf::RectangleShape arroxDecr;//arrow to decrease by one the value
};