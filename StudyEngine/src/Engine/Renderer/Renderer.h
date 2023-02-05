#ifndef RENDERER_H
#define RENDERER_H

namespace Study {

    enum class RendererAPI {

        None = 0, OpenGL

    };

    class STUDY_API Renderer {

        public:
            inline static RendererAPI GetAPI() { return s_RendererAPI; } 

        private:
            static RendererAPI s_RendererAPI;

    };



}

#endif