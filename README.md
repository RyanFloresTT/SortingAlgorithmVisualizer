I’ve been very interested in Game Development for a long time and though I mainly use Unity and C#, I realize that a lot of positions require some sort of C++ knowledge. I am familiar with the language and have written some C++ code, but this was my first project I tackled.

I had been planning on learning some C++ for a while now and I’ve known of 2 libraries that people use for creating 2D games, SDL2 and SFML. I decided to use SFML purely because it’s the option that came up on my heads or tails flip. 

The idea for this project came from me watching these sorts of visualizers on YouTube and seeing someone on a forum saying that they learned the basics of SFML and C++ by creating a visualizer, I thought it’d be a fun project, and it turned out I was right!

![https://res.cloudinary.com/djdtmbpce/image/upload/v1715541319/AlgorithmVisualizer2024-05-1212-12-11-ezgif.com-video-to-gif-converter_ana1ux.gif](https://res.cloudinary.com/djdtmbpce/image/upload/v1715541319/AlgorithmVisualizer2024-05-1212-12-11-ezgif.com-video-to-gif-converter_ana1ux.gif)

### You can’t learn without a little failure

I know my code is probably all sorts of wrong, but for this being my first C++ project, I think I can let it slide. I’ve learned from this project and I’ll continue to do so in future projects.

I created 2 header files `Globals.h` and `SortingAlgorithms.h`, where they do what it seems they do. I feel like having some `Global` variables is bad practice because it can get messy in there quickly. As it stands I only have 2 fields in there though, `bool sorting = false;` and `int delayMS= 50;`. These are global so that my sorting algorithms can say when they are done, and delayMS is defined here so that the sliders from my main.cpp can affect it and my algorithms can wait on that delay.

My `SortingAlgorithms.h` looks like this:

```cpp
//
// Created by rcflo on 5/11/2024.
//

#ifndef TESTPROGRAM_SORTINGALGORITHMS_H
#define TESTPROGRAM_SORTINGALGORITHMS_H

#include <SFML/Graphics.hpp>
#include <thread>

class SortingAlgorithms {
public:
    static void bubbleSort(int arr[], int n);
    static void selectionSort(int arr[], int n);
    static void insertionSort(int arr[], int n);
    static void mergeSort(int arr[], int l, int r);
private:
    static void merge(int arr[], int l, int m, int r);
};

#endif //TESTPROGRAM_SORTINGALGORITHMS_H
```

### Dear ImGui… You’re really cool!

This is also my first time using and hearing about ImGui (Dear ImGui). Reading through it’s github repo makes me want to create an entire game engine from scratch and they make it look so easy! The demo they show makes it quite apparent that it’s super easy to do what you want when it comes to creating UI.

I created a DropDown menu within the application that allows users to change the color of the bars, shuffle the data, pick a sorting algorithm to sort by, and start / stop the sorting process.

For now I’m using a switch case statement because it was the easiest thing to do, but I know it can be improved by wrapping it in some sort of Strategy Pattern.

```cpp
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
```

### Threading the threads

I’m also *very* new to asynchronous programming and I had to use it in this project because of problem I was having without it. This project helped me in realizing that it’s not magic, and that it’s just a way to tell the program to come back to this thread to see if it still needs to finish it’s job, but continue with your normal work.

Before creating a thread for the sorting algorithms, I saw that when I ran the sort, it would freeze for a bit and then snap all the data bars into their correct places. It was because the window was rendering the data bars after the sort happened, and because there was no asynchronous code happening, the thread was waiting for the sort to happen, then draw all the data bars.

Introducing the thread for each of the sort, and detaching it allows for it to run independently of the main program. Which means it can finish and continuously run the window rendering loop at the same time the sorting is happening.

Here is a quick view of what it does so far. For the fun of it, I added a slider to change the delay between each sort step, and a color option to change the color of the bars.

![https://res.cloudinary.com/djdtmbpce/image/upload/v1715543029/AlgorithmVisualizer2024-05-1212-41-51-ezgif.com-video-to-gif-converter_qvzr58.gif](https://res.cloudinary.com/djdtmbpce/image/upload/v1715543029/AlgorithmVisualizer2024-05-1212-41-51-ezgif.com-video-to-gif-converter_qvzr58.gif)
