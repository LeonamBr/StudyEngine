#ifndef PLATFORMUTILS_H
#define PLATFORMUTILS_H

#include <string>

namespace Study {

    class STUDY_API FileDialogs {
        
        public:
            static std::string OpenFile(const char* filter);
            static std::string SaveFile(const char* filter);
    };

}

#endif