#include "myEffect.h"

/// @brief Constructeur hérité de la classe Effect qui effectue la gestion du FBO dans les shaders
/// @param shaderPath le repertoire contenant les shaders
myEffect::myEffect(const QString &shaderPath) : Effect(shaderPath)
{
}

myEffect::~myEffect()
{
}

/// @brief Effectue le rendu en ajoutant le FBO contenant la scène en tant que texture
/// @param channel le channel de la texture
/// @param buffer_name le nom de la texture contenant le FBO dans le shader
/// @param frameBuffer le Frame Buffer Object
void myEffect::render(int channel, char *buffer_name, FBO *frameBuffer)
{
    // activation des shaders
    this->m_program->bind();

    // passage des uniformes, des textures ou texture de FBO
    this->attachTexture(channel, buffer_name, frameBuffer);
    this->m_program->setUniformValue("resolution", frameBuffer->getSize());

    // affichage de Quadrangle couvrant l'écran
    this->m_geometry->bindVertices(this->attribPos);
    this->m_geometry->draw();
    // desactivation des shaders
    this->m_program->release();
}

/// @brief Fonction qui permet d'activer ou désactiver le rendu du FBO
/// @param filterOn
void myEffect::setFilter(bool filterOn)
{
    // activation des shaders
    this->m_program->bind();
    if (filterOn)
    {
        qDebug() << " Set current FBO filter ON";
        this->m_program->setUniformValue("filterOn", 1);
    }
    else
    {
        qDebug() << " Set current FBO filter OFF";
        this->m_program->setUniformValue("filterOn", 2);
    }
    // desactivation des shaders
    this->m_program->release();
}
