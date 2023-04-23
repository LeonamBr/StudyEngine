#ifndef SCENEHIERARCHYPANEL_H
#define SCENEHIERARCHYPANEL_H

#include "../../StudyEngine/src/Study.h"
#include "../../StudyEngine/src/Engine/Core/Core.h"

namespace Study {

    class SceneHierarchyPanel {

        public:

            SceneHierarchyPanel(const Shared<Scene>& context);
            virtual ~SceneHierarchyPanel() = default;

            void SetContext(const Shared<Scene>& context);
            void OnImGuiRender();
            void OnAttach();

            Entity GetSelectedEntity() const { return m_SelectionContext; }

        private:

            void DrawEntityNode(Entity entity);
            void DrawComponents(Entity entity);

        private:

            Shared<Scene> m_Context;
            Entity m_SelectionContext;

    };

}

#endif