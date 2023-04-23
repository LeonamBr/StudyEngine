#include "SceneHierarchyPanel.h"

#include "../../StudyEngine/include/imGUI/imgui.h"
#include "../../StudyEngine/include/imGUI/imgui_internal.h"
#include "../../StudyEngine/src/Engine/Scene/Scene.h"
#include <glm/gtc/type_ptr.hpp>



namespace Study {

    SceneHierarchyPanel::SceneHierarchyPanel(const Shared<Scene> &context)
    {
        SetContext(context);
        ImGui::SetCurrentContext(ImGuiLayer::GetContext());
    }

    void SceneHierarchyPanel::SetContext(const Shared<Scene> &context)
    {
        m_Context = context;
        m_SelectionContext = {};
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {

        ImGui::Begin("Scene Entities");

        if(m_Context)
        {
            m_Context->m_Registry.each( [&, this](auto entityID)
            { 
                Entity entity { entityID, m_Context.get()};

                DrawEntityNode(entity);
    
            });

            if(ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
                m_SelectionContext = {};

            if(ImGui::BeginPopupContextWindow(0, ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
            {
                if(ImGui::MenuItem("Create empty entity"))
                    m_Context->CreateEntity("Empty Entity");
                
                ImGui::EndPopup();

            }

        }

        ImGui::End();


        ImGui::Begin("Properties");

            if(m_SelectionContext)
            {
                DrawComponents(m_SelectionContext);
            }

        ImGui::End();

    }

    void SceneHierarchyPanel::OnAttach()
    {
        ImGui::SetCurrentContext(ImGuiLayer::GetContext());
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {

        auto& tagComponent = entity.GetComponent<TagComponent>().Tag;
        ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
        
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tagComponent.c_str());

        if(ImGui::IsItemClicked())
        {
            m_SelectionContext = entity;
        }

        bool entityDeleted = false;
        if(ImGui::BeginPopupContextItem())
        {
            if(ImGui::MenuItem("Delete entity"))
                entityDeleted = true;
            
            ImGui::EndPopup();

        }


        if(opened)
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
            bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tagComponent.c_str());
            if(opened)
                ImGui::TreePop();
            ImGui::TreePop();
        }

        if(entityDeleted)
        {
            m_Context->DeleteEntity(entity);
            if(m_SelectionContext == entity)
                m_SelectionContext = {};
        }
    }

    static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 80.0f)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 4.0f, lineHeight};

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.1f, 0.75f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.3f, 0.85f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.1f, 0.75f, 1.0f});
        ImGui::PushFont(boldFont);

        if(ImGui::Button("X", buttonSize))
            values.x = resetValue;

        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.75f, 0.1f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.85f, 0.3f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.75f, 0.1f, 1.0f});
        ImGui::PushFont(boldFont);

        if(ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.75f, 0.1f, 0.1f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.85f, 0.3f, 0.3f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.75f, 0.1f, 0.1f, 1.0f});
        ImGui::PushFont(boldFont);

        if(ImGui::Button("Z", buttonSize))
            values.z = resetValue;

        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f);
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();

    }

    template<typename T, typename UIFunction>
    static void DrawComponent(const std::string& name, Entity entity, UIFunction function)
    {

        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap |  ImGuiTreeNodeFlags_SpanAvailWidth |  ImGuiTreeNodeFlags_FramePadding;

        if(entity.HasComponent<T>())
        {
            auto& component = entity.GetComponent<T>();
            ImVec2 contentRegionAvaliable = ImGui::GetContentRegionAvail();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4});
            float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y + 4.0f;
            ImGui::Separator();
            bool IsOpen = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
            ImGui::PopStyleVar();
            ImGui::SameLine(contentRegionAvaliable.x - lineHeight );

            if(ImGui::Button("+", ImVec2{ lineHeight, lineHeight}))
            {
                ImGui::OpenPopup("ComponentSetings");
            }

            bool removeComponent = false;
            if(ImGui::BeginPopup("ComponentSetings"))
            {
                if (ImGui::MenuItem("RemoveComponent"))
                    removeComponent = true;
                
                ImGui::EndPopup();
            }

            if(IsOpen)
            {
                function(component);
                ImGui::TreePop();
            }

            if(removeComponent)
                entity.RemoveComponent<T>();

        }

    }

    void SceneHierarchyPanel::DrawComponents(Entity entity)
    {

        if(entity.HasComponent<TagComponent>())
        {

            auto& tagComponent = entity.GetComponent<TagComponent>().Tag;

            static char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), tagComponent.c_str());

            if(ImGui::InputText("##: Name", buffer, sizeof(buffer)))
            {
                tagComponent = std::string(buffer);
            }

        }

        ImGui::SameLine();
        ImGui::PushItemWidth(-1);

        if(ImGui::Button("Add Component"))
            ImGui::OpenPopup("AddComponent");
                
        if(ImGui::BeginPopup("AddComponent"))
        {

            if(ImGui::MenuItem("Camera"))
            {
                m_SelectionContext.AddComponents<CameraComponent>();
                ImGui::CloseCurrentPopup();
            }

            if(ImGui::MenuItem("Sprite Renderer"))
            {
                m_SelectionContext.AddComponents<SpriteRendererComponent>();
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        ImGui::PopItemWidth();

        DrawComponent<TransformComponent>("Transform Component", entity, [](auto& component)
        {

            DrawVec3Control("Translate", component.Translation);
            glm::vec3 rotation = glm::degrees(component.Rotation);
            DrawVec3Control("Rotation", rotation);
            component.Rotation = glm::radians(rotation);
            DrawVec3Control("Scale", component.Scale, 1.0f);

        });

        DrawComponent<CameraComponent>("Camera Component", entity, [](auto& component)
        {

            ImGui::Checkbox("Primary", &component.Primary);

           
            const char* ProjectionTypeString[] = {"Perpective", "orthographic" };
            const char* currentProjectionTypeString = ProjectionTypeString[(int)component.Camera.GetProjectionType()];

                if(ImGui::BeginCombo("Projection", currentProjectionTypeString))
                {
                    for(int i = 0; i < 2; i++)
                    {
                        bool isSelected = currentProjectionTypeString == ProjectionTypeString[i];
                        if(ImGui::Selectable(ProjectionTypeString[i], isSelected))
                        {
                            currentProjectionTypeString = ProjectionTypeString[i];
                            component.Camera.SetProjectionType((SceneCamera::ProjectionType)i);
                        }

                        if(isSelected)
                            ImGui::SetItemDefaultFocus();
                    }

                    ImGui::EndCombo();
                }

                if(component.Camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
                {

                    float perspectiveFOV = glm::degrees(component.Camera.GetPerspectiveFOV());
                    if(ImGui::DragFloat("Fov", &perspectiveFOV))
                        component.Camera.SetPerspectiveFOV(glm::radians(perspectiveFOV));
                        
                    float perspectiveNear = component.Camera.GetPerspectiveNearClip();
                    if(ImGui::DragFloat("Nearclip", &perspectiveNear))
                        component.Camera.SetPerspectiveNearClip(perspectiveNear);
                       
                    float perspectiveFar = component.Camera.GetPerspectiveFarClip();
                    if(ImGui::DragFloat("Farclip", &perspectiveFar))
                        component.Camera.SetPerspectiveFarClip(perspectiveFar);

                        
                }

                if(component.Camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
                {
                        
                    float orthoSize = component.Camera.GetOrthographicSize();
                    if(ImGui::DragFloat("Size", &orthoSize))
                        component.Camera.SetOrthographicSize(orthoSize);
                        
                    float orthoNear = component.Camera.GetOrthographicNearClip();
                    if(ImGui::DragFloat("Nearclip", &orthoNear))
                        component.Camera.SetOrthographicNearClip(orthoNear);
                       
                    float orthoFar = component.Camera.GetOrthographicFarClip();
                    if(ImGui::DragFloat("Farclip", &orthoFar))
                        component.Camera.SetOrthographicFarClip(orthoFar);

                }

        });

        DrawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [](auto& component)
        {
            ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
        });

    }
}