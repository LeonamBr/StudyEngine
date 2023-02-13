#include "../../Headers.h"
#include "OrthographicCameraController.h"

#include "../Core/Input.h"
#include "../Core/KeyCodes.h"

namespace Study {

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) :m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio*m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
    {

    }

    void OrthographicCameraController::OnUpdate(Timer timestep)
    {

        if(Input::IsKeyPressed(STUDY_KEY_LEFT))
                m_CameraPosition.x -= m_CameraTranslationSpeed*timestep;
            else if(Input::IsKeyPressed(STUDY_KEY_RIGHT))
                m_CameraPosition.x += m_CameraTranslationSpeed*timestep;

            if(Input::IsKeyPressed(STUDY_KEY_UP))
                m_CameraPosition.y += m_CameraTranslationSpeed*timestep;
            else if(Input::IsKeyPressed(STUDY_KEY_DOWN))
                m_CameraPosition.y -= m_CameraTranslationSpeed*timestep;

        if(m_Rotation){
            if(Input::IsKeyPressed(STUDY_KEY_A))
                m_CameraRotation += m_CameraRotationSpeed*timestep;
            if(Input::IsKeyPressed(STUDY_KEY_D))
                m_CameraRotation -= m_CameraRotationSpeed*timestep;
            
            m_Camera.SetRotation(m_CameraRotation);
        }
            
        m_Camera.SetPosition(m_CameraPosition);

        m_CameraTranslationSpeed = m_ZoomLevel;

    }

    void OrthographicCameraController::OnEvent(Event &e)
    {

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(STUDY_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(STUDY_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e)
    {
        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio*m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &e)
    {
        m_ZoomLevel = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio*m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}