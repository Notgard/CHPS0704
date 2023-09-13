#include "myTextureMaterial.h"

myTextureMaterial::myTextureMaterial(const QString & texturename) {
    initShader(QString("./data/myTextureMaterial/"));
    this->m_texture = new glTexture(texturename);
    this->m_externTexture = true;
}

myTextureMaterial::myTextureMaterial( glTexture * texture) {
    this->m_texture = texture;
}

void myTextureMaterial::bindSpecific( const QGLCamera *c ) {
    Q_UNUSED(c);
    this->gl->glActiveTexture(GL_TEXTURE0);
    this->m_texture->bind();
    this->m_program->setUniformValue("myTexture", 0);
}
