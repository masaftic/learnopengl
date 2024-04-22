#include "spriteRenderer.h"
#include <VBO.h>

SpriteRenderer::SpriteRenderer(Shader& shader) : quadVAO()
{
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    this->quadVAO.Delete();
}

void SpriteRenderer::DrawSprite(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    this->shader.Use();

    glm::mat4 model =  {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    model = glm::translate(model, glm::vec3(position, 0.0f));
    // moving the origin to the center instead of top-left (vertices origin is top left)
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    // reverse moving the origin
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->shader.setMat4("model", model);
    this->shader.setVec3("spriteColor", color);


    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    
    this->quadVAO.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}



void SpriteRenderer::initRenderData()
{
    float vertices[] = {
        // pos          // tex
        0.0f, 1.0f,     0.0f, 1.0f,
        1.0f, 0.0f,     1.0f, 0.0f,
        0.0f, 0.0f,     0.0f, 0.0f,
                        
        0.0f, 1.0f,     0.0f, 1.0f,
        1.0f, 1.0f,     1.0f, 1.0f,
        1.0f, 0.0f,     1.0f, 0.0f
    };

	VBO vbo(vertices, sizeof(vertices));

    this->quadVAO.Bind();
    this->quadVAO.LinkAtrrib(vbo, 0, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);

    vbo.Unbind();
    this->quadVAO.Unbind();
}
