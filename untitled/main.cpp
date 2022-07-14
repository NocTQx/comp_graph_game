#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "view.h"
#include <iomanip>
#include <sstream>
#include "map.h"

using namespace sf;

class Entity{
public:
    float x, y, h, w, dx, dy, speed, moveTimer;
    int health;
    bool life;
    Texture texture;
    Sprite sprite;
    String name;
    Text texts;
    Entity(Image &image, float X, float Y, int W, int H, String Name, Text text) {
        texts = text;
        x = X;
        y = Y;
        w = W;
        h = H;
        name = Name;
        speed = 0;
        dx = 0;
        dy = 0;
        health = 100;
        life = true;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(w / 2, h / 2);
        sprite.setPosition(x + w / 2, y + h / 2);
    }
    FloatRect getRect(){
        return FloatRect(x, y, w, h);
    }
    virtual void update(float time) = 0;
};
class Enemy : public Entity{
public:
    Enemy(Image &image, float X, float Y, float W, float H, String Name, Text text) :Entity(image, X, Y, W, H, Name, text) {

        if (name == "easygame1"){ sprite.setTextureRect(IntRect(186, 672, w, h)); dx = 0.1;}
        if (name == "easygame2"){ sprite.setTextureRect(IntRect(63, 704, w, h)); dx = 0.2;}
        if (name == "easygame3"){ sprite.setTextureRect(IntRect(127, 672, w, h)); dx = 0.3;}
    }
    void interactionWithMap() {
        for (int j = y / 32; j < (y + h) / 32; j++)
            for (int k = x / 32; k < (x + w) / 32; k++) {
                if ((TileMap[j][k] == '$') || (TileMap[j][k] == '#')) {
                    if (dy > 0) {
                        x = j * 32 - h;
                    }
                    if (dy < 0) {
                        x = j * 32 + 32;
                    }
                    if (dx > 0) {
                        x = k * 32 - w;
                    }
                    if (dx < 0) {
                        x = k * 32 + 32;
                    }
                }
            }
    }
    void update(float time) {
        moveTimer += time;
        if (name == "easygame1") {
            if (moveTimer > 3000) {
                dx *= -1;
                moveTimer = 0;
                sprite.scale(-1, 1);
            }
            interactionWithMap();
            x += dx * time;
            sprite.setPosition(x - w / 2, y - h / 2);
        }
        if (name == "easygame2") {
            if (moveTimer > 1500) {
                dx *= -1;
                moveTimer = 0;
                sprite.scale(-1, 1);
            }
            interactionWithMap();
            x += dx * time;
            sprite.setPosition(x - w / 2, y - h / 2);
        }
        if (name == "easygame3") {
            if (moveTimer > 1000) {
                dx *= -1;
                moveTimer = 0;
                sprite.scale(-1, 1);
            }
            interactionWithMap();
            x += dx * time;
            sprite.setPosition(x - w / 2, y - h / 2);
        }
    }
};
class Player :public Entity {
public:
    enum {
        left, right, up, down, stay
    } state;
    int Gold, key;

    Player(Image &image, float X, float Y, float W, float H, String Name, Text text) :Entity(image, X, Y, W, H, Name, text) {
        Gold = 0;
        key = 0;
        state = stay;
        if (name == "player1"){
        sprite.setTextureRect(IntRect(0, 0, w, h));
        }
    }
    void control() {
        if (life == true) {
            if (Keyboard::isKeyPressed) {
                if (Keyboard::isKeyPressed(Keyboard::W)) {
                    state = up;
                    speed = 0.1;
                }
                if (Keyboard::isKeyPressed(Keyboard::S)) {
                    state = down;
                    speed = 0.1;
                }
                if (Keyboard::isKeyPressed(Keyboard::D)) {
                    state = right;
                    speed = 0.1;
                }
                if (Keyboard::isKeyPressed(Keyboard::A)) {
                    state = left;
                    speed = 0.1;
                }
            }
        }
    }
        void interactionWithMap() {
            for (int j = y / 32; j < (y + h) / 32; j++)
                for (int k = x / 32; k < (x + w) / 32; k++) {
                    if ((TileMap[j][k] == '#') || (TileMap[j][k] == '$')) {
                        if (dy > 0) {
                            y = j * 32 - h;
                        }
                        if (dy < 0) {
                            y = j * 32 + 32;
                        }
                        if (dx > 0) {
                            x = k * 32 - w;
                        }
                        if (dx < 0) {
                            x = k * 32 + 32;
                        }
                    }
                    if (((j == 8) && (k == 18)) || ((j == 28) && (k == 53)) || ((j == 28) && (k == 73)) ||
                            ((j == 28) && (k == 35)) || (j == 8) && (k == 37)){
                        TileMap[j][k+1] = '.';
                        TileMap[j-1][k+1] = '.';
                        TileMap[j-2][k+1] = '.';
                    }
                    if (((j == 31) && (k == 10)) || ((j == 46) && (k == 10)) || ((j == 39) && (k == 25)) ||
                       ((j == 36) && (k == 65)) || ((j == 48) && (k == 66)) || ((j == 61) && (k == 70)) ||
                       ((j == 38) && (k == 100)) || ((j == 36) && (k == 122)) ){
                        TileMap[j+1][k] = '.';
                        TileMap[j+1][k-1] = '.';
                        TileMap[j+1][k-2] = '.';
                    }
                    if ((((j == 29) && (k == 16)) || ((j == 28) && (k == 92)) || ((j == 28) && (k == 110))) && (key == 1)) {
                       TileMap[j][k+1] = '.';
                       TileMap[j-1][k+1] = '.';
                        TileMap[j-2][k+1] = '.';
                       key--;
                    }
                    if (((j == 19) && (k == 8)) && (key == 1)) {
                        TileMap[j+1][k] = '.';
                        TileMap[j+1][k-1] = '.';
                        TileMap[j+1][k-2] = '.';
                        key--;
                    }
                    if (TileMap[j][k] == 'T'){
                        health -= 10;
                        TileMap[j][k] = '.';
                    }
                    if (TileMap[j][k] == 'H'){
                        if (health <= 70){
                            health += 30;
                            TileMap[j][k] = '.';
                        }
                        else if ((health > 70) && (health < 100)){
                            health = 100;
                            TileMap[j][k] = '.';
                        }
                    }
                    if (TileMap[j][k] == 'K'){
                        texts.setString("Press E");
                        texts.setPosition(x - (w /2), y - 2*h);
                        if (Keyboard::isKeyPressed(Keyboard::E)) {
                            key++;
                            TileMap[j][k] = '.';
                            texts.setString("");
                        }
                    }
                    if (TileMap[j][k] == 'S') {
                        Gold++;
                        TileMap[j][k] = '.';
                    }
                    if (TileMap[j][k] == 'Q') {
                        texts.setCharacterSize(104);
                        texts.setString("You win!!!");
                        texts.setPosition(view.getCenter().x-250, view.getCenter().y-100);
                        dx = 0; dy = 0;
                    }
                }
        }
        void update(float time) {
        if (life) {
                control();
                switch (state) {
                    case right :
                        dx = speed;
                        dy = 0;
                        break;
                    case left :
                        dx = -speed;
                        dy = 0;
                        break;
                    case down :
                        dx = 0;
                        dy = speed;
                        break;
                    case up :
                        dx = 0;
                        dy = -speed;
                        break;
                }
                x += dx * time;
                y += dy * time;
                interactionWithMap();
                speed = 0;
                sprite.setPosition(x - w/2, y - h/2);
                if (sprite.getPosition().x > 300) view.setCenter(sprite.getPosition().x, sprite.getPosition().y);
                    else view.setCenter(300, sprite.getPosition().y);
                if (health <= 0) {
                    life = false;
                    texts.setCharacterSize(104);
                    texts.setString("Game over");
                    dx = 0; dy = 0;
                    texts.setPosition(view.getCenter().x-250, view.getCenter().y-100);
                }
            }
        }
    void death(Enemy e, float time) {
            if (e.getRect().intersects(getRect())) {
                    health -= static_cast<int>(time) * 5 * 0.0001;
            }
    }
};

int start()
{
    float CurrentFrame  = 0;
    map_load();
    RandomGold();

    Font font;
    font.loadFromFile(file + "font.ttf");
    Text text1("",font,20);
    text1.setColor(Color::Red);
    text1.setStyle(sf::Text::Bold);
    Text text2("",font,20);
    text2.setColor(Color::Red);
    text2.setStyle(sf::Text::Bold);
    Text text3("",font,20);
    text3.setColor(Color::Red);
    text3.setStyle(sf::Text::Bold);
    Text text_key("",font,20);
    text_key.setColor(Color::Red);
    text_key.setStyle(sf::Text::Bold);

    RenderWindow window(VideoMode(550, 700), "Dungeon");

   // view.setViewport(sf::FloatRect(0.0029f, 0.015f, 0.94f, 0.89f));
    view.reset(FloatRect(0,0,980,720));

    Image map_t;
    map_t.loadFromFile(file +"/images/tiles.png");
    Texture map_text;
    map_text.loadFromImage(map_t);
    Sprite map_spr;
    map_spr.setTexture(map_text);

    Image hero_img;
    hero_img.loadFromFile(file + "/images/hero_run.png");

    Image enemy_img;
    enemy_img.loadFromFile(file + "/images/tiles.png");

    Enemy enemy1(enemy_img, 658, 1424, 32, 32, "easygame1", text_key);
    Enemy enemy2(enemy_img, 638, 1560, 32, 32, "easygame2", text_key);
    Enemy enemy3(enemy_img, 1910, 880, 32, 32, "easygame3", text_key);
    Enemy enemy4(enemy_img, 150, 1660, 32, 32, "easygame2", text_key);
    Enemy enemy5(enemy_img, 1300, 300, 32, 32, "easygame2", text_key);
    Enemy enemy6(enemy_img, 3700, 900, 32, 32, "easygame3", text_key);

    Player p(hero_img, 300, 500, 32, 32, "player1", text_key);
    Clock clock;

    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color::Yellow);

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        p.update(time);

        CurrentFrame += 0.005*time;
        if (CurrentFrame > 6) CurrentFrame -= 6;
        if ((p.dx == 0) && (p.dy == 0)) p.sprite.setTextureRect(IntRect(0, 0, 34, 32));
        else if ((p.dx > 0) || (p.dx == 0) && (p.dy !=0)) p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 34, 32));
        else if (p.dx < 0) p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame)+32, 0, -34, 32));

        p.death(enemy1, time);
        p.death(enemy2, time);
        p.death(enemy3, time);
        p.death(enemy4, time);
        p.death(enemy5, time);
        p.death(enemy6, time);

        if (enemy1.life == true) enemy1.update(time);
        if (enemy2.life == true) enemy2.update(time);
        if (enemy3.life == true) enemy3.update(time);
        if (enemy4.life == true) enemy4.update(time);
        if (enemy5.life == true) enemy5.update(time);
        if (enemy6.life == true) enemy6.update(time);

        for (int i=0; i < DIM1; i++)
            for (int j = 0; j < DIM2; j++){
                    if (TileMap[i][j] == '#') map_spr.setTextureRect(IntRect(63, 64, 32, 32));
                    if (TileMap[i][j] == '$') map_spr.setTextureRect(IntRect(93, 63, 32, 32));
                    if (TileMap[i][j] == '.') map_spr.setTextureRect(IntRect(127, 95, 32, 32));
                    if (TileMap[i][j] == ' ') map_spr.setTextureRect(IntRect(272, 113, 32, 32));
                    if (TileMap[i][j] == 'D') map_spr.setTextureRect(IntRect(224, 64, 32, 32));
                    if (TileMap[i][j] == 'X') map_spr.setTextureRect(IntRect(223, 95, 32, 32));
                    if (TileMap[i][j] == 'K') map_spr.setTextureRect(IntRect(96, 128, 32, 32));
                    if (TileMap[i][j] == 'S') map_spr.setTextureRect(IntRect(32, 480, 32, 32));
                    if (TileMap[i][j] == 'T') map_spr.setTextureRect(IntRect(94, 95, 32, 32));
                    if (TileMap[i][j] == 'H') map_spr.setTextureRect(IntRect(101, 159, 32, 32));
                    map_spr.setPosition(j * 32 - 32, i * 32 - 32);
                    window.draw(map_spr);
                }
        if ((p.life == false) && (Keyboard::isKeyPressed(Keyboard::E))) return -1;
        std::ostringstream phealth, pkeys, pgold;
        phealth << p.health;
        pkeys << p.key;
        pgold << p.Gold;
        text1.setString("XP  " + phealth.str());
        text1.setPosition(view.getCenter().x - 250, view.getCenter().y + 200);
        text2.setString("Keys  " + pkeys.str());
        text2.setPosition(view.getCenter().x + 220, view.getCenter().y - 230);
        text3.setString("Gold  " + pgold.str());
        text3.setPosition(view.getCenter().x + 220, view.getCenter().y - 210);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(p.texts);
        window.setView(view);
        window.draw(enemy1.sprite);
        window.draw(enemy2.sprite);
        window.draw(enemy3.sprite);
        window.draw(enemy4.sprite);
        window.draw(enemy5.sprite);
        window.draw(enemy6.sprite);
        window.draw(p.sprite);
        window.display();
    }
    return 0;
}
int main() {
    while(start() == 1) start();
    return 0;
}