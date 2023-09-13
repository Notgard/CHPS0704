#include "myColorMaterial.h"

myColorMaterial::myColorMaterial( const QVector4D & col, const QString & shaderPath , char * colorName) {
    this->m_color = col;
    this->color_name = colorName;
    initShader(shaderPath);
}

void myColorMaterial::bindSpecific(const QGLCamera * c) {
    Q_UNUSED(c);
    m_program->setUniformValue("color", this->m_color);
}
