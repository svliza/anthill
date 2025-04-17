#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ant.h"
#include "anthill.h"
#include "enemy.h"
#include "sfml_ant.h"

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    // Создаем SFML окно
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ant Colony Simulation");
    window.setFramerateLimit(60);

    // Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load font!" << endl;
        return 1;
    }

    // Создаем муравейник
    Anthill hill(10, 10, 200);
    SFMLAnthill sfmlHill(&hill, 400.f, 300.f);  // Центр окна

    cout << "Муравейник создан: 10 муравьёв, запас еды — 200.\n" << endl;

    // Текст для отображения дня
    sf::Text dayText;
    dayText.setFont(font);
    dayText.setCharacterSize(20);
    dayText.setFillColor(sf::Color::Black);
    dayText.setPosition(10.f, 10.f);

    // Основной игровой цикл
    for (int day = 1; day <= 30; ++day) {
        cout << "=== День " << day << " ===" << endl;
        dayText.setString("Day: " + to_string(day));

        // Обработка событий SFML
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Логика симуляции
        for (size_t i = 0; i < hill.getAllAnts().size(); ++i) {
            Ant* ant = hill.getAnt(static_cast<int>(i));
            ant->change_age();
            ant->work();
        }

        if (day % 3 == 0) {
            int food = rand() % 50 + 20;
            int branches = rand() % 30 + 10;
            hill.newFood(food);
            hill.newBranches(branches);
            cout << "Муравьи принесли еду: " << food << ", веток: " << branches << endl;
        }

        if (day % 5 == 0) {
            int born = rand() % 5 + 1;
            hill.newAnts(born);
            cout << "В муравейнике родилось " << born << " новых муравьёв." << endl;
        }

        if (day % 7 == 0) {
            Enemy enemy(rand() % 100 + 30);
            enemy.attack(hill);
        }

        if (day % 4 == 0) {
            cout << "Еды не хватило — здоровье муравьёв снижается!" << endl;
            hill.emptyfood();
        }

        if (day % 10 == 0) {
            cout << "Муравейник осыпается — уменьшаются размер и вместимость." << endl;
            hill.lowbranch();
        }

        // Обновляем SFML представление
        sfmlHill.update();

        // Отрисовка
        window.clear(sf::Color::White);
        sfmlHill.draw(window);
        window.draw(dayText);
        window.display();

        cout << endl;
        sf::sleep(sf::milliseconds(500));  // Задержка между днями
    }

    cout << "Итоговое состояние муравейника: " << endl;
    hill.showAllAnts();

    // Ожидаем закрытия окна
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color::White);
        sfmlHill.draw(window);
        window.draw(dayText);
        window.display();
    }

    return 0;
}