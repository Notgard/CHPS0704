#ifndef MYEFFECT_H
#define MYEFFECT_H

#include "Effect.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QColor>
#include "QString"

class myEffect : public Effect {
public:

    myEffect( const QString & shaderPath = "./data/myEffect/" );
    virtual ~myEffect();

    void render(int channel, char * buffer_name, FBO * frameBuffer);
    void setFilter(bool filterOn);

private:
    QString m_shaderPath;
};

#endif // MYEFFECT_H
