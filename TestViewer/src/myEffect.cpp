#include "myEffect.h"

myEffect::myEffect(const QString & shaderPath) {
    this->m_shaderPath = shaderPath;
}

void myEffect::render(FBO * frameBuffer) {
    //activation des shaders
    this->m_program->bind();

    //TODO : passage des uniformes, des textures ou texture de FBO
    //...
    this->attachTexture(0, "frameBuffer", frameBuffer);


    //affichage de Quadrangle couvrant l'écran
    this->m_geometry->bindVertices(this->attribPos);
    this->m_geometry->draw();
    //desactivation des shaders
    this->m_program->release();
}
