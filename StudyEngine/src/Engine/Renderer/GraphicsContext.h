#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

namespace Study {

    class STUDY_API GraphicsContext {

        public:

            virtual void Init() = 0;
            virtual void SwapBuffers() = 0;

    };

}

#endif