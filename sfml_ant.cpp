#pragma once
#include "sfml_ant.h"
#include <SFML-3.0.0\include\SFML\Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "ant.h"
#include "anthill.h"

sf::Font SFMLAnt::font;

SFMLAnt::SFMLAnt(Ant* ant, float x, float y) : ant(ant) {
    // Загрузка шрифта (если ещё не загружен)
    if (font.getInfo().family.empty()) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Ошибка загрузки шрифта!" << std::endl;
            // Можно создать базовый шрифт, если загрузка не удалась
            font.loadFromMemory(nullptr, 0);
        }
    }

    // Настройка графического представления муравья
    shape.setRadius(8.f);
    shape.setOrigin({8.f, 8.f});
    shape.setPosition({x, y});
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Black);

    // Настройка текста с ролью
    roleText.setFont(font);  // Устанавливаем шрифт
    roleText.setCharacterSize(12);
    roleText.setFillColor(sf::Color::Black);
    
    update(); // Инициализация цвета и текста
}

void SFMLAnt::update() {
    // Установка цвета в зависимости от роли
    const std::string role = ant->getRoleName();
    if (role == "Nanny") {
        shape.setFillColor(sf::Color::Green);
    } else if (role == "Soldier") {
        shape.setFillColor(sf::Color::Red);
    } else if (role == "Pastuh") {
        shape.setFillColor(sf::Color::Yellow);
    } else if (role == "Builder") {
        shape.setFillColor(sf::Color::Blue);
    } else if (role == "Cleaner") {
        shape.setFillColor(sf::Color::Magenta);
    } else {
        shape.setFillColor(sf::Color::White); // Norole
    }

    // Обновление текста
    roleText.setString(role);
    
    // Центрирование текста под муравьем
    const sf::FloatRect textBounds = roleText.getLocalBounds();
    roleText.setOrigin({textBounds.width / 2.f, 0.f});
    roleText.setPosition(shape.getPosition() + sf::Vector2f{0.f, 12.f});

    // Анимация движения
    if (ant->getRoleName() != "Norole") {
        const float angle = std::rand() % 360;
        const float distance = 0.5f;
        shape.move({distance * std::cos(angle * 3.14159f / 180.f), 
                   distance * std::sin(angle * 3.14159f / 180.f)});
    }
}

void SFMLAnt::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(roleText);
}

void SFMLAnt::setPosition(sf::Vector2f pos) {
    shape.setPosition(pos);
    roleText.setPosition(pos + sf::Vector2f{0.f, 12.f});
}

sf::Vector2f SFMLAnt::getPosition() const {
    return shape.getPosition();
}

SFMLAnthill::SFMLAnthill(Anthill* anthill, float x, float y) 
    : anthill(anthill), position{x, y} {
    
    // Настройка графического представления муравейника
    shape.setRadius(static_cast<float>(anthill->getSize()) * 5.f);
    shape.setOrigin({shape.getRadius(), shape.getRadius()});
    shape.setPosition(position);
    shape.setFillColor(sf::Color{139, 69, 19}); // Коричневый
    shape.setOutlineThickness(3.f);
    shape.setOutlineColor(sf::Color{101, 67, 33}); // Темно-коричневый

    // Создание графических представлений муравьев
    for (auto* ant : anthill->getAllAnts()) {
        addRandomAnt(ant);
    }
}

void SFMLAnthill::addRandomAnt(Ant* ant) {
    const float angle = static_cast<float>(std::rand() % 360);
    const float distance = 10.f + std::rand() % static_cast<int>(shape.getRadius());
    const float x = position.x + distance * std::cos(angle * 3.14159f / 180.f);
    const float y = position.y + distance * std::sin(angle * 3.14159f / 180.f);
    
    sfmlAnts.emplace_back(ant, x, y);
}

void SFMLAnthill::update() {
    // Обновление размера муравейника
    const float newRadius = static_cast<float>(anthill->getSize()) * 5.f;
    shape.setRadius(newRadius);
    shape.setOrigin({newRadius, newRadius});

    // Обновление муравьев
    for (auto& sfmlAnt : sfmlAnts) {
        sfmlAnt.update();
    }

    // Добавление новых муравьев при необходимости
    while (sfmlAnts.size() < anthill->getAllAnts().size()) {
        addRandomAnt(anthill->getAnt(sfmlAnts.size()));
    }

    // Удаление умерших муравьев
    if (sfmlAnts.size() > anthill->getAllAnts().size()) {
        sfmlAnts.resize(anthill->getAllAnts().size());
    }
}

void SFMLAnthill::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    for (const auto& sfmlAnt : sfmlAnts) {
        sfmlAnt.draw(window);
    }
}

void SFMLAnthill::addAnt(const SFMLAnt& ant) {
    sfmlAnts.push_back(ant);
}