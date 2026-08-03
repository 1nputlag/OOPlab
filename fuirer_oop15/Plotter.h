#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Interfaces.h"
#include "Fourier.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <optional>

class Plotter {
private:
    sf::RenderWindow window;
    sf::Font font;
    
    int harmonics = 18;       
    int integrationSteps = 1300; 
    int currentFuncIdx = 0;
    int currentIntIdx = 0;
    bool showHistogram = false; 

public:
    Plotter() : window(sf::VideoMode({1000, 800}), "Fourier Math Visualizer") {
        if (!font.openFromFile("arial.ttf")) {
            std::cerr << "Error: Font arial.ttf not found!\n";
        }
    }

    void runInteractive(std::vector<IFunction*>& functions, std::vector<IIntegrator*>& integrators) {
        FourierSeries fourier;
        fourier.calculate(*functions[currentFuncIdx], *integrators[currentIntIdx], harmonics, integrationSteps);

        while (window.isOpen()) {
            bool needsRecalculation = false;
            while (const std::optional<sf::Event> event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) window.close();
                if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouseEvent->button == sf::Mouse::Button::Left) {
                        int mx = mouseEvent->position.x;
                        int my = mouseEvent->position.y;
                        
                        // Кнопки Ne
                        if (mx >= 30 && mx <= 70 && my >= 630 && my <= 670 && integrationSteps > 100) { integrationSteps -= 100; needsRecalculation = true; }
                        if (mx >= 210 && mx <= 250 && my >= 630 && my <= 670) { integrationSteps += 100; needsRecalculation = true; }
                        
                        // Кнопки Ng
                        if (mx >= 30 && mx <= 70 && my >= 700 && my <= 740 && harmonics > 1) { harmonics--; needsRecalculation = true; }
                        if (mx >= 210 && mx <= 250 && my >= 700 && my <= 740) { harmonics++; needsRecalculation = true; }
                        
                        // Вибір
                        if (mx >= 300 && mx <= 550 && my >= 630 && my <= 670) { currentFuncIdx = (currentFuncIdx + 1) % functions.size(); needsRecalculation = true; }
                        if (mx >= 300 && mx <= 550 && my >= 700 && my <= 740) { currentIntIdx = (currentIntIdx + 1) % integrators.size(); needsRecalculation = true; }
                        
                        // Режим
                        if (mx >= 600 && mx <= 950 && my >= 630 && my <= 740) { showHistogram = !showHistogram; }
                    }
                }
            }
            if (needsRecalculation) fourier.calculate(*functions[currentFuncIdx], *integrators[currentIntIdx], harmonics, integrationSteps);
            render(functions[currentFuncIdx], integrators[currentIntIdx], fourier);
        }
    }

private:
    void render(IFunction* func, IIntegrator* integrator, const FourierSeries& fourier) {
        window.clear(sf::Color::White); // Чисто білий фон для математики
        if (!showHistogram) drawGraphs(func, fourier);
        else drawHistogram(fourier);
        drawUI(func, integrator);
        window.display();
    }

    void drawGridAndAxes(float centerX, float centerY) {
        // Сітка (Grid)
        sf::VertexArray grid(sf::PrimitiveType::Lines);
        for (float i = 0; i <= 1000; i += 50) {
            grid.append(sf::Vertex{ {i, 0.f}, sf::Color(240, 240, 240) });
            grid.append(sf::Vertex{ {i, 600.f}, sf::Color(240, 240, 240) });
        }
        for (float i = 0; i <= 600; i += 50) {
            grid.append(sf::Vertex{ {0.f, i}, sf::Color(240, 240, 240) });
            grid.append(sf::Vertex{ {1000.f, i}, sf::Color(240, 240, 240) });
        }
        window.draw(grid);

        // Вісь X
        sf::VertexArray axisX(sf::PrimitiveType::Lines, 2);
        axisX[0] = sf::Vertex{ {0.f, centerY}, sf::Color::Black };
        axisX[1] = sf::Vertex{ {1000.f, centerY}, sf::Color::Black };
        window.draw(axisX);

        // Стрілка X
        sf::ConvexShape arrowX(3);
        arrowX.setPoint(0, {1000.f, centerY});
        arrowX.setPoint(1, {990.f, centerY - 5.f});
        arrowX.setPoint(2, {990.f, centerY + 5.f});
        arrowX.setFillColor(sf::Color::Black);
        window.draw(arrowX);
        
        sf::Text textX(font, L"X", 16);
        textX.setFillColor(sf::Color::Black);
        textX.setPosition({975.f, centerY + 10.f});
        window.draw(textX);

        // Вісь Y
        sf::VertexArray axisY(sf::PrimitiveType::Lines, 2);
        axisY[0] = sf::Vertex{ {centerX, 600.f}, sf::Color::Black };
        axisY[1] = sf::Vertex{ {centerX, 0.f}, sf::Color::Black };
        window.draw(axisY);

        // Стрілка Y
        sf::ConvexShape arrowY(3);
        arrowY.setPoint(0, {centerX, 0.f});
        arrowY.setPoint(1, {centerX - 5.f, 10.f});
        arrowY.setPoint(2, {centerX + 5.f, 10.f});
        arrowY.setFillColor(sf::Color::Black);
        window.draw(arrowY);

        sf::Text textY(font, L"Y", 16);
        textY.setFillColor(sf::Color::Black);
        textY.setPosition({centerX + 15.f, 5.f});
        window.draw(textY);

        // Відлік на осі X (-10 до 10)
        for (int i = -10; i <= 10; ++i) {
            if (i == 0) continue;
            float xPos = centerX + i * 50.0f; // 50 пікселів = 1 одиниця X
            sf::VertexArray tick(sf::PrimitiveType::Lines, 2);
            tick[0] = sf::Vertex{ {xPos, centerY - 4.f}, sf::Color::Black };
            tick[1] = sf::Vertex{ {xPos, centerY + 4.f}, sf::Color::Black };
            window.draw(tick);

            sf::Text num(font, std::to_wstring(i), 12);
            num.setFillColor(sf::Color::Black);
            sf::FloatRect bounds = num.getLocalBounds();
            num.setPosition({xPos - bounds.size.x / 2.0f, centerY + 8.f});
            window.draw(num);
        }

        // Відлік на осі Y (-3 до 3)
        for (int i = -3; i <= 3; ++i) {
            if (i == 0) continue;
            float yPos = centerY - i * 100.0f; // 100 пікселів = 1 одиниця Y
            sf::VertexArray tick(sf::PrimitiveType::Lines, 2);
            tick[0] = sf::Vertex{ {centerX - 4.f, yPos}, sf::Color::Black };
            tick[1] = sf::Vertex{ {centerX + 4.f, yPos}, sf::Color::Black };
            window.draw(tick);

            sf::Text num(font, std::to_wstring(i), 12);
            num.setFillColor(sf::Color::Black);
            sf::FloatRect bounds = num.getLocalBounds();
            num.setPosition({centerX - bounds.size.x - 8.f, yPos - bounds.size.y / 2.0f - 4.f});
            window.draw(num);
        }
    }

    void drawGraphs(IFunction* func, const FourierSeries& fourier) {
        drawGridAndAxes(500.f, 300.f);
        
        sf::VertexArray origLine(sf::PrimitiveType::LineStrip);
        sf::VertexArray fourierLine(sf::PrimitiveType::LineStrip);

        for (float x = -10.f; x <= 10.f; x += 0.02f) {
            float sx = 500.0f + x * 50.0f;
            // Зелений колір (як на фото) для оригіналу
            origLine.append(sf::Vertex{ {sx, 300.0f - (float)func->evaluate(x) * 100.0f}, sf::Color(34, 139, 34) }); 
            // Малиново-рожевий колір для Фур'є
            fourierLine.append(sf::Vertex{ {sx, 300.0f - (float)fourier.evaluateApproximation(x) * 100.0f}, sf::Color(255, 20, 147) }); 
        }
        window.draw(origLine);
        window.draw(fourierLine);
    }

    void drawHistogram(const FourierSeries& fourier) {
        drawGridAndAxes(500.f, 550.f); // Осі для гістограми зміщені вниз
        
        float startX = 60.0f; float baseY = 550.0f;
        float barWidth = 880.0f / (harmonics + 1);
        float maxA = 0.001f;
        for (int i = 0; i <= harmonics; ++i) if (fourier.getAmplitude(i) > maxA) maxA = fourier.getAmplitude(i);

        for (int i = 0; i <= harmonics; ++i) {
            float h = (fourier.getAmplitude(i) / maxA) * 400.0f;
            sf::RectangleShape bar({barWidth * 0.7f, h});
            bar.setPosition({startX + i * barWidth, baseY - h});
            bar.setFillColor(sf::Color(0, 191, 255)); // Блакитні стовпці
            bar.setOutlineThickness(1.f);
            bar.setOutlineColor(sf::Color(0, 100, 150));
            window.draw(bar);
        }
    }

    void drawUI(IFunction* func, IIntegrator* integrator) {
        // Світло-сіра панель (Apple-style)
        sf::RectangleShape panel({1000.f, 200.f});
        panel.setPosition({0.f, 600.f});
        panel.setFillColor(sf::Color(245, 245, 247)); 
        window.draw(panel);

        sf::VertexArray topBorder(sf::PrimitiveType::Lines, 2);
        topBorder[0] = sf::Vertex{ {0.f, 600.f}, sf::Color(200, 200, 200) };
        topBorder[1] = sf::Vertex{ {1000.f, 600.f}, sf::Color(200, 200, 200) };
        window.draw(topBorder);

        auto drawBtn = [&](float x, float y, float w, float h, sf::Color c, std::wstring t, sf::Color tc = sf::Color::White) {
            sf::RectangleShape r({w, h});
            r.setPosition({x, y});
            r.setFillColor(c);
            r.setOutlineThickness(1.f);
            r.setOutlineColor(sf::Color(0, 0, 0, 40)); // Легка тінь
            window.draw(r);

            sf::Text txt(font, t, 15);
            txt.setFillColor(tc);
            sf::FloatRect bounds = txt.getLocalBounds();
            txt.setPosition({x + (w - bounds.size.x) / 2.0f, y + (h - bounds.size.y) / 2.0f - 3.f}); // Центрування тексту
            window.draw(txt);
        };

        // Синій колір (як у macOS/сучасних інтерфейсах)
        sf::Color btnBlue(0, 122, 255);
        sf::Color btnLight(255, 255, 255);

        // Кнопки Ne
        drawBtn(30, 630, 40, 40, btnBlue, L"-");
        drawBtn(80, 630, 120, 40, btnLight, L"Ne = " + std::to_wstring(integrationSteps), sf::Color::Black);
        drawBtn(210, 630, 40, 40, btnBlue, L"+");
        
        // Кнопки Ng
        drawBtn(30, 700, 40, 40, btnBlue, L"-");
        drawBtn(80, 700, 120, 40, btnLight, L"Ng = " + std::to_wstring(harmonics), sf::Color::Black);
        drawBtn(210, 700, 40, 40, btnBlue, L"+");
        
        // Вибір
        drawBtn(300, 630, 250, 40, btnLight, func->getName() + L" ▼", sf::Color::Black);
        drawBtn(300, 700, 250, 40, btnLight, integrator->getName() + L" ▼", sf::Color::Black);
        
        // Великий перемикач
        drawBtn(600, 630, 350, 110, btnBlue, showHistogram ? L"Режим: Гістограма" : L"Режим: Математичний Графік");
    }
};