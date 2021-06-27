#define STB_IMAGE_IMPLEMENTATION
#pragma once
#include <GL/glew.h>
#include "cpp/Camera.cpp"
#include "cpp/Shader.cpp"
#include "cpp/Texture.cpp"

 int main() {
	Camera Camera;
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.majorVersion = 4;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Core;

	sf::Window window(sf::VideoMode(800, 600, 32), "First Window",
		sf::Style::Titlebar | sf::Style::Close, settings);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Error:: glew not init =(" << std::endl;
		return -1;
	}
    // настройки
    glEnable(GL_DEPTH_TEST);

	// шейдеры и текстуры
	Shader box("res/shaders/combined.vs", "res/shaders/combined.fs");
    Shader lamp("res/shaders/lamp.vs", "res/shaders/lamp.fs");
	// ====================

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    float vertices[] = {
        // координаты        // нормали           // текстурные координаты
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
       -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };


    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };


    // 1. Настраиваем VAO (и VBO) куба
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // 2. Настраиваем VAO света (VBO остается неизменным; вершины те же и для светового объекта, который также является 3D-кубом)
    unsigned int lightCubeVAO;;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Обратите внимание, что мы обновляем шаг атрибута положения лампы, чтобы отразить обновленные данные буфера
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ================================================
    Texture diffuseMap("res/imgs/box.png");
    //Texture specularMap("res/imgs/frame.png");
    // ================================================
    box.use();
    box.set_int("material.diffuse", 0);
    //box.set_int("material.specular", 1);
    // ================================================
	sf::Mouse::setPosition(sf::Vector2i(800/2, 600/2), window);
    Camera.set_pos(0.0f, 2.0f, 7.0f);

	bool isGo = true;
    //float phi = 0.0f;

	while (isGo) {
        //phi += 0.0005f;
		// ========== обработка событий
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) {
			switch (windowEvent.type) {
			case sf::Event::Closed:
				isGo = false;
				break;
			case sf::Event::KeyPressed:
				Camera.keyboard();
				break;
			case sf::Event::MouseMoved:
				Camera.move_mouse(window);
				break;
			case sf::Event::MouseWheelScrolled:
				Camera.scroll(windowEvent.mouseWheelScroll.delta);
				break;
			default:
				break;
			}
		}
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // ================================================
        box.use();
        box.set_vec3("viewPos", Camera.get_pos());
        box.set_float("material.shininess", 32.0f);

        // Направленный свет
        box.set_vec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        box.set_vec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        box.set_vec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        box.set_vec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

        // Точечный источник света №1
        box.set_vec3("pointLights[0].position", pointLightPositions[0]);
        box.set_vec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        box.set_vec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        box.set_vec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        box.set_float("pointLights[0].constant", 1.0f);
        box.set_float("pointLights[0].linear", 0.09);
        box.set_float("pointLights[0].quadratic", 0.032);

        // Точечный источник света №2
        box.set_vec3("pointLights[1].position", pointLightPositions[1]);
        box.set_vec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        box.set_vec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        box.set_vec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        box.set_float("pointLights[1].constant", 1.0f);
        box.set_float("pointLights[1].linear", 0.09);
        box.set_float("pointLights[1].quadratic", 0.032);

        // Точечный источник света №3
        box.set_vec3("pointLights[2].position", pointLightPositions[2]);
        box.set_vec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        box.set_vec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        box.set_vec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        box.set_float("pointLights[2].constant", 1.0f);
        box.set_float("pointLights[2].linear", 0.09);
        box.set_float("pointLights[2].quadratic", 0.032);

        // Точечный источник света №4
        box.set_vec3("pointLights[3].position", pointLightPositions[3]);
        box.set_vec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        box.set_vec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        box.set_vec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        box.set_float("pointLights[3].constant", 1.0f);
        box.set_float("pointLights[3].linear", 0.09);
        box.set_float("pointLights[3].quadratic", 0.032);

        // Прожектор
        box.set_vec3("spotLight.position", Camera.get_pos());
        box.set_vec3("spotLight.direction", Camera.get_front());
        box.set_vec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        box.set_vec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        box.set_vec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        box.set_float("spotLight.constant", 1.0f);
        box.set_float("spotLight.linear", 0.09);
        box.set_float("spotLight.quadratic", 0.032);
        box.set_float("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        box.set_float("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        // Преобразования Вида/Проекции
        box.set_mat4("projection", Camera.get_projection());
        box.set_mat4("view", Camera.get_view());

        // Рендеринг контейнеров
        glBindVertexArray(cubeVAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // Вычисляем матрицу модели для каждого объекта и передаем её в шейдер
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            box.set_mat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Также отрисовываем объект лампы
        lamp.use();
        lamp.set_mat4("projection", Camera.get_projection());
        lamp.set_mat4("view", Camera.get_view());

        // А теперь мы отрисовываем столько ламп, сколько у нас есть точечных источников света
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // меньший куб
            lamp.set_mat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // ================================================
		window.display();
	}


	window.close();
	return 0;
}
