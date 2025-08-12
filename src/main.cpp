#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource =
    "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

const char *firstFragmentShaderSource =
    "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

const char *secondFragmentShaderSource =
    "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.5f, 1.0f, 0.2f, 1.0f);\n"
    "}\n";

int main()
{
    //GLFW initialize
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //GLFWwindow initialize
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //GLAD initialize
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    GLfloat firstVertex[] = {
        -0.2f, 0.1f, 0.0f,
        0.5f, 0.1f, 0.0f,
        0.7f, 0.2f, 0.0f
    };
    GLfloat secondVertex[] = {
        -0.6f, 0.3f, 0.0f,
        0.9f, 0.4f, 0.0f,
        0.1f, 0.3f, 0.0f
    };
    
    
    
    
    //first shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint first_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint second_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint first_shader_program = glCreateProgram();
    GLuint second_shader_program = glCreateProgram();

    glShaderSource(vertex_shader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertex_shader);
    glShaderSource(first_fragment_shader, 1, &firstFragmentShaderSource, NULL);
    glCompileShader(first_fragment_shader);
    glShaderSource(second_fragment_shader, 1, &secondFragmentShaderSource, NULL);
    glCompileShader(second_fragment_shader);

    glAttachShader(first_shader_program, vertex_shader);
    glAttachShader(first_shader_program, first_fragment_shader);
    glLinkProgram(first_shader_program);

    glAttachShader(second_shader_program, vertex_shader);
    glAttachShader(second_shader_program, second_fragment_shader);
    glLinkProgram(second_shader_program);
    
    //first triangle
    
    GLuint VBOs[2], VAOs[2];

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstVertex), firstVertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    //Second triangle

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondVertex), secondVertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);


    //Render loop
    while (!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);

        //Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //Rendering square
        glUseProgram(first_shader_program);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(second_shader_program);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(first_shader_program);
    glDeleteProgram(second_shader_program);

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    //Callback for glfwSetFramebufferSizeCallback to resize screen
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    //Input for escape to terminate
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}