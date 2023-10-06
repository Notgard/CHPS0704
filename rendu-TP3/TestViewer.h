/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef TESTVIEWER_H
#define TESTVIEWER_H

#include "QGLShaderViewer.h"
#include "Mesh.h"
#include "FBO.h"
#include "myEffect.h"


/// ==============================================================
///    TestViewer
/// -------------------
///
///   Classe de test pour l'interface public de QGLShaderViewer
///   Demonstrastion basique de l'utilisation de la future lib
///
class TestViewer : public QGLShaderViewer
{
public:
    TestViewer();
    virtual ~TestViewer() override;

    virtual void  init               ()     override;
    virtual void  resizeGL(int width, int height) override;

    virtual void  createSceneEntities()     override;

    virtual void  animate            ()     override;
    virtual void  drawInformation    ()     override;
    virtual void  drawScene          ()     override;

    virtual void  keyPressEvent      (QKeyEvent * event)   override;


protected:
        QList<PointLight> m_lights;

// test pour mon 1er TP et faciliter les tests
        virtual void drawMono  ();
private:
        bool pause = false; //booléan pour effectuer la pause du rendu de la scène
        bool filter = false; //booléan pour effectuer le rendu de la scène dans le FBO avec les effets shaders
        bool phong_render = true; //booléan pour changer les objets dans la scène actuelle
        bool fbo_render = false; //booléan pour activer/désactiver le mode de rendu avec FBO
        Mesh * m_cube;
        FBO * m_framebuffer; //le Frame Buffer Object
        myEffect * m_effect; //l'instance de la classe myEffect pour faire les filtres avec le FBO
};

#endif // TESTVIEWER_H
