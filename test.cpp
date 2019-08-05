#include <iostream>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

int main()
{
    glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
    // glm::vec3 xAxis = glm::normalize(glm::cross(zAxis, yAxis));

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
    trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0));
    trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
    zAxis = glm::normalize(glm::vec3(trans * glm::vec4(zAxis, 1.0f)));
    yAxis = glm::normalize(glm::vec3(trans * glm::vec4(yAxis, 1.0f)));
    xAxis = glm::normalize(glm::vec3(trans * glm::vec4(xAxis, 1.0f)));

    std::cout << "x = " << xAxis.x << " y = " << xAxis.y << " z = " << xAxis.z << std::endl;
    std::cout << "x = " << yAxis.x << " y = " << yAxis.y << " z = " << yAxis.z << std::endl;
    std::cout << "x = " << zAxis.x << " y = " << zAxis.y << " z = " << zAxis.z << std::endl;

    glm::vec3 position = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::mat4 view = glm::mat4(xAxis.x, yAxis.x, zAxis.x, 0.0f,
                            xAxis.y, yAxis.y, zAxis.y, 0.0f,
                            xAxis.z, yAxis.z, zAxis.z, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f);
    view = glm::translate(view, glm::vec3(-1.0, 0.0, 0.0));
    glm::vec3 pos = view * glm::vec4(position, 1.0f);

    std::cout << "x = " << pos.x << " y = " << pos.y << " z = " << pos.z << std::endl;
    std::cout << glm::cos(glm::radians(30.0f)) << std::endl;

    return 0;
}