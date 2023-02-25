#ifndef SANDBOX2D_H
#define SANDBOX2D_H

#include "../StudyEngine/src/Study.h"

class SandBox2D : public Study::Layer {
    public:

        SandBox2D();
        virtual ~SandBox2D() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnUpdate(Study::Timer timestep) override;
        virtual void OnImGuiRender() override;
        void OnEvent(Study::Event& e) override;
    
    private:
        
        Study::OrthographicCameraController m_CameraController;

        Study::Shared<Study::VertexArray> m_VertexArray;
        Study::Shared<Study::Shader> m_Shader;
        Study::Shared<Study::Texture2D> m_Texture, m_Background, m_Ghost, m_Jeff, m_Marcus, m_Nicholas;

        glm::vec4 m_SquareColor = {1.0f, 0.0f, 0.0f, 1.0f};

        static float s_FPS;
        static float s_Time;

};

#endif