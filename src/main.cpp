#include "Core.h"
#include "Camera.h"
#include "Portal.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Module.h"
#include "Intersection.h"

bool initGL(int width=800, int height=600, bool fullscreen=false);
void cleanup();
void handleCamera(Camera * camera);

bool g_toggle;

int main()
{
	if(!initGL())
		return 1;

	Portal::init();

	Shader shader("res/shaders/portal_vert.glsl","res/shaders/portal_frag.glsl");
	shader.bind();

	f32 vCube[24] = {	-0.5, 0.5,-0.5,
						 0.5, 0.5,-0.5,
						-0.5,-0.5,-0.5,
						 0.5,-0.5,-0.5,
						-0.5, 0.5, 0.5,
						 0.5, 0.5, 0.5,
						-0.5,-0.5, 0.5,
						 0.5,-0.5, 0.5 };

	u32 iCube[36] = {	0,1,2,	//Front
						1,3,2,
						0,4,5,	//Top
						1,0,5,
						5,4,6,	//Back
						5,6,7,
						2,3,7,	//Bottom
						6,2,7,
						3,1,5,	//Right
						3,5,7,
						4,0,6,	//Left
						0,2,6};

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

	// MODULE A

	Model wallFrontA(&cube, &red);
	wallFrontA.setScale(vec3(10.0,2.0,1.0));
	wallFrontA.setPosition(vec3(0,0,-2.5));

	Model wallBackA(&cube, &blue);
	wallBackA.setScale(vec3(10.0,2.0,1.0));
	wallBackA.setPosition(vec3(0,0,2.5));

	Model wallLeftA(&cube, &green);
	wallLeftA.setScale(vec3(1.0,2.0,5.0));
	wallLeftA.setPosition(vec3(-5.0,0,0));

	Model wallRightA(&cube, &yellow);
	wallRightA.setScale(vec3(1.0,2.0,5.0));
	wallRightA.setPosition(vec3(5.0,0,0));

	Model floorModelA(&cube, &white);
	floorModelA.setScale(vec3(10,1,5));
	floorModelA.setPosition(vec3(0,-1.5,0));

	Model cubeModelA(&cube, &green);
	cubeModelA.setPosition(vec3(2,0,0));

	Portal portalA(1.5f, 2.0f);
	portalA.setPosition(vec3(-4.49,0,-1.0));
	portalA.rotateY(90.0f);

	Portal portalA2(1.5f, 2.0f);
	portalA2.setPosition(vec3(-4.49,0,1.0));
	portalA2.rotateY(90.0f);

	Module moduleA;

	moduleA.addGameObject(&wallFrontA);
	moduleA.addGameObject(&wallBackA);
	moduleA.addGameObject(&wallLeftA);
	moduleA.addGameObject(&wallRightA);
	moduleA.addGameObject(&floorModelA);
	moduleA.addGameObject(&cubeModelA);
	moduleA.addGameObject(&portalA);
	moduleA.addGameObject(&portalA2);

	// MODULE B

	Model wallFrontB(&cube, &white);
	wallFrontB.setScale(vec3(10.0,2.0,1.0));
	wallFrontB.setPosition(vec3(0,0,-2.5));

	Model wallBackB(&cube, &green);
	wallBackB.setScale(vec3(10.0,2.0,1.0));
	wallBackB.setPosition(vec3(0,0,2.5));

	Model wallLeftB(&cube, &red);
	wallLeftB.setScale(vec3(1.0,2.0,5.0));
	wallLeftB.setPosition(vec3(-5.0,0,0));

	Model wallRightB(&cube, &yellow);
	wallRightB.setScale(vec3(1.0,2.0,5.0));
	wallRightB.setPosition(vec3(5.0,0,0));

	Model floorModelB(&cube, &blue);
	floorModelB.setScale(vec3(10,1,5));
	floorModelB.setPosition(vec3(0,-1.5,0));

	Model cubeModelB(&cube, &yellow);
	cubeModelB.setPosition(vec3(2,0,0));

	Portal portalB(1.5f, 2.0f);
	portalB.setPosition(vec3(-4.49,0,1.0));
	portalB.rotateY(90.0f);

	Portal portalB2(1.5f, 2.0f);
	portalB2.setPosition(vec3(-4.49,0,-1.0));
	portalB2.rotateY(90.0f);

	Module moduleB;

	moduleB.addGameObject(&wallFrontB);
	moduleB.addGameObject(&wallBackB);
	moduleB.addGameObject(&wallLeftB);
	moduleB.addGameObject(&wallRightB);
	moduleB.addGameObject(&floorModelB);
	//moduleB.addGameObject(&cubeModelB);
	//moduleB.addGameObject(&portalB);
	moduleB.addGameObject(&portalB2);
	moduleB.addGameObject(&portalB);

	// Set targets
	portalA.setTargetPortal(&portalB);
	portalB.setTargetPortal(&portalA);
	portalB2.setTargetPortal(&portalA2);
	portalA2.setTargetPortal(&portalB2);

	Camera camera;
	camera.translate(vec3(0, 0, 0));
	camera.setupProjection(800,600);

	// Add camera to moduleA
	moduleB.addGameObject(&camera);

	vec4 v(0.5,0.5,-0.1,1);
	mat4 proj = glm::perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
	proj[2][2] = 1.0f;
	//proj[2][3] = 0.0f;
	proj[3][2] = 0.0f;
	//proj[3][3] = 1.0f;

	v = proj * v;
	v = v / v.w;
	printf("matrix : \n");
	for(int i=0; i<4; ++i)
	{
		printf("%f, %f, %f, %f \n", proj[0][i], proj[1][i], proj[2][i], proj[3][i]);
	}
	printf("vector! ( %f, %f, %f, %f ) \n", v.x, v.y, v.z, v.w);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glfwSwapInterval(1);

	while(true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		handleCamera(&camera);

		camera.render();
		
		glfwSwapBuffers();

		if(glfwGetKey(GLFW_KEY_ESC))
			break;
	}

	Portal::cleanup();
	cleanup();

	return 0;
}

void handleCamera(Camera * camera)
{
	vec3 oldCameraPos = camera->getPosition();

	vec3 move(glfwGetKey('D')-glfwGetKey('A'),0,glfwGetKey('S')-glfwGetKey('W'));
	move *= 0.1f;
	camera->move(move);

	vec3 newCameraPos = camera->getPosition();

	vec2 lookVec(	glfwGetKey(GLFW_KEY_LEFT)-glfwGetKey(GLFW_KEY_RIGHT),
					glfwGetKey(GLFW_KEY_UP)-glfwGetKey(GLFW_KEY_DOWN));
	camera->rotateY(lookVec.x * 2.0);

	// Handle portaling :)
	Module * currentModule = camera->getOwnerModule();
	std::vector<Portal*> portals = currentModule->getPortals();

	for(u32 i=0; i<portals.size(); ++i)
	{
		Portal * portal = portals[i];

		if( intersectLinePortal(oldCameraPos, newCameraPos, *portal) )
		{
			camera->getOwnerModule()->removeGameObject(camera);
			portal->getTargetPortal()->getOwnerModule()->addGameObject(camera);

			camera->setTransform(portal->getInvViewMatrix(camera));
		}
	}
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
						32, 8,
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