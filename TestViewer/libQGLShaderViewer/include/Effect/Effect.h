#ifndef EFFECT_H
#define EFFECT_H

#include "ShaderTools.h"
#include "Geometry.h"
#include "fbo.h"
#include "gltexture.h"



// ==============================================================
//    Effect
// -------------
//
// Classe générique représentant un effet, basé sur un shader.
//
// Les shaders doivent être nommés de manière standard, à savoir vertex.txt, geometry.txt et fragment.txt. Leur nom correspond à la catégorie du shader.
// Le chemin où sont situés les shaders doit être donné au constructeur.
// Exploite le maillage :/3d/quad.obj
//
// Cette classe possède les méthodes facilitant
//   - la communication avec les shader chargés sur le GPU et leur exploitation.
//   - l'attachement des textures (cf. attachTexture)
//
// L'application de l'effet est réalisée via l'appel de la méthode apply.
//

/** Classe générique représentant un effet, basé sur un shader.
 * @brief Classe générique représentant un effet, basé sur un shader.
			- Les shaders doivent être nommés de manière standard, à savoir \c vertex.txt, \c geometry.txt et \c fragment.txt. Leur nom correspond à la catégorie du shader.
			- Le chemin où sont situés les shaders doit être donné au constructeur.
			- Exploite le maillage \c :/3d/quad.obj

		Cette classe possède les méthodes facilitant
		- la communication avec les shader chargés sur le GPU et leur exploitation.
		- l'attachement des textures (cf. attachTexture)

		L'application de l'effet est réalisée via l'appel de la méthode apply.
		
 * @class Effect		Effect.h
 * @author    S. Prévost & j. Gerhards 
 * @version   1.0
 * @date      Septembre 2021
 *
 **/
class DLL_SPEC Effect
{
public:
    Effect( const QString &shaderPath = ":/glsl/quad/" );
    virtual ~Effect();

	/** Apply the effect
		 @brief After binding the shader program, this method binds the quad on the location \c pos and calls Geometry::draw().
		GL_DEPTH_TEST is disable.
		This method is abstact and must be overriden in the children classes.
	 **/
    virtual void apply();

	/** Attach the texture
	 *  @brief Active the <em>GL_TEXTURE0 + \c num</em>  and attach the texture \c tex on the attribut named \c name in the shader.
	 */
    void attachTexture( int num, const char * name, glTexture * tex );
	
	/** Attach the texture
	 *  @brief Active the <em>GL_TEXTURE0 + \c num</em>  and attach the frame buffer object \c fbo on the attribut named \c name in the shader.
	 */
    void attachTexture( int num, const char * name, FBO * fbo );

	/** Attach the texture
	 *  @brief Active the <em>GL_TEXTURE0 + \c num</em>  and attach the frame buffer object \c fbo  on the attribut identified by \c location in the shader.
	 */
    void attachTexture( int num, int location,      FBO * fbo );

protected :
    Geometry             * m_geometry = nullptr;		//!< Quad Geometry

    QOpenGLShaderProgram * m_program;					//!< Shader program 
    QOpenGLFunctions     * gl;							//!< Access to OpenGL functions
    GLuint                 attribPos;					//!< id of Shader Attribut \c pos

};

#endif // EFFECT_H
