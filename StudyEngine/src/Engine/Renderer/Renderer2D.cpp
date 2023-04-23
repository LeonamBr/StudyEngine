#include "../../Headers.h"

#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RendererCommand.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Study {

    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexIndex;
        float Scale;
    };

    struct Renderer2DData
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
        static const uint32_t MaxTexturesSlots = 32;

		Shared<VertexArray> QuadVertexArray;
		Shared<VertexBuffer> QuadVertexBuffer;
		Shared<Shader> TextureShader;
		Shared<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

        std::array<Shared<Texture2D>, MaxTexturesSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1;

        glm::vec4 QuadVertexPositions[4];

        Renderer2D::Statistics Stats;

	};

    static Renderer2DData s_Data;

    void Renderer2D::Init()
    {

        STUDY_PROFILE_FUNCTION();
    
        s_Data.QuadVertexArray = VertexArray::Create();

        s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
       
        s_Data.QuadVertexBuffer->SetLayout({
            { ShaderDataType::Vec3, "a_Position" },
            { ShaderDataType::Vec4, "a_Color"},
            { ShaderDataType::Vec2, "a_Texture"},
            { ShaderDataType::Float, "a_TexIndex"},
            { ShaderDataType::Float, "a_Scale"}
        });

    
        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

        s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

        uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

        uint32_t offset = 0;

        for(uint32_t i = 0; i < s_Data.MaxIndices; i+=6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;

        }

    Shared<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
    s_Data.QuadVertexArray->AddIndexBuffer(quadIB);
    delete[] quadIndices;

    s_Data.WhiteTexture = Texture2D::Create(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

    int32_t samplers[s_Data.MaxTexturesSlots];
    for (uint32_t i = 0; i < s_Data.MaxTexturesSlots; i++ )
        samplers[i] = i;

    s_Data.TextureShader = Shader::Create("../Assets/Shaders/UniqueShader.glsl");
    s_Data.TextureShader->Bind();
    s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTexturesSlots);

    memset(s_Data.TextureSlots.data(), 0, s_Data.TextureSlots.size() * sizeof(uint32_t));

    
    s_Data.TextureSlots[0] = s_Data.WhiteTexture;

    s_Data.QuadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[3] = {-0.5f,  0.5f, 0.0f, 1.0f};

    }

    void Renderer2D::Shutdown()
    {
        STUDY_PROFILE_FUNCTION();
    }

    void Renderer2D::BeginScene(const Camera &camera, const glm::mat4 &transform)
    {

        STUDY_PROFILE_FUNCTION();

        glm::mat4 viewprojection = camera.GetProjection() * glm::inverse(transform);

        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetMat4("u_ViewProjection", viewprojection);

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        s_Data.TextureSlotIndex = 1;

    }

    void Renderer2D::BeginScene(const EditorCamera &camera)
    {

        STUDY_PROFILE_FUNCTION();

        glm::mat4 viewprojection = camera.GetViewProjection();

        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetMat4("u_ViewProjection", viewprojection);

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        s_Data.TextureSlotIndex = 1;

    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera)
    {

        STUDY_PROFILE_FUNCTION();

        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        s_Data.TextureSlotIndex = 1;

    }

    void Renderer2D::EndScene()
    {
        STUDY_PROFILE_FUNCTION();

        uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		Flush();
    }

    void Renderer2D::Flush()
	{

        for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
            s_Data.TextureSlots[i]->Bind(i);

		RendererCommand::DrawIndex(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
        s_Data.Stats.DrawCalls++;

	}

    void Renderer2D::StartNewBatch()
    {
        EndScene();

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        s_Data.TextureSlotIndex = 1;

    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        
            DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {

        STUDY_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4{1.0f}, {size.x, size.y, 1.0f});

        DrawQuad(transform, color);

    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Shared<Texture2D> &texture, float texScale, const glm::vec4& colorize)
    {

        DrawQuad({position.x, position.y, 0.0f}, size, texture, texScale, colorize);

    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Shared<Texture2D> &texture, float texScale, const glm::vec4& colorize)
    {
        STUDY_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4{1.0f}, {size.x, size.y, 1.0f});

       DrawQuad(transform, texture, texScale, colorize);

    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<SubTexture2D>& subtexture, float texScale, const glm::vec4& colorize)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, subtexture, texScale, colorize);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<SubTexture2D>& subtexture, float texScale, const glm::vec4& colorize)
    {

        STUDY_PROFILE_FUNCTION();

        constexpr size_t quadVertexCount = 4;
        constexpr glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
        const glm::vec2* textureCoords = subtexture->GetTexCoords();
        const Shared<Texture2D> texture = subtexture->GetTexture();

        if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
            StartNewBatch();

        float textureIndex = 0.0f;

        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
        {

            if(*s_Data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }

        }

        if(textureIndex == 0.0f)
        {
            textureIndex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4{1.0f}, {size.x, size.y, 1.0f});

       for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->Scale = texScale;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;        


    }

    void Renderer2D::DrawQuad(const glm::mat4 &transform, const glm::vec4 &color)
    {

        STUDY_PROFILE_FUNCTION();

        constexpr size_t quadVertexCount = 4;
		const float textureIndex = 0.0f; // White Texture
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float scale = 1.0f;

        if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
            StartNewBatch();

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->Scale = scale;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;

    }

    void Renderer2D::DrawQuad(const glm::mat4 &transform, const Shared<Texture2D> &texture, float texScale, const glm::vec4 &colorize)
    {

        STUDY_PROFILE_FUNCTION();

        constexpr size_t quadVertexCount = 4;
        constexpr glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
        constexpr glm::vec2 textureCoords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

        if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
            StartNewBatch();

        float textureIndex = 0.0f;

        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
        {

            if(*s_Data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }

        }

        if(textureIndex == 0.0f)
        {
            textureIndex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }

       for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->Scale = texScale;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;

    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {

        DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);

    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Shared<Texture2D> &texture, float texScale, const glm::vec4& colorize)
    {

        DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, texture, texScale, colorize);

    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {

        STUDY_PROFILE_FUNCTION();

        constexpr size_t quadVertexCount = 4;
		const float textureIndex = 0.0f;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float scale = 1.0f;

        if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
            StartNewBatch();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
            * glm::scale(glm::mat4{1.0f}, {size.x, size.y, 1.0f});

        for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->Scale = scale;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;
        
        s_Data.Stats.QuadCount++;

    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Shared<Texture2D> &texture, float texScale, const glm::vec4& colorize)
    {

        STUDY_PROFILE_FUNCTION();

        constexpr size_t quadVertexCount = 4;
		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

        if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
            StartNewBatch();

        float textureIndex = 0.0f;

        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
        {

            if(*s_Data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }

        }

        if(textureIndex == 0.0f)
        {
            textureIndex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
            * glm::scale(glm::mat4{1.0f}, {size.x, size.y, 1.0f});

        for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->Scale = texScale;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;

    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Shared<SubTexture2D> &subtexture, float texScale, const glm::vec4& colorize)
    {

        DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, subtexture, texScale, colorize);

    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Shared<SubTexture2D> &subtexture, float texScale, const glm::vec4& colorize)
    {

        STUDY_PROFILE_FUNCTION();

        constexpr size_t quadVertexCount = 4;
		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		const glm::vec2* textureCoords =  subtexture->GetTexCoords();
        const Shared<Texture2D> texture = subtexture->GetTexture();

        if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
            StartNewBatch();

        float textureIndex = 0.0f;

        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
        {

            if(*s_Data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }

        }

        if(textureIndex == 0.0f)
        {
            textureIndex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
            * glm::scale(glm::mat4{1.0f}, {size.x, size.y, 1.0f});

        for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->Scale = texScale;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;

    }


    void Renderer2D::ResetStats()
    {
        memset(&s_Data.Stats, 0, sizeof(Statistics));
    }

    Renderer2D::Statistics Renderer2D::GetStats()
    {
        return s_Data.Stats;
    }

}