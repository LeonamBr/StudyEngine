#include "../../Headers.h"

#include "PlatformUtils.h"

#include <commdlg.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "../Core/Application.h"

namespace Study {
    
    std::string FileDialogs::OpenFile(const char *filter)
    {

        OPENFILENAMEA openFileName;
        CHAR fileSize[260] = { 0 };
        
        ZeroMemory(&openFileName, sizeof(OPENFILENAME));
        openFileName.lStructSize = sizeof(OPENFILENAME);
        openFileName.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
        openFileName.lpstrFile = fileSize;
        openFileName.nMaxFile = sizeof(fileSize);
        openFileName.lpstrFilter = filter;
        openFileName.nFilterIndex = 1;
        openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if(GetOpenFileNameA(&openFileName) == TRUE)
        {
            return openFileName.lpstrFile;
        }

        return std::string();
    }

    std::string FileDialogs::SaveFile(const char *filter)
    {

        OPENFILENAMEA openFileName;
        CHAR fileSize[260] = { 0 };

        ZeroMemory(&openFileName, sizeof(OPENFILENAME));
        openFileName.lStructSize = sizeof(OPENFILENAME);
        openFileName.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
        openFileName.lpstrFile = fileSize;
        openFileName.nMaxFile = sizeof(fileSize);
        openFileName.lpstrFilter = filter;
        openFileName.nFilterIndex = 1;
        openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if(GetSaveFileNameA(&openFileName) == TRUE)
        {
            return openFileName.lpstrFile;
        }

        return std::string();
    }

}