#ifndef MYTEXTUREMATERIAL_H
#define MYTEXTUREMATERIAL_H

#include "Material.h"
#include "glTexture.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QString>

class myTextureMaterial : public Material
{
public:
    myTextureMaterial( glTexture * texture);
    myTextureMaterial( const QString & texturename);

    virtual void bindSpecific( const QGLCamera *c )  override;

private:
    glTexture            * m_texture;
    bool                   m_externTexture = false;
};

#endif // MYTEXTUREMATERIAL_H
