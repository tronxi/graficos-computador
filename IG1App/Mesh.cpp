#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaPoligonoRegular(GLuint num, GLdouble r)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_LINE_LOOP;

    mesh->mNumVertices = num;
    mesh->vVertices.reserve(mesh->mNumVertices);
    GLdouble ang = 90.0;

    for (int i = 0; i < mesh->mNumVertices; i++) {
        GLdouble x = 0 + r * cos(radians(ang));
        GLdouble y = 0 + r * sin(radians(ang));
        ang += 360.0 / mesh->mNumVertices;
        mesh->vVertices.emplace_back(x, y, 0);

    }
    return mesh;
}

Mesh* Mesh::generaTrianguloRGB(GLdouble r)
{
    Mesh* mesh = generaPoligonoRegular(3, r);
    mesh->mPrimitive = GL_TRIANGLES;
    mesh->vColors.reserve(3);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    return mesh;
}

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);
    GLdouble x = w / 2;
    GLdouble y = h / 2;
    mesh->vVertices.push_back({ -x, y, 0.0 });
    mesh->vVertices.push_back({ -x, -y, 0.0 });
    mesh->vVertices.push_back({ x, y, 0.0 });
    mesh->vVertices.push_back({ x, -y, 0.0 });

    return mesh;
}

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
    Mesh* mesh = generaRectangulo(w, h);

    mesh->vColors.reserve(mesh->mNumVertices);

    mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 1.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 0.0, 1.0, 1.0 });
    mesh->vColors.push_back({ 0.5, 0.5, 0.5, 1.0 });

    return mesh;
}

/*Mesh* Mesh::generaCubo(GLdouble longitud)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 14;
    mesh->vVertices.reserve(mesh->mNumVertices);

    GLdouble size = longitud / 2;

    mesh->vVertices.push_back({ size, size, -size });
    mesh->vVertices.push_back({ -size, size, -size });
    mesh->vVertices.push_back({ size, -size, -size });
    mesh->vVertices.push_back({ -size, -size, -size });
    mesh->vVertices.push_back({ -size, -size, size });
    mesh->vVertices.push_back({ -size, size, -size });
    mesh->vVertices.push_back({ -size, size, size });
    mesh->vVertices.push_back({ size, size, -size });
    mesh->vVertices.push_back({ size, size, size });
    mesh->vVertices.push_back({ size, -size, -size });
    mesh->vVertices.push_back({ size, -size, size });
    mesh->vVertices.push_back({ -size, -size, size });
    mesh->vVertices.push_back({ size, size, size });
    mesh->vVertices.push_back({ -size, size, size });


    return mesh;
}*/

Mesh* Mesh::generaCubo(GLdouble longitud)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLES;

    mesh->mNumVertices = 36;
    mesh->vVertices.reserve(mesh->mNumVertices);

    GLdouble size = longitud / 2;
    //FRONT
    mesh->vVertices.push_back({ 0, size, size });
    mesh->vVertices.push_back({ 0, 0, size });
    mesh->vVertices.push_back({ size, size, size });
    mesh->vVertices.push_back({ size, size, size });
    mesh->vVertices.push_back({ 0, 0, size });
    mesh->vVertices.push_back({ size, 0, size });

    //BACK
    mesh->vVertices.push_back({ 0, size, 0 });
    mesh->vVertices.push_back({ 0, 0, 0 });
    mesh->vVertices.push_back({ size, size, 0 });
    mesh->vVertices.push_back({ size, size, 0 });
    mesh->vVertices.push_back({ 0, 0, 0 });
    mesh->vVertices.push_back({ size, 0, 0 });

    //UP
    mesh->vVertices.push_back({ 0, size, 0 });
    mesh->vVertices.push_back({ 0, size, size });
    mesh->vVertices.push_back({ size, size, size });
    mesh->vVertices.push_back({ 0, size, 0 });
    mesh->vVertices.push_back({ size, size, size });
    mesh->vVertices.push_back({ size, size, 0 });

    //DOWN
    mesh->vVertices.push_back({ 0, 0, 0 });
    mesh->vVertices.push_back({ 0, 0, size });
    mesh->vVertices.push_back({ size, 0, size });
    mesh->vVertices.push_back({ 0, 0, 0 });
    mesh->vVertices.push_back({ size, 0, size });
    mesh->vVertices.push_back({ size, 0, 0 });

    //LEFT
    mesh->vVertices.push_back({ 0, size, 0 });
    mesh->vVertices.push_back({ 0, size, size });
    mesh->vVertices.push_back({ 0, 0, 0 });
    mesh->vVertices.push_back({ 0, 0, 0 });
    mesh->vVertices.push_back({ 0, size, size });
    mesh->vVertices.push_back({ 0, 0, size });


    //RIGHT
    mesh->vVertices.push_back({ size, size, 0 });
    mesh->vVertices.push_back({ size, size, size });
    mesh->vVertices.push_back({ size, 0, 0 });
    mesh->vVertices.push_back({ size, 0, 0 });
    mesh->vVertices.push_back({ size, size, size });
    mesh->vVertices.push_back({ size, 0, size });

    return mesh;
}



Mesh* Mesh::generaCuboTriangulosRGB(GLdouble longitud)
{
    Mesh* mesh = generaCubo(longitud);
    mesh->mPrimitive = GL_TRIANGLES;
    mesh->vColors.reserve(mesh->mNumVertices);
    //FRONT
    mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });

    //BACK
    mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });
    //up
    mesh->vColors.push_back({ 0.0, 0.0, 1.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 0.0, 1.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 0.0, 1.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 0.0, 1.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 0.0, 1.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 0.0, 1.0, 1.0 });
    //down
    mesh->vColors.push_back({ 0.0, 0.0, 1.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 0.0, 1.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 0.0, 1.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 0.0, 1.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 0.0, 1.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 0.0, 1.0, 1.0 });
    //left
    mesh->vColors.push_back({ 0.0, 1.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 1.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 1.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 1.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 1.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 1.0, 0.0, 1.0 });
    //right
    mesh->vColors.push_back({ 0.0, 1.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 1.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 1.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 1.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 1.0, 0.0, 1.0 });
    mesh->vColors.push_back({ 0.0, 1.0, 0.0, 1.0 });
    return mesh;
}
