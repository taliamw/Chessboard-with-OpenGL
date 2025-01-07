#include <stdio.h>
#include <iostream>
#include <cmath>

#include <glew.h>
#include <glfw3.h>

using namespace std;

const GLint WIDTH = 800, HEIGHT = 600;

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int BOARD_SIZE = 8; // 8x8 chessboard

// Function to draw a square given the lower left corner coordinates and size
void drawSquare(float x, float y, float size, bool isWhite) {
    if (isWhite) {
        glColor3f(1.0f, 1.0f, 1.0f); // White color
    }
    else {
        glColor3f(0.0f, 0.0f, 0.0f); // Black color
    }

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
    glEnd();
}

// Function to draw the chessboard
void drawChessboard() {
    float squareSize = 2.0f / BOARD_SIZE; // Each square's size in normalized device coordinates

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            // Alternate colors
            bool isWhite = (row + col) % 2 == 0;

            // Calculate the lower left corner of each square
            float x = -1.0f + col * squareSize;
            float y = -1.0f + row * squareSize;

            // Draw the square
            drawSquare(x, y, squareSize, isWhite);
        }
    }
}

// Initialize OpenGL settings
void initOpenGL() {
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f); // Set the background color to gray
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f); // Orthographic projection
}

// Main display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawChessboard();
    glFlush();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Chessboard", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Initialize OpenGL settings
    initOpenGL();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}