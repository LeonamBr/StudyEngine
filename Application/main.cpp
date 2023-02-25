#include "../StudyEngine/src/Study.h"

#include "SandBox2D.h"

#include "../StudyEngine/src/Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TestAPI : public Study::Application{

    public:
        TestAPI(){

            PushLayer(new SandBox2D());

        }
        ~TestAPI(){}

};

Study::Application* Study::CreateApplication(){

    return new TestAPI();
}