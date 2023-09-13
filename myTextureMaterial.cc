#include "myTextureMaterial.h"

myTextureMaterial::myTextureMaterial(const & QString textureName) {
	this->m_texture = new glTexture(textureName);
	this->m_exturnTexture = true;
}

myTextureMaterial::myTextureMaterial( glTexture * texture) {
	this->m_texture = texture;
}

void myTextureMaterial::bindSpecific( const QGLCamera *c ) {
	Q_UNUSED(c);
	glActiveTexture(GL_TEXTURE0);
	this->m_texture->bind();
	this->m_program->setUniformValue("maTexture", 0);
}