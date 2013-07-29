#include "Camera.h"
#include "Portal.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"

bool initGL(int width=800, int height=600, bool fullscreen=false);
void cleanup();
void controlCamera(Camera * camera);

int main()
{
	if(!initGL())
		return 1;

	Shader shader;
	shader.bind();

	f32 vData[12] = {   -1, 1, 0,
						 1, 1, 0,
						-1,-1, 0,
						 1,-1, 0 };

	u32 iData[6] = { 	0, 2, 1,
						1, 2, 3 };

	Mesh quad = Mesh(	"v3f",
						GL_STATIC_DRAW,
						12*sizeof(f32),
						vData,
						GL_UNSIGNED_INT,
						GL_STATIC_DRAW,
						GL_TRIANGLES,
						6*sizeof(u32),
						iData,
						6);

	f32 vCube[24] = {	-0.5, 0.5,-0.5,
						 0.5, 0.5,-0.5,
						-0.5,-0.5,-0.5,
						 0.5,-0.5,-0.5,
						-0.5, 0.5, 0.5,
						 0.5, 0.5, 0.5,
						-0.5,-0.5, 0.5,
						 0.5,-0.5, 0.5 };

	u32 iCube[36] = {	0,2,1,	//Front
						1,2,3,
						4,0,5,	//Top
						0,1,5,
						4,5,6,	//Back
						6,5,7,
						3,2,7,	//Bottom
						2,6,7,
						1,3,5,	//Right
						3,7,5,
						0,4,6,	//Left
						0,6,2};

	Mesh cube = Mesh(	"v3f",
						GL_STATIC_DRAW,
						24*sizeof(f32),
						vCube,
						GL_UNSIGNED_INT,
						GL_STATIC_DRAW,
						GL_TRIANGLES,
						36*sizeof(u32),
						iCube,
						36);

	Material red;
	red.setColor(vec3(1,0,0));

	Material green;
	green.setColor(vec3(0,1,0));

	Material blue;
	blue.setColor(vec3(0,0,1));

	Material white;
	white.setColor(vec3(1,1,1));

	Material yellow;
	yellow.setColor(vec3(1,1,0));

	Model wallFront(&cube, &red);
	wallFront.setScale(vec3(10.0,2.0,1.0));
	wallFront.setPosition(vec3(0,0,-2.5));

	Model wallBack(&cube, &blue);
	wallBack.setScale(vec3(10.0,2.0,1.0));
	wallBack.setPosition(vec3(0,0,2.5));

	Model wallLeft(&cube, &green);
	wallLeft.setScale(vec3(1.0,2.0,5.0));
	wallLeft.setPosition(vec3(-5.0,0,0));

	Model wallRight(&cube, &yellow);
	wallRight.setScale(vec3(1.0,2.0,5.0));
	wallRight.setPosition(vec3(5.0,0,0));

	Portal portal(1.0f, 2.0f);
	portal.setTargetPortal(&portal);

	Camera camera;
	camera.translate(vec3(0, 2, 5));
	camera.setupProjection(800,600);

	glEnable(GL_DEPTH_TEST);

	while(true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		controlCamera(&camera);
		camera.setup();

		//model.rotateY(0.1f);
		wallFront.draw();
		wallBack.draw();
		wallLeft.draw();
		wallRight.draw();

		glfwSwapBuffers();

		if(glfwGetKey(GLFW_KEY_ESC))
			break;
	}

	cleanup();

	return 0;
}

void controlCamera(Camera * camera)
{
	vec3 moveVec(glfwGetKey('D')-glfwGetKey('A'),0,glfwGetKey('S')-glfwGetKey('W'));
	moveVec *= 0.1f;
	camera->move(moveVec);

	vec2 lookVec(	glfwGetKey(GLFW_KEY_RIGHT)-glfwGetKey(GLFW_KEY_LEFT),
					glfwGetKey(GLFW_KEY_UP)-glfwGetKey(GLFW_KEY_DOWN));
	camera->rotateY(lookVec.x);
}

bool initGL(int width, int height, bool fullscreen)
{
	glfwInit();

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	int fs = fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW;

	if(!glfwOpenWindow(	width,
						height,
						8, 8, 8, 8,
						32, 0,
						fs))
	{
		printf("Could not create GLFW-window\n");
		return false;
	}

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Could not init GLEW\n");
		return false;
	}

	printf("Successfully created OpenGL-window, version %i.%i\n",
	        glfwGetWindowParam(GLFW_OPENGL_VERSION_MAJOR),
	        glfwGetWindowParam(GLFW_OPENGL_VERSION_MINOR));

	return true;
}

void cleanup()
{

}