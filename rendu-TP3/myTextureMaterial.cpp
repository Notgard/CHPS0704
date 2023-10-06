#include "myTextureMaterial.h"

myTextureMaterial::myTextureMaterial(const QString & texturename) {
    initShader(QString("./data/myTextureMaterial/"));
    this->m_texture = new glTexture(texturename);
    this->m_externTexture = true;
}

myTextureMaterial::myTextureMaterial(FBO * framebuffer) {
    initShader(QString("./data/myTextureMaterial/"));
    this->m_fbuffer = framebuffer;
}

myTextureMaterial::myTextureMaterial( glTexture * texture) {
    initShader(QString("./data/myTextureMaterial/"));
    this->m_texture = texture;
}

void myTextureMaterial::bindSpecific( const QGLCamera *c ) {
    Q_UNUSED(c);

    this->gl->glActiveTexture(GL_TEXTURE0);
    this->gl->glBindTexture(GL_TEXTURE_2D, this->m_fbuffer->getGetexID());
    this->m_program->setUniformValue("myTexture", 0);
}
