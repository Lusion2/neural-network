#version 330 core
layout (location = 0) in vec2 position;
out vec4 vertexColor; // Added output variable for color

void main() {
    gl_Position = vec4(position, 0.0, 1.0);
    
    // Calculate color based on y-coordinate
    float colorValue = position.y * 0.5 + 0.5; // Adjust this formula based on your function
    vertexColor = vec4(1.0, colorValue, 0.0, 1.0); // Color based on y-coordinate
}