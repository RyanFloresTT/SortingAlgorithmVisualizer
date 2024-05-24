#include "imgui.h"
#include "imgui-SFML.h"
#include "../Header Files/SortingAlgorithms.h"
#include "../Header Files/Globals.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <random>
#include <thread>
#include <functional>
#include <iostream>
#include <ostream>

const int DATA_BAR_AMOUNT = 256;

sf::RenderWindow window(sf::VideoMode(1280, 1280), "Algorithm Visualizer");
sf::RectangleShape dataBars[DATA_BAR_AMOUNT];
int data[DATA_BAR_AMOUNT];
float barColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};

void shuffleData() {
    std::shuffle(std::begin(data), std::end(data), std::mt19937(std::random_device()()));
}

void drawBars() {
    int screenHeight = window.getSize().y;
    float maxHeight = screenHeight * 0.5f;
    int numBars = window.getSize().x / 5;

    for (int i = 0; i < numBars; ++i) {
        auto height = static_cast<float>(data[i]) * (maxHeight / 100.0f);
        auto barWidth = 5.0f;
        auto xPos = static_cast<float>(barWidth * i);
        dataBars[i].setSize(sf::Vector2f(barWidth, height));
        dataBars[i].setFillColor(sf::Color(barColor[0] * 255, barColor[1] * 255, barColor[2] * 255, barColor[3] * 255)); // Use selected color
        dataBars[i].setPosition(xPos, screenHeight - height);
        window.draw(dataBars[i]);
    }
}

int main() {
    window.setFramerateLimit(60);
    bool success = ImGui::SFML::Init(window);
    if (!success) {
        std::cerr << "Window Initialization Failed!" << std::endl;
    }


    srand((unsigned) time(NULL));

    for (int & i : data){
        i = rand() % 101;
    }

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());


        ImGui::Begin("Sorting Menu");
        ImGui::ColorEdit4("Color", barColor);
        ImGui::Spacing();

        static const char* algorithms[] = { "Bubble Sort", "Selection Sort", "Insertion Sort" , "Merge Sort"};
        static int currentAlgorithm = 0;
        ImGui::Combo("Sorting Algorithm", &currentAlgorithm, algorithms, IM_ARRAYSIZE(algorithms));
        ImGui::Spacing();

        if (ImGui::Button("Sort Data", ImVec2(-1, 0))) {
            if (!sorting) {
                sorting = true;
                switch (currentAlgorithm) {
                    case 0: {
                        std::thread sortingThread(SortingAlgorithms::bubbleSort, data, DATA_BAR_AMOUNT);
                        sortingThread.detach();
                        break;
                    }
                    case 1: {
                        std::thread sortingThread(SortingAlgorithms::selectionSort, data, DATA_BAR_AMOUNT);
                        sortingThread.detach();
                        break;
                    }
                    case 2: {
                        std::thread sortingThread(SortingAlgorithms::insertionSort, data, DATA_BAR_AMOUNT);
                        sortingThread.detach();
                        break;
                    }
                    case 3: {
                        std::thread sortingThread(SortingAlgorithms::mergeSort, data, 0, DATA_BAR_AMOUNT - 1);
                        sortingThread.detach();
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        ImGui::Spacing();

        if (ImGui::Button("Shuffle Data", ImVec2(-1, 0))){
            shuffleData();
            drawBars();
        }
        ImGui::Spacing();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
        if (ImGui::Button("Stop", ImVec2(-1, 0))){
            sorting = false;
        }
        ImGui::PopStyleColor();
        ImGui::Spacing();
        ImGui::SliderInt("Delay (ms)", &delayMS, 5, 1000);
        ImGui::End();

        window.clear();
        drawBars();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}