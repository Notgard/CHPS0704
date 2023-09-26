#include "myEffect.h"

myEffect::myEffect(const QString & shaderPath): Effect(shaderPath) {
}

myEffect::~myEffect() {

}

void myEffect::render(int channel, char * buffer_name, FBO * frameBuffer) {
    //activation des shaders
    this->m_program->bind();

    //TODO : passage des uniformes, des textures ou texture de FBO
    //...
    this->attachTexture(channel, buffer_name, frameBuffer);
    this->m_program->setUniformValue("resolution", frameBuffer->getSize());

    //affichage de Quadrangle couvrant l'écran
    this->m_geometry->bindVertices(this->attribPos);
    this->m_geometry->draw();
    //desactivation des shaders
    this->m_program->release();
}

void myEffect::setFilter(bool filterOn) {
    //activation des shaders
    this->m_program->bind();
    if(filterOn) {
        qDebug() << " Set current FBO filter ON";
        this->m_program->setUniformValue("filterOn", 1);
    } else {
        qDebug() << " Set current FBO filter OFF";
        this->m_program->setUniformValue("filterOn", 2);
    }
    //desactivation des shaders
    this->m_program->release();
}
