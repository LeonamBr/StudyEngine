#ifndef IMGUIRENDERER_H
#define IMGUIRENDERER_H

#include <string>
#include <glm/glm.hpp>


namespace Study {

    class STUDY_API ImGUIRenderer {

        public:

            ImGUIRenderer(){}
            ~ImGUIRenderer() = default;

            void Begin(const char* name);
            void ColorEdit3(const std::string& name, float* value);
            void End();
            static void Init();
            static ImGUIRenderer* Get();
        
        private:
            static ImGUIRenderer* s_Instance;


    };

}



#endif