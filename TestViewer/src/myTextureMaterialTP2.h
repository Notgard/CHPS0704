#ifndef myTextureMaterialTP2TP2_H
#define myTextureMaterialTP2TP2_H

#include "Material.h"
#include "glTexture.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QString>

class myTextureMaterialTP2 : public Material
{
public:
    myTextureMaterialTP2( glTexture * texture);
    myTextureMaterialTP2( const QString & texturename);

    virtual void bindSpecific( const QGLCamera *c )  override;

private:
    glTexture            * m_texture;
    bool                   m_externTexture = false;
};

#endif // myTextureMaterialTP2TP2_H
