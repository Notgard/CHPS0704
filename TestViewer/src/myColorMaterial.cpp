#include "myColorMaterial.h"

/// @brief Constructeur qui prend la couleur choisi, le chemin du répertoire des shaders et le nom de la couleur
/// @param col la couleur choisi pour le matériel
/// @param shaderPath le chemin du répertoire des shaders
/// @param colorName le nom du paramètre uniforme de la couleur dans le fragment shader 
myColorMaterial::myColorMaterial( const QVector4D & col, const QString & shaderPath , char * colorName) {
    this->m_color = col;
    this->color_name = colorName;
    initShader(shaderPath);
}

void myColorMaterial::bindSpecific(const QGLCamera * c) {
    Q_UNUSED(c);
    //envoie la variable uniforme color dans le fragment shader
    m_program->setUniformValue(this->color_name, this->m_color);
}
