#include "gameClient.h"
#include "gui/screen.h"
#include "gui/shapes/VehicleLogo.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

double xPosition = 0.2;
double yPosition = 0.2;
double width = 0.5;
double height = 0.6;
int size = 20;
Screen center;



int main() {
    Screen screen(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    sf::RenderWindow window(sf::VideoMode(screen.width * width, screen.height * height), "WoT_strategy_Pigs-on-the-moon");

    window.setPosition(sf::Vector2i(screen.width * xPosition, screen.height * yPosition));
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
    center = {window.getSize().x / 2, window.getSize().y / 2};

    sf::Music music;
    if (!music.openFromFile("resources/music/Intro.ogg"))
        std::cerr << "can't load Intro music" << '\n';
    music.play();

    GameClient gc;
    gc.InitGame("Den-Pig");
    gc.InitIds();

    sf::Texture texture;
    if (!texture.loadFromFile("resources/image/background.jpg")) {
        std::cerr << "can't load texture" << '\n';
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::CircleShape hex(size - 3, 6);
    hex.setOutlineThickness(1.f);
    hex.setFillColor(sf::Color::Transparent);
    hex.setOrigin(hex.getLocalBounds().width/2, hex.getLocalBounds().height/2);
    hex.setRotation(30.f);


    while (window.isOpen()) {
        window.draw(sprite);
        auto map = gc.GetGame()->GetMap();
        for (const auto point : map->GetGrid()) {
            hex.setOutlineColor(sf::Color::Green);
            if (map->GetType(*point.second) == ConstructionsTypes::BASE) hex.setOutlineColor(sf::Color::Blue);
            if (map->GetType(*point.second) == ConstructionsTypes::OBSTACLE) hex.setOutlineColor(sf::Color::Red);
            int x = size * 3. / 2 * point.first.x + center.width;
            int y = size * (sqrt(3) / 2 * point.first.x + std::sqrt(3) * point.first.y) + center.height;
            hex.setPosition(x, y);
            window.draw(hex);
        }

        auto vehiclesVectors = gc.GetGame()->GetVehicles();

        for (int i = 0; i < vehiclesVectors.size(); i++){
            VehicleLogo::GenerateLogos(size - 6, i);
            for (int j = 0; j < vehiclesVectors[i].size(); j++) {
                auto logo = VehicleLogo::GetLogoOfType(VehiclesTypes::Type(j));
                auto point = vehiclesVectors[i][j]->GetCurrentPosition();
                int x = size * 3. / 2 * point.x + center.width;
                int y = size * (sqrt(3) / 2 * point.x + std::sqrt(3) * point.y) + center.height;
                logo->setPosition(x, y);
                window.draw(*logo);
            }
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                VehicleLogo::DestructLogos();
                window.close();
            }
        }


        window.display();
        if(gc.GameIsFinished() == false) {
            gc.UpdateGameState();
            if (gc.IsPlayTime())// play only our turn
                gc.SendAction();
            std::this_thread::sleep_for(std::chrono::seconds(5));
            gc.SendTurn();
        }
    }

    return 0;
}