#include "myPhongMaterial.h"
#include "Mesh.h"

myPhongMaterial::myPhongMaterial( const QVector4D &ambient, const QVector4D &diffuse, const float &f ) {
    this->m_ambiant = ambient;
    this->m_diffuse = diffuse;
    this->m_specpower = f;
}

void myPhongMaterial::render(const Mesh * mesh, const QGLCamera *c, const QList<PointLight> & lights ) {
    this->gl->glEnable(GL_DEPTH_TEST);
    this->m_program->bind();

    this->bindSpecific(c);
    this->bindMatrix(c, mesh->getModelMatrix());

    this->m_program->setUniformValue("lightAmbiante", this->getAmbiant());
    this->m_program->setUniformValue("lightDiffuse", this->getDiffuse());
    this->m_program->setUniformValue("lightSpecPow", this->getSpecPower());

    this->m_program->setUniformValue("cameraPosition", c->getPosition());

    for(PointLight light : lights) {
        this->m_program->setUniformValue("lightDirection", light.getColor());
    }

    QVector3D normal;

    this->m_program->setUniformValue("cameraNormal", normal);

    mesh->getGeometry()->binds(this->attribPos, this->attribNorm, this->attribUvs, this->attribTangents);
    mesh->getGeometry()->draw();
    this->m_program->release();
}
