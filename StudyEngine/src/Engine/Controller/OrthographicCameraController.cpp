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

        STUDY_PROFILE_FUNCTION();

        if(Input::IsKeyPressed(STUDY_KEY_LEFT))
        {
            m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
        }
        else if(Input::IsKeyPressed(STUDY_KEY_RIGHT))
        {
            m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
        }
        if(Input::IsKeyPressed(STUDY_KEY_UP))
        {
            m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
        }
        else if(Input::IsKeyPressed(STUDY_KEY_DOWN))
        {
            m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
        }

        if(m_Rotation){

            if(Input::IsKeyPressed(STUDY_KEY_A))
                m_CameraRotation += m_CameraRotationSpeed*timestep;
            if(Input::IsKeyPressed(STUDY_KEY_D))
                m_CameraRotation -= m_CameraRotationSpeed*timestep;

            if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;
            
            m_Camera.SetRotation(m_CameraRotation);
        }
            
        m_Camera.SetPosition(m_CameraPosition);

        m_CameraTranslationSpeed = m_ZoomLevel;

    }

    void OrthographicCameraController::OnEvent(Event &e)
    {

        STUDY_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(STUDY_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(STUDY_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

    }

    void OrthographicCameraController::CalculateView()
    {

        m_Camera.SetProjection(-m_AspectRatio*m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e)
    {

        STUDY_PROFILE_FUNCTION();

        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        CalculateView();
        
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &e)
    {

        STUDY_PROFILE_FUNCTION();

        m_ZoomLevel = (float)e.GetWidth() / (float)e.GetHeight();
        CalculateView();
        return false;
    }
}