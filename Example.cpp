//
// Created by Bastian Wegge on 10.10.17.
//

#include "Example.h"

#include <SFML/Graphics.hpp>

class MyClass
{
public:

    MyClass(sf::RenderWindow& window) :
            m_window(window),
            m_text("My Text")
    {}

    void Draw()
    {
        m_window.Draw(m_text);
    }

private:

    sf::RenderWindow& m_window;
    sf::Text m_text;
};

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");

    MyClass myObject(window);

    while(window.IsOpen())
    {
        sf::Event ev;
        while(window.PollEvent(ev))
        {
            if(ev.Type == sf::Event::Closed)
                window.Close();
        }

        window.Clear();
        myObject.Draw();
        window.Display();
    }

    return 0;
}