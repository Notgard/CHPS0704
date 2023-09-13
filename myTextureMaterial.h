#ifndef TEXTUREMAT_H
#define TEXTUREMAT_H

#include "Material.h"
#include "glTexture.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QString>

class DLL_SPEC  TextureMaterial : public Material
{
public:
    TextureMaterial( const QString & texturename);
    TextureMaterial( glTexture * texture);

    ~TextureMaterial()  override;

    virtual void bindSpecific( const QGLCamera *c )  override;

private:
    glTexture            * m_texture;
    bool                   m_externTexture = false;
};

#endif
