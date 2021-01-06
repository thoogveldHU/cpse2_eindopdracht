#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Collection.hpp"
#include "NotMoveableCollection.hpp"
#include "Factory.hpp"
#include "Action.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "BloxBox");
    CollectionMoveables<42> collection = {}; //Items go here when the are created dynamically.
    shared_ptr<MoveableObject> active_object; //last selected object.
    auto defaultColor = sf::Color::Red; //Red would be the standard color of the selectors.

    // collection.add(make_shared<Circle>(sf::Vector2f{25,25}, 20, defaultColor)); //Selector for Circle
    // collection.add(make_shared<Rectangle>(sf::Vector2f{25,25}, sf::Vector2f{30,30}, defaultColor)); //Selector for Rect

    //--------------------SHAPE SELECTOR-------------------------------------------------------
    sf::RectangleShape squareBox(sf::Vector2f{20,20});
    squareBox.setPosition(25,0);
    squareBox.setFillColor(defaultColor);
    sf::CircleShape circleBox(10);
    circleBox.setPosition(25,25);
    circleBox.setFillColor(defaultColor);
    //---------------------COLOR SELECTORS-----------------------------------------------------
    sf::RectangleShape redBox(sf::Vector2f(20,20));
    redBox.setFillColor(sf::Color::Red);

    sf::RectangleShape greenBox(sf::Vector2f(20,20));
    greenBox.setFillColor(sf::Color::Green);
    greenBox.setPosition(0,25);

    sf::RectangleShape blueBox(sf::Vector2f(20,20));
    blueBox.setFillColor(sf::Color::Blue);
    blueBox.setPosition(0,50);

    sf::RectangleShape yellowBox(sf::Vector2f(20,20));
    yellowBox.setFillColor(sf::Color::Yellow);
    yellowBox.setPosition(0,75);

    sf::RectangleShape whiteBox(sf::Vector2f(20,20));
    whiteBox.setFillColor(sf::Color::White);
    whiteBox.setPosition(0,100);

    sf::RectangleShape purpleBox(sf::Vector2f(20,20));
    purpleBox.setFillColor(sf::Color::Magenta);
    purpleBox.setPosition(0,125);

    sf::RectangleShape cyanBox(sf::Vector2f(20,20));
    cyanBox.setFillColor(sf::Color::Cyan);
    cyanBox.setPosition(0,150);
    //---------------------------------------------------------------------------
    std::vector<sf::RectangleShape> colors = {redBox,greenBox,blueBox,yellowBox,whiteBox,purpleBox,cyanBox};

    // sf::Text text;
    // text.setString("Hello World");
    // sf::Font font;
    // font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    // text.setFont(font);
    // text.setCharacterSize(18);
    // text.setFillColor(sf::Color::White);
    // text.setPosition(50,10);

    
	Action actions[] = {Action(Keyboard::Left, [&]() { active_object->move(Vector2f(-2.0, 0.0)); std::cout << "Move Left \n"; }),
                      Action(Keyboard::Right, [&]() { active_object->move(Vector2f(+2.0, 0.0)); std::cout << "Move Right \n";}),
                      Action(Keyboard::Up, [&]() { active_object->move(Vector2f(0.0, -2.0)); std::cout << "Move Up \n"; }),
                      Action(Keyboard::Down, [&]() { active_object->move(Vector2f(0.0, +2.0)); std::cout << "Move Down \n"; })};


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                bool mouseIsClickedOnce = true;
                auto position = sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        //Is clicked somewhere on the left of the screen, the color selector for example, we dont make new object.
                        //Check the X and Y position of the mouse to do so.
                        //sets the colors of the 2 fields.
                        sf::Vector2f minVal = {0,0};
                        sf::Vector2f maxVal = {20,170};
                        sf::Vector2f minValSelector = {25,0};
                        sf::Vector2f maxValSelector = {25,50};

                        if( position.x >= minVal.x && position.x <= maxVal.x && position.y >= minVal.y && position.y <= maxVal.y)
                        {
                            std::cout << "user clicked on a color." << std::endl;
                            for(auto x: colors)
                            {
                                auto globalBounds = x.getGlobalBounds();
                                if(globalBounds.contains(position.x,position.y))
                                {
                                    squareBox.setFillColor(x.getFillColor());
                                    circleBox.setFillColor(x.getFillColor());
                                }
                            }
                        } 

                        //else if
                        //the user clicked on the circle or square, to make a new object.
                        //circle should be stuck to the mouse until the user clicks again
                        //this will drop the circle on that position.
                        else if(position.x >= minValSelector.x && position.x <= maxValSelector.x && position.y >= minValSelector.y && position.y <= maxValSelector.y){
                            std::cout << "Clicked on either the circle or the square." << std::endl;
                        }

                        //Did the user click in the middle of the screen and select an object that is moveable?
                        else{
                            std::cout << "Clicked somewhere on the field" << std::endl;
                            std::cout << "coord :" << position.x << " " << position.y << std::endl;
                            active_object = collection.getObject(sf::Mouse::getPosition(window));
                        }


                        // std::cout << "Memory Adress of active_object: " << active_object << std::endl;
                        // std::cout << "Height of the Object : " << active_object->getBound().height << std::endl;
                        // std::cout << "top of the Object : " << active_object->getBound().top << std::endl;
                        // std::cout << "left of the Object : " << active_object->getBound().left << std::endl;
                        // std::cout << "widht of the Object : " << active_object->getBound().width << std::endl;

                    }



            }
            for (auto& Action : actions) 
            {
                Action();
            }
        }
        window.clear();

        for(auto x : colors){
            window.draw(x);
        }
        window.draw(squareBox);
        window.draw(circleBox);
        collection.drawObjects(window);
        // window.draw(text);
        window.display();

    }
    return 0;
}

//for use in wsl use this before running:
//export DISPLAY=$(ip route|awk '/^default/{print $3}'):0.0