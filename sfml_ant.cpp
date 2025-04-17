#include "sfml_ant.h"
#include <SFML-3.0.0\include\SFML\Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

// Инициализация статического шрифта
sf::Font SFMLAnt::font = [](){
    sf::Font f;
    if (!f.loadFromFile("arial.ttf")) {
        std::cerr << "Ошибка загрузки шрифта!" << std::endl;
    }
    return f;
}();

// Конструктор SFMLAnt
SFMLAnt::SFMLAnt(Ant* ant, float x, float y) : ant(ant) {
    // Настройка графического представления муравья
    shape.setRadius(8.f);
    shape.setOrigin({8.f, 8.f});
    shape.setPosition({x, y});
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Black);

    // Настройка текста с ролью
    roleText.setFont(font);
    roleText.setCharacterSize(12);
    roleText.setFillColor(sf::Color::Black);
    
    update(); // Инициализация цвета и текста
}

// Обновление состояния муравья
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

    // Анимация движения (пример)
    if (ant->getRoleName() != "Norole") {
        const float angle = std::rand() % 360;
        const float distance = 0.5f;
        shape.move({distance * std::cos(angle * 3.14159f / 180.f), 
                   distance * std::sin(angle * 3.14159f / 180.f)});
    }
}

// Отрисовка муравья
void SFMLAnt::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(roleText);
}

// Установка позиции
void SFMLAnt::setPosition(sf::Vector2f pos) {
    shape.setPosition(pos);
    // Обновляем позицию текста при изменении позиции муравья
    const sf::FloatRect textBounds = roleText.getLocalBounds();
    roleText.setPosition(pos + sf::Vector2f{0.f, 12.f});
}

// Получение позиции
sf::Vector2f SFMLAnt::getPosition() const {
    return shape.getPosition();
}

// Конструктор SFMLAnthill
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

// Добавление муравья в случайной позиции вокруг муравейника
void SFMLAnthill::addRandomAnt(Ant* ant) {
    const float angle = static_cast<float>(std::rand() % 360);
    const float distance = 10.f + std::rand() % static_cast<int>(shape.getRadius());
    const float x = position.x + distance * std::cos(angle * 3.14159f / 180.f);
    const float y = position.y + distance * std::sin(angle * 3.14159f / 180.f);
    
    sfmlAnts.emplace_back(ant, x, y);
}

// Обновление муравейника
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

    // Удаление умерших муравьев (если размер вектора уменьшился)
    if (sfmlAnts.size() > anthill->getAllAnts().size()) {
        sfmlAnts.resize(anthill->getAllAnts().size());
    }
}

// Отрисовка муравейника
void SFMLAnthill::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    for (const auto& sfmlAnt : sfmlAnts) {
        sfmlAnt.draw(window);
    }
}

// Добавление муравья
void SFMLAnthill::addAnt(const SFMLAnt& ant) {
    sfmlAnts.push_back(ant);
}