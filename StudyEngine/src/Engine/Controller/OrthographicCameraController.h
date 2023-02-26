#ifndef ORTHOGRAPHICCAMERACONTROLLER_H
#define ORTHOGRAPHICCAMERACONTROLLER_H

#include "../Renderer/OrthographicCamera.h"
#include "../Core/Timer.h"
#include "../Event/ApplicationEvent.h"
#include "../Event/MouseEvent.h"

namespace Study {


    class STUDY_API OrthographicCameraController {

        public:

            OrthographicCameraController(float aspectRatio, bool rotation = false);
            ~OrthographicCameraController() = default;

            void OnUpdate(Timer timestep);
            void OnEvent(Event& e);

            OrthographicCamera& GetCamera() { return m_Camera; }
            const OrthographicCamera& GetCamera() const { return m_Camera; }
            float GetZoomLevel() const { return m_ZoomLevel; }
            void SetZoomLevel(float level) { m_ZoomLevel = level; CalculateView(); }

        private:

            void CalculateView();

            bool OnMouseScrolled(MouseScrolledEvent& e);
            bool OnWindowResized(WindowResizeEvent& e);

        private:

            float m_AspectRatio;
            float m_ZoomLevel = 1.0f;
            OrthographicCamera m_Camera;

            bool m_Rotation;
            glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
            float m_CameraRotation = 0.0f;

            float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;

    };

}

#endif