/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef GLTEXTURE_H
#define GLTEXTURE_H


#include <QOpenGLTexture>

#include "define.h"


// ==============================================================
//    glTexture
// -------------
//
// Classe représentant une texture chargée sur GPU
//
// Ses paramètres sont :
//  - filePath : nom du fichier contenant la texture
// soit
//  - texture  : une instance de glTexture.
//

/** 	Texture chargée sur GPU
 * @brief      Classe représentant une texture chargée sur GPU.
 *             To load a texture, passed the name of the texture in argument of the constructor.
	Ses paramètres sont :
 *     - filePath : nom du fichier contenant la texture
 * soit
 *     - texture  : une instance de glTexture.
 *
 * @class glTexture       glTexture.h
 * @author    S. Prévost & j. Gerhards
 * @version   1.0
 * @date      Septembre 2021
 *
 **/ 
class DLL_SPEC glTexture
{
public:
    glTexture ( const QString  & filePath );
    glTexture ( glTexture * texture );
    ~glTexture();

    void bind ();									//!< Bind the texture data


private:
   QOpenGLTexture * data;

};

#endif // GLTEXTURE_H
