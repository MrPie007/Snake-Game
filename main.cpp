#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
int speed_of_updates = 500;
bool can_change_dir=0;
vector<RectangleShape>snake;
RectangleShape fruity(Vector2f(40,40));

char snake_dir='R';
sf::RenderWindow window(sf::VideoMode(600, 600), "My window");
void init_snake()
{
    RectangleShape rect(Vector2f(38,38));
    rect.setOutlineThickness(2.f);
    rect.setOutlineColor(sf::Color(0, 0, 0));
    snake.push_back(rect);
    snake.push_back(rect);
    snake[0].setPosition(Vector2f(-40,0));
   /* snake.push_back(rect);
    snake.push_back(rect);
    snake.push_back(rect);
    snake.push_back(rect);
    snake.push_back(rect);
    snake.push_back(rect);
    snake.push_back(rect);
    snake.push_back(rect);*/
    snake[snake.size()-1].setFillColor(Color(255,0,0));
}
void draw_snake()
{
    string title="SNAKE, Score = ";
    title+=to_string(snake.size()*72);
    window.setTitle(title);
    /*sf::Text text;
    Font font;
    font.loadFromFile("Arial.ttf");
    text.setFont(font);
    text.setString("Hello world");
    text.setCharacterSize(24);

    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    window.draw(text);*/
    for(int i=0;i<snake.size();i++)
    {
        window.draw(snake[i]);
    }
    window.draw(fruity);
}
void grow_snake()
{
    RectangleShape rect(Vector2f(38,38));
    rect.setOutlineThickness(2.f);
    rect.setOutlineColor(sf::Color(0, 0, 0));
    rect.setPosition(snake[0].getPosition());
    reverse(snake.begin(),snake.end());
    snake.push_back(rect);
    reverse(snake.begin(),snake.end());
}
void spawn_fruit()
{

    vector<pair<int,int>>vtobe;
    for(int i=40;i<=400;i+=40)
    {
        for(int j=40;j<=400;j+=40)
        {
            vtobe.push_back({i,j});

        }
    }

    random_shuffle(vtobe.begin(),vtobe.end());
    for(int x=0;x<vtobe.size();x++)
    {
        bool f=1;
        int i=vtobe[x].first;
        int j=vtobe[x].second;
        for(int k=0;k<snake.size();k++)
        {
            if(i == snake[k].getPosition().x && j == snake[k].getPosition().y)
            {
                f=0;
            }
        }
        if(f)
        {
            fruity.setPosition(Vector2f(i,j));
            return;
        }
    }


}

void advance_snake()
{
    can_change_dir=1;
    RectangleShape rect(Vector2f(40,40));
    Vector2f v = snake[snake.size()-1].getPosition();
    if(snake_dir == 'R')
    {
        v.x+=40;
    }
    if(snake_dir == 'D')
    {
        v.y+=40;
    }
    if(snake_dir == 'L')
    {
        v.x-=40;
    }
    if(snake_dir == 'U')
    {
        v.y-=40;
    }
    for(int i=0;i+1<snake.size();i++)
    {
        snake[i].setPosition(snake[i+1].getPosition());
    }
    snake[snake.size()-1].setPosition(v);
    if(snake.back().getPosition() == fruity.getPosition())
    {
        grow_snake();
        spawn_fruit();
    }
    cout<<snake.back().getPosition().x<<" "<<snake.back().getPosition().y<<endl;

}

bool did_i_eat_myself()
{
    //snake.back is the head of the snake
    for(int i=0;i+1<snake.size();i++)
    {
        if(snake.back().getPosition() == snake[i].getPosition())
        {
            return 1;
        }
    }
    if(snake.back().getPosition().x<0 || snake.back().getPosition().x>600)return 1;
    if(snake.back().getPosition().y<0 || snake.back().getPosition().y>600)return 1;
    return 0;

}
void snake_movement()
{
    if(Keyboard::isKeyPressed(Keyboard::F))
    {
        if(speed_of_updates>80)
        speed_of_updates--;
    }
    if(Keyboard::isKeyPressed(Keyboard::G))
    {

        speed_of_updates++;
    }
    if(can_change_dir)
    {
        if(Keyboard::isKeyPressed(Keyboard::D) && snake_dir!='L')
        {
            snake_dir='R';
            can_change_dir=0;
        }
        if(Keyboard::isKeyPressed(Keyboard::S) && snake_dir!='U')
        {
            snake_dir='D';
            can_change_dir=0;
        }
        if(Keyboard::isKeyPressed(Keyboard::W) && snake_dir!='D')
        {
            snake_dir='U';
            can_change_dir=0;
        }
        if(Keyboard::isKeyPressed(Keyboard::A) && snake_dir!='R')
        {
            snake_dir='L';
            can_change_dir=0;
        }
    }

}
int main()
{

    fruity.setFillColor(Color(0,255,0));
    init_snake();
    spawn_fruit();

    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    srand(clock()^time(0));
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }
        std::chrono::time_point<std::chrono::steady_clock> endd = std::chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endd - start);
        if(did_i_eat_myself())
        {
            cout<<"AHHH"<<endl;
            goto xx;
        }

        if(duration.count()>speed_of_updates)
        {
            //cout<<speed_of_updates<<endl;


            advance_snake();
            start=chrono::steady_clock::now();
            if(Keyboard::isKeyPressed(Keyboard::N))
            {
                grow_snake();
            }

        }
        snake_movement();
        //spawn_fruit();
        xx:;
        window.clear(sf::Color::Black);
        draw_snake();
        window.display();
    }

    return 0;
}
