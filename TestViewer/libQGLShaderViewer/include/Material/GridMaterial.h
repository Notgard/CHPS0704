#ifndef GRIDMATERIAL_H
#define GRIDMATERIAL_H


//#include "glm/glm.hpp"
#include "Material.h"
#include "gltexture.h"

#include <QColor>



class DLL_SPEC GridMaterial : public Material
{
public:
    GridMaterial(int nbDivision = 10, const QColor &color = Qt::white, float widthLine = 0.05f );
    ~GridMaterial()  override;

    void bindSpecific(const QGLCamera *c) override;

private:
    glTexture            * m_texture = nullptr;
    bool                   m_externTexture = false;

    QColor                 m_colorLine;
    int                    m_nbDivision;
    float                  m_widthLine;

};

#endif // GRIDMATERIAL_H
