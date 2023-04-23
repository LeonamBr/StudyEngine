#ifndef MATH_H
#define MATH_H

#include <glm/glm.hpp>

namespace Study::Math {

    bool STUDY_API DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);


}

#endif