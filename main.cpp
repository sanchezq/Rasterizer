#include "pch.h"
#include <iostream>
#include <vector>

#include "Rasterizer.h"
#include "Entity.h"
#include "Camera.h"

#include <GL/glew.h>
#include <GL/freeglut.h>


#include "Suth-Hodg.h"

#include <chrono>

#define _USE_MATH_DEFINES
#include "math.h"

using namespace std::chrono;

std::chrono::high_resolution_clock::time_point m_lastFrameTime;
Mat4 perspective = Rasterizer::CreatePerspectiveProjectionMatrix(5, 5, .1f, 10.f, 90.f);

bool isWireframe = false;
bool isBackface = true;


int count = 0;
bool rotatex = false;
bool rotatey = false;
bool rotatez = false;
float anglex = 0.1f;
float angley = 0.1f;
float anglez = 0.1f;

Camera cam;

struct Pixel
{
	Pixel() = default;

	Pixel(unsigned char r, unsigned char g, unsigned b, unsigned char a = 255) :
		m_red(r), m_green(g), m_blue(b), m_alpha(a)
	{}

	unsigned char m_red = 0;
	unsigned char m_green = 0;
	unsigned char m_blue = 0;
	unsigned char m_alpha = 255;
};


static GLuint	s_texture;

static std::vector<Pixel>	s_imagePixels;

static unsigned int s_width = 1024;
static unsigned int s_height = 768;

void InitGL(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// create a buffer of black RGBA pixels.
	s_imagePixels.resize((size_t)s_width * (size_t)s_height);

	// Enable textures
	glEnable(GL_TEXTURE_2D);

	// fill a texture with the pixel buffer
	glGenTextures(1, &s_texture);

	glBindTexture(GL_TEXTURE_2D, s_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, s_width, s_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, s_imagePixels.data());

	// Set up the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

}

void OnUpdate(int val)
{
	if (!glutGetWindow())
	{
		return;
	}

	high_resolution_clock::time_point now = high_resolution_clock::now();
	duration<float> deltaDuration = duration_cast<duration<float>>(now - m_lastFrameTime);
	m_lastFrameTime = now;
	float deltaTime = deltaDuration.count();

	float dt = 1 / deltaTime;
	count++;
	if ((dt < 1000) & (count >= 100))
	{
		count = 0;
		std::cout << dt << std::endl;
	}

	glutPostRedisplay();
	
	if (glutGetWindow())
	{
		glutTimerFunc(0, &OnUpdate, 0);
	}
}


void display(void)
{
	if (rotatex)
	{
		anglex += 1;
		if (anglex > 360)
		{
			anglex = 0;
		}
	}
	if (rotatey)
	{
		angley += 1;
		if (angley > 360)
		{
			angley = 0;
		}
	}
	if (rotatez)
	{
		anglez += 1;
		if (anglez > 360)
		{
			anglez = 0;
		}
	}


	if (Scene::GetInstance()->m_entities.size() > 0)
	{
		Scene::GetInstance()->m_entities[0].m_transformation = Scene::GetInstance()->m_entities[0].m_transformation.CreateTransformMatrix({ anglex, angley, anglez }, { 0, 0, -3.5f }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_normaleTransform = Scene::GetInstance()->m_entities[0].m_normaleTransform.CreateTransformMatrix({ anglex, angley, anglez }, { 0, 0, 0 }, { 1.f, 1.f, 1.f });
	}

	cam.m_transform = cam.m_transform.CreateTransformMatrix(cam.m_rotation, cam.m_position, { 1, 1, 1 });
	Rasterizer::GetInstance()->RendererScene(Scene::GetInstance(), Texture::GetInstance(), perspective, cam.m_transform.GetInverse(), isWireframe, isBackface, cam);

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_QUADS);

	glTexCoord2f(0.f, 1.f);
	glVertex2f(-1.f, 1.f);

	glTexCoord2f(1.f, 1.f);
	glVertex2f(1.f, 1.f);

	glTexCoord2f(1.f, 0.f);
	glVertex2f(1.f, -1.f);

	glTexCoord2f(0.f, 0.f);
	glVertex2f(-1.f, -1.f);

	glEnd();

	glutSwapBuffers();

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Texture::GetInstance()->GetWidth(), Texture::GetInstance()->GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, Texture::GetInstance()->GetPixels());

}


void reshape_window(GLsizei w, GLsizei h)
{
	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	s_width = w;
	s_height = h;

	glViewport(0, 0, s_width, s_height);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Resize the texture
	if (s_texture > 0)
	{
		// create a buffer of black RGBA pixels.
		s_imagePixels.resize((size_t)s_width * (size_t)s_height);
		for (auto& pixel : s_imagePixels)
		{
			pixel = Pixel(255, 0, 0);
		}

		glBindTexture(GL_TEXTURE_2D, s_texture);

		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, s_width, s_height, GL_RGBA, GL_UNSIGNED_BYTE, s_imagePixels.data());
	}

}

void Input(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE : 
		glutDestroyWindow(glutGetWindow());
		break;
	
	case 'w' :
		cam.m_position.m_z -= sin((-(cam.m_rotation.m_y) + 90) * ((float)M_PI / 180)) * 0.1f;
		cam.m_position.m_x += cos((-(cam.m_rotation.m_y) + 90) * ((float)M_PI / 180)) * 0.1f;
		break;

	case 's' :
		cam.m_position.m_z -= sin((-(cam.m_rotation.m_y) - 90) * ((float)M_PI / 180)) * 0.1f;
		cam.m_position.m_x += cos((-(cam.m_rotation.m_y) - 90) * ((float)M_PI / 180)) * 0.1f;
		break;

	case 'a' :
		cam.m_position.m_z += sin((-cam.m_rotation.m_y) * ((float)M_PI / 180)) * 0.1f;
		cam.m_position.m_x -= cos((-cam.m_rotation.m_y) * ((float)M_PI / 180)) * 0.1f;
		break;

	case 'd' :
		cam.m_position.m_z -= sin((-cam.m_rotation.m_y) * ((float)M_PI / 180)) * 0.1f;
		cam.m_position.m_x += cos((-cam.m_rotation.m_y) * ((float)M_PI / 180)) * 0.1f;
		break;

	case'x' :
		if (rotatex)
		{
			rotatex = false;
		}
		else
		{
			rotatex = true;
		}
		break;

	case'y':
		if (rotatey)
		{
			rotatey = false;
		}
		else
		{
			rotatey = true;
		}
		break;

	case'z':
		if (rotatez)
		{
			rotatez = false;
		}
		else
		{
			rotatez = true;
		}
		break;

	case '1':
	{
		glutLeaveMainLoop();

		Entity ent;
		Scene::GetInstance()->m_entities.clear();
		Scene::GetInstance()->m_entities.push_back(ent);
		Scene::GetInstance()->m_entities[0].m_transformation = Scene::GetInstance()->m_entities[0].m_transformation.CreateTransformMatrix({ anglex, angley, anglez }, { 0, 0, -3.5f }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_normaleTransform = Scene::GetInstance()->m_entities[0].m_normaleTransform.CreateTransformMatrix({ anglex, angley, anglez }, { 0, 0, 0 }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_alpha = 1.f;

		Vertex v8({ 0.f, 1.f, 0.f }, { 0, 0, 1 }, { 255, 0, 0, 255 });
		Vertex v9({ 1.f, -1.f, 0.f }, { 0, 0, 1 }, { 0, 255, 0, 255 });
		Vertex v10({ -1.f, -1.f, 0.f }, { 0, 0, 1 }, { 0, 0, 255, 255 });

		Mesh mesh;
		mesh.m_vertices.push_back(v8);
		mesh.m_vertices.push_back(v9);
		mesh.m_vertices.push_back(v10);
		mesh.m_indices.push_back(0);
		mesh.m_indices.push_back(2);
		mesh.m_indices.push_back(1);

		Scene::GetInstance()->m_entities[0].m_mesh = &mesh;
		glutMainLoop();
	}
	break;

	case '2':
	{
		glutLeaveMainLoop();

		Entity ent;
		Entity ent2;
		Scene::GetInstance()->m_entities.clear();
		Scene::GetInstance()->m_entities.push_back(ent);
		Scene::GetInstance()->m_entities.push_back(ent2);

		Scene::GetInstance()->m_entities[0].m_transformation = Scene::GetInstance()->m_entities[0].m_transformation.CreateTransformMatrix({ anglex, angley, anglez }, { 1, 0, -3.5f }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_normaleTransform = Scene::GetInstance()->m_entities[0].m_normaleTransform.CreateTransformMatrix({ anglex, angley, anglez }, { 0, 0, 0 }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_alpha = 1.f;


		Mesh mesh;
		mesh = mesh.CreateCube();
		Scene::GetInstance()->m_entities[0].m_mesh = &mesh;

		Scene::GetInstance()->m_entities[1].m_transformation = Scene::GetInstance()->m_entities[1].m_transformation.CreateTransformMatrix({ 0, 0, 0 }, { 1, 0, -4.5f }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_normaleTransform = Scene::GetInstance()->m_entities[0].m_normaleTransform.CreateTransformMatrix({ 0, 0, 0 }, { 0, 0, 0 }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[1].m_alpha = 1.f;

		Vertex v1({ 0.f, 1.f, 0.f }, { 0, 0, 1 }, { 255, 255, 255, 200 });
		Vertex v2({ 1.f, -1.f, 0.f }, { 0, 0, 1 }, { 255, 255, 255, 200 });
		Vertex v3({ -1.f, -1.f, 0.f }, { 0, 0, 1 }, { 255, 255, 255, 200 });

		Mesh mesh2;
		mesh2.m_vertices.push_back(v1);
		mesh2.m_vertices.push_back(v2);
		mesh2.m_vertices.push_back(v3);
		mesh2.m_indices.push_back(0);
		mesh2.m_indices.push_back(2);
		mesh2.m_indices.push_back(1);

		Scene::GetInstance()->m_entities[1].m_mesh = &mesh2;

		glutMainLoop();
	}
	break;

	case '3':
	{
		glutLeaveMainLoop();
		Entity ent;
		Mesh mesh3;

		glutLeaveMainLoop();

		Scene::GetInstance()->m_entities.clear();
		Scene::GetInstance()->m_entities.push_back(ent);

		Scene::GetInstance()->m_entities[0].m_transformation = Scene::GetInstance()->m_entities[0].m_transformation.CreateTransformMatrix({ anglex, angley, anglez }, { 0, 0, -3.5f }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_normaleTransform = Scene::GetInstance()->m_entities[0].m_normaleTransform.CreateTransformMatrix({ anglex, angley, anglez }, { 0, 0, 0 }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_alpha = 1.f;

		mesh3 = mesh3.CreateSphere(10, 10);
		Scene::GetInstance()->m_entities[0].m_mesh = &mesh3;

		glutMainLoop();
	}
	break;

	case '4':
	{
		glutLeaveMainLoop();

		Entity ent;
		Mesh mesh3;

		Scene::GetInstance()->m_entities.clear();
		Scene::GetInstance()->m_entities.push_back(ent);
		Scene::GetInstance()->m_entities[0].m_transformation = Scene::GetInstance()->m_entities[0].m_transformation.CreateTransformMatrix({ anglex, angley, anglez }, { 0, 0, -3.5f }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_normaleTransform = Scene::GetInstance()->m_entities[0].m_normaleTransform.CreateTransformMatrix({ anglex, angley, anglez }, { 0, 0, 0 }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_alpha = 1.f;

		const char* test = "Assets/quentin.png";
		Texture text(test);

		mesh3 = mesh3.CreateCube();
		mesh3.pTexture = &text;
		Scene::GetInstance()->m_entities[0].m_mesh = &mesh3;

		glutMainLoop();
	}
	break;

	case '5':
	{
		glutLeaveMainLoop();

		Entity ent;
		Entity ent2;
		Scene::GetInstance()->m_entities.clear();
		Scene::GetInstance()->m_entities.push_back(ent);
		Scene::GetInstance()->m_entities.push_back(ent2);

		Scene::GetInstance()->m_entities[0].m_transformation = Scene::GetInstance()->m_entities[0].m_transformation.CreateTransformMatrix({ 0, 0, 0 }, { 0, -1.f, -3.5f }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_transformation = Scene::GetInstance()->m_entities[0].m_transformation.CreateTransformMatrix({ anglex, angley, anglez }, { 0, 0, -3.5f }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_normaleTransform = Scene::GetInstance()->m_entities[0].m_normaleTransform.CreateTransformMatrix({ anglex, angley, anglez }, { 0, 0, 0 }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_alpha = 1.f;

		Vertex v8({ 0.f, 1.f, 0.f }, { 0, 0, 1 }, { 255, 0, 0, 255 });
		Vertex v9({ 1.f, -1.f, 0.f }, { 0, 0, 1 }, { 0, 255, 0, 255 });
		Vertex v10({ -1.f, -1.f, 0.f }, { 0, 0, 1 }, { 0, 0, 255, 255 });

		Mesh mesh;
		mesh.m_vertices.push_back(v8);
		mesh.m_vertices.push_back(v9);
		mesh.m_vertices.push_back(v10);
		mesh.m_indices.push_back(0);
		mesh.m_indices.push_back(2);
		mesh.m_indices.push_back(1);

		Scene::GetInstance()->m_entities[0].m_mesh = &mesh;
		Scene::GetInstance()->m_entities[1].m_transformation = Scene::GetInstance()->m_entities[1].m_transformation.CreateTransformMatrix({ 0, 0, 0 }, { 0, -1.f, -2.5f }, { 1.5f, 1.5f, 1.5f });
		Scene::GetInstance()->m_entities[1].m_transformation = Scene::GetInstance()->m_entities[1].m_transformation.CreateTransformMatrix({ 0, 0, 0 }, { 0, 0, -2.5f }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_normaleTransform = Scene::GetInstance()->m_entities[0].m_normaleTransform.CreateTransformMatrix({ 0, 0, 0 }, { 0, 0, 0 }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[1].m_alpha = 0.5f;

		Vertex v1({ 0.f, 1.5f, 0.f }, { 0, 0, 1 }, { 255, 255, 255, 200 });
		Vertex v2({ 1.5f, -1.5f, 0.f }, { 0, 0, 1 }, { 255, 255, 255, 200 });
		Vertex v3({ -1.5f, -1.5f, 0.f }, { 0, 0, 1 }, { 255, 255, 255, 200 });

		Mesh mesh2;
		mesh2.m_vertices.push_back(v1);
		mesh2.m_vertices.push_back(v2);
		mesh2.m_vertices.push_back(v3);
		mesh2.m_indices.push_back(0);
		mesh2.m_indices.push_back(2);
		mesh2.m_indices.push_back(1);

		Scene::GetInstance()->m_entities[1].m_mesh = &mesh2;

		glutMainLoop();
	}
	break;

	case '6':
	{
		glutLeaveMainLoop();

		Entity ent;
		Mesh mesh3;
		Scene::GetInstance()->m_entities.clear();
		Scene::GetInstance()->m_entities.push_back(ent);

		Scene::GetInstance()->m_entities[0].m_transformation = Scene::GetInstance()->m_entities[0].m_transformation.CreateTransformMatrix({ anglex + 90, angley, anglez }, { 0, 0, -3.5f }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_normaleTransform = Scene::GetInstance()->m_entities[0].m_normaleTransform.CreateTransformMatrix({ anglex, angley, anglez }, { 0, 0, 0 }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_alpha = 1.f;

		mesh3 = mesh3.CreateObject("Assets/groudon2.obj");
		Scene::GetInstance()->m_entities[0].m_mesh = &mesh3;

		glutMainLoop();
	}
	break;

	case '7' :
		{
			Scene::GetInstance()->m_lights.clear();
			Scene::GetInstance()->m_lights.push_back(Light({ 0, 0, 1 }, 0.2f, 0.4f, 0.4f));
		}
		break;

	case '8' :
		{
			Scene::GetInstance()->m_lights.clear();
			Scene::GetInstance()->m_lights.push_back(Light({ 0, 0, 1 }, 0.4f, 0.f, 0.f));
		}
	break;

	case '9':
	{
		Scene::GetInstance()->m_lights.clear();
	}
	break;

	case '0':
	{
		glutLeaveMainLoop();

		Entity ent;
		Mesh mesh3;

		Scene::GetInstance()->m_entities.clear();
		Scene::GetInstance()->m_entities.push_back(ent);
		Scene::GetInstance()->m_entities[0].m_transformation = Scene::GetInstance()->m_entities[0].m_transformation.CreateTransformMatrix({ 0, 90, 0 }, { 0, -1.f, -2.5f }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_normaleTransform = Scene::GetInstance()->m_entities[0].m_normaleTransform.CreateTransformMatrix({ anglex, angley, anglez }, { 0, 0, 0 }, { 1.f, 1.f, 1.f });
		Scene::GetInstance()->m_entities[0].m_alpha = 1.f;

		mesh3 = mesh3.CreateObject("Assets/groudon.obj");
		Scene::GetInstance()->m_entities[0].m_mesh = &mesh3;

		glutMainLoop();
	}
	break;
	
	default:
		break;



	}



}

void SpecialInput(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		if (isWireframe)
		{
			isWireframe = false;
		}
		else
		{
			isWireframe = true;
		}
	}
	if (key == GLUT_KEY_F2)
	{
		if (isBackface)
		{
			isBackface = false;
		}
		else
		{
			isBackface = true;
		}
	}
	else if (key == GLUT_KEY_UP)
	{
		cam.m_rotation.m_x += -1;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		cam.m_rotation.m_x += 1;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		cam.m_rotation.m_y += -1;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		cam.m_rotation.m_y += 1;
	}
}

int main(int argc, char **argv) {


	Rasterizer rasterizer;
	Scene scene;
	Texture texture(s_width, s_height);

	Scene::GetInstance()->m_lights.push_back(Light({ 0, 0, 1 }, 0.3f, 0.f, 0.f));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(s_width, s_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("rasterize me");

	glViewport(0, 0, s_width, s_height);        // Reset The Current Viewport

	InitGL();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape_window);

	glutKeyboardFunc(&Input);
	glutSpecialFunc(&SpecialInput);

	if (!glutGetWindow())
	{
		glutLeaveMainLoop();
		exit(0);
	}
	else
		glutTimerFunc(0, &OnUpdate, 0);
		glutMainLoop();
}