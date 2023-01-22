#include "../StudyEngine/src/Study.h"


class LayerTest : public Study::Layer{

    public:
        LayerTest() : Layer("Test!"){

        }

        void OnUpdate() override{
            
        }

        virtual void OnImGuiRender() override{

        }

        void OnEvent(Study::Event& event) override{

            if(event.GetEventType() == Study::EventType::kPressed){
            
                if(Study::Input::IsKeyPressed(STUDY_KEY_SPACE))
                STUDY_TRACE("Space key has pressed");
                else {
                Study::KeyPressedEvent& e = (Study::KeyPressedEvent&)event;
                STUDY_TRACE("{0}", (char)e.GetKeyCode());
                }
            }
        }

};

class TestAPI : public Study::Application{

    public:
        TestAPI(){

            PushLayer(new LayerTest());

        }
        ~TestAPI(){}

};

Study::Application* Study::CreateApplication(){

    return new TestAPI();
}