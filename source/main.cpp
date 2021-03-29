#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <camera.h>

#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
int input();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 translate = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);

int main()
{
    int shape_id = input();
    string file;

    // cout << "Shape ID selected is: " << shape_id << endl;

    if (shape_id == 1)
    {
        file = "../source/shapes/decagonal_prism.txt";
    }

    else if (shape_id == 2)
    {
        file = "../source/shapes/hexagonal_dipyramid.txt";
    }

    else if (shape_id == 3)
    {
        file = "../source/shapes/undecagonal_pyramid.txt";
    }

    else
    {
        assert(false);
    }

    std::fstream in;
    in.open(file);

    int N_VERTICES;
    in >> N_VERTICES;

    float vertices[N_VERTICES * 6];

    for (int i = 0; i < N_VERTICES * 6; i++)
    {
        in >> vertices[i];
    }

    in.close();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Assignment 0", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("./../source/shaders/shader.vert", "./../source/shaders/shader.frag");

    // float vertices[] = {
    //     0.0f, 0.4f, 0.0f, 0.4137623926f, 0.7677182949f, 0.0026915627f,
    //     -0.3f, 0.0f, -0.3f, 0.4137623926f, 0.7677182949f, 0.0026915627f,
    //     0.1098076211f, 0.0f, -0.4098076211f, 0.4137623926f, 0.7677182949f, 0.0026915627f,
    //     0.0f, 0.4f, 0.0f, 0.4896200473f, 0.1676612736f, 0.4429672735f,
    //     0.1098076211f, 0.0f, -0.4098076211f, 0.4896200473f, 0.1676612736f, 0.4429672735f,
    //     0.4098076211f, 0.0f, -0.1098076211f, 0.4896200473f, 0.1676612736f, 0.4429672735f,
    //     0.0f, 0.4f, 0.0f, 0.7135420959f, 0.4870776437f, 0.009163385f,
    //     0.4098076211f, 0.0f, -0.1098076211f, 0.7135420959f, 0.4870776437f, 0.009163385f,
    //     0.3f, 0.0f, 0.3f, 0.7135420959f, 0.4870776437f, 0.009163385f,
    //     0.0f, 0.4f, 0.0f, 0.7669461611f, 0.1447912111f, 0.3784481615f,
    //     0.3f, 0.0f, 0.3f, 0.7669461611f, 0.1447912111f, 0.3784481615f,
    //     -0.1098076211f, 0.0f, 0.4098076211f, 0.7669461611f, 0.1447912111f, 0.3784481615f,
    //     0.0f, 0.4f, 0.0f, 0.2321058843f, 0.0893231443f, 0.8212044249f,
    //     -0.1098076211f, 0.0f, 0.4098076211f, 0.2321058843f, 0.0893231443f, 0.8212044249f,
    //     -0.4098076211f, 0.0f, 0.1098076211f, 0.2321058843f, 0.0893231443f, 0.8212044249f,
    //     0.0f, 0.4f, 0.0f, 0.628434076f, 0.6623973755f, 0.0981678636f,
    //     -0.4098076211f, 0.0f, 0.1098076211f, 0.628434076f, 0.6623973755f, 0.0981678636f,
    //     -0.3f, 0.0f, -0.3f, 0.628434076f, 0.6623973755f, 0.0981678636f,
    //     0.0f, -0.4f, 0.0f, 0.3930452327f, 0.1704100815f, 0.1118084155f,
    //     -0.3f, 0.0f, -0.3f, 0.3930452327f, 0.1704100815f, 0.1118084155f,
    //     0.1098076211f, 0.0f, -0.4098076211f, 0.3930452327f, 0.1704100815f, 0.1118084155f,
    //     0.0f, -0.4f, 0.0f, 0.2015423091f, 0.8579473578f, 0.296699785f,
    //     0.1098076211f, 0.0f, -0.4098076211f, 0.2015423091f, 0.8579473578f, 0.296699785f,
    //     0.4098076211f, 0.0f, -0.1098076211f, 0.2015423091f, 0.8579473578f, 0.296699785f,
    //     0.0f, -0.4f, 0.0f, 0.2245422345f, 0.3296623273f, 0.9089737724f,
    //     0.4098076211f, 0.0f, -0.1098076211f, 0.2245422345f, 0.3296623273f, 0.9089737724f,
    //     0.3f, 0.0f, 0.3f, 0.2245422345f, 0.3296623273f, 0.9089737724f,
    //     0.0f, -0.4f, 0.0f, 0.2055296789f, 0.1924532933f, 0.6339205417f,
    //     0.3f, 0.0f, 0.3f, 0.2055296789f, 0.1924532933f, 0.6339205417f,
    //     -0.1098076211f, 0.0f, 0.4098076211f, 0.2055296789f, 0.1924532933f, 0.6339205417f,
    //     0.0f, -0.4f, 0.0f, 0.1084795311f, 0.2213584152f, 0.0852229093f,
    //     -0.1098076211f, 0.0f, 0.4098076211f, 0.1084795311f, 0.2213584152f, 0.0852229093f,
    //     -0.4098076211f, 0.0f, 0.1098076211f, 0.1084795311f, 0.2213584152f, 0.0852229093f,
    //     0.0f, -0.4f, 0.0f, 0.3697238863f, 0.7677923485f, 0.649349796f,
    //     -0.4098076211f, 0.0f, 0.1098076211f, 0.3697238863f, 0.7677923485f, 0.649349796f,
    //     -0.3f, 0.0f, -0.3f, 0.3697238863f, 0.7677923485f, 0.649349796f

    // };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    view = camera.GetViewMatrix();

    ourShader.use();
    ourShader.setMat4("projection", projection);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        view = camera.GetViewMatrix();

        glm::mat4 MVP = projection * view * translate * model;
        unsigned int MVPLoc = glGetUniformLocation(ourShader.ID, "MVP");

        glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

        glBindVertexArray(VAO);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, N_VERTICES);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

int input()
{
    int shape_id;

    cout << "Please choose one of the following:\n"
         << "Enter 1 for Decagonal Prism\n"
         << "Enter 2 for Hexagonal Dipyramid\n"
         << "Enter 3 for Undecagonal Pyramid\n";

    cin >> shape_id;

    return shape_id;
}

void moveObject(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        translate = glm::translate(translate, glm::vec3(0, 1.0f * deltaTime, 0));

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        translate = glm::translate(translate, glm::vec3(0, -1.0f * deltaTime, 0));

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        translate = glm::translate(translate, glm::vec3(-1.0f * deltaTime, 0, 0));

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        translate = glm::translate(translate, glm::vec3(1.0f * deltaTime, 0, 0));

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        translate = glm::translate(translate, glm::vec3(0, 0, 1.0f * deltaTime));

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        translate = glm::translate(translate, glm::vec3(0, 0, -1.0f * deltaTime));
}

void moveCamera(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
}

void teleportCamera(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        glm::vec3 objectPosition = glm::vec3(translate[3][0], translate[3][1], translate[3][2]);
        glm::vec3 fixedPosition = glm::vec3(0.0f, 0.0f, 3.0f);

        camera.teleportCamera(objectPosition, fixedPosition);
    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        glm::vec3 objectPosition = glm::vec3(translate[3][0], translate[3][1], translate[3][2]);
        glm::vec3 fixedPosition = glm::vec3(0.0f, 0.0f, -3.0f);

        camera.teleportCamera(objectPosition, fixedPosition);
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        glm::vec3 objectPosition = glm::vec3(translate[3][0], translate[3][1], translate[3][2]);
        glm::vec3 fixedPosition = glm::vec3(3.0f, 0.0f, 3.0f);

        camera.teleportCamera(objectPosition, fixedPosition);
    }
}

void spinObject(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(1, 0, 0));

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0, 1, 0));

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0, 0, 1));
}

void spinCamera(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        camera.ProcessKeyboard(SPIN, deltaTime);
    }
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    moveObject(window);
    moveCamera(window);
    teleportCamera(window);
    spinObject(window);
    spinCamera(window);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
