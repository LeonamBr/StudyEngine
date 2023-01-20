#include <Study.h>

class LayerTest : public Study::Layer{

    public:
        LayerTest() : Layer("Test!"){

        }

        void OnUpdate() override{
            STUDY_INFO("TestLayer::Layer");
        }

        void OnEvent(Study::Event& event) override{
            STUDY_TRACE("{0}", event);
        }

};

class TestAPI : public Study::Application{

    public:
        TestAPI(){

            PushLayer(new LayerTest());
            PushOverlay(new Study::ImGuiLayer());

        }
        ~TestAPI(){}

};

Study::Application* Study::CreateApplication(){

    return new TestAPI();
}