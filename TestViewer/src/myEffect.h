#ifndef MYEFFECT_H
#define MYEFFECT_H

#include "Effect.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QColor>
#include "QString"

/// @brief Classe qui permet de faire des effets sur scène contenu dans le FBO
class myEffect : public Effect {
public:
    /// @brief Constructeur hérité de la classe Effect qui effectue la gestion du FBO dans les shaders
    /// @param shaderPath le repertoire contenant les shaders
    myEffect( const QString & shaderPath = "./data/myEffect/" );
    virtual ~myEffect();

    /// @brief Effectue le rendu en ajoutant le FBO contenant la scène en tant que texture
    /// @param channel le channel de la texture
    /// @param buffer_name le nom de la texture contenant le FBO dans le shader
    /// @param frameBuffer le Frame Buffer Object
    void render(int channel, char * buffer_name, FBO * frameBuffer);
    /// @brief Fonction qui permet d'activer ou désactiver le rendu du FBO
    /// @param filterOn 
    void setFilter(bool filterOn);

private:
    QString m_shaderPath;
};

#endif // MYEFFECT_H
