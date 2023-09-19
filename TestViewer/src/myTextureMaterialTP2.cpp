#include "myTextureMaterialTP2.h"

myTextureMaterialTP2::myTextureMaterialTP2(const QString & texturename) {
    initShader(QString("./data/myTextureMaterialTP2/"));
    this->m_texture = new glTexture(texturename);
    this->m_externTexture = true;
}

myTextureMaterialTP2::myTextureMaterialTP2( glTexture * texture) {
    this->m_texture = texture;
}

void myTextureMaterialTP2::bindSpecific( const QGLCamera *c ) {
    Q_UNUSED(c);

    this->gl->glActiveTexture(GL_TEXTURE0);
    this->m_texture->bind();
    this->m_program->setUniformValue("myTexture", 0);
}
