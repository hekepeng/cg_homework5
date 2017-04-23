/*#include<math.h>
#include<time.h>
#include<iostream>
#include<GL/freeglut.h>  

using namespace std;

// 将立方体的八个顶点保存到一个数组里面   
static const float vertex_list[][3] =
{
	-0.05f, -0.05f, -0.05f,
	0.05f, -0.05f, -0.05f,
	-0.05f, 0.05f, -0.05f,
	0.05f, 0.05f, -0.05f,
	-0.05f, -0.05f, 0.05f,
	0.05f, -0.05f, 0.05f,
	-0.05f, 0.05f, 0.05f,
	0.05f, 0.05f, 0.05f,
};

// 将要使用的顶点的序号保存到一个数组里面   
static const GLint index_list[][4] =
{
	{ 0, 1, 5, 4 },
	{ 2, 6, 7, 3 },
	{ 0, 4, 6, 2 },
	{ 1, 5, 7, 3 },
	{ 0, 2, 3, 1 },
	{ 4, 6, 7, 5 }
};

//设置每个面的颜色
static const float color_list[][3] = {
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f },
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 1.0f },
};

//初始化
void init() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

// 绘制立方体  
void DrawCube(void)
{
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			glColor3f(color_list[i][0], color_list[i][1], color_list[i][2]);
			glVertex3fv(vertex_list[index_list[i][j]]);
		}
	}
	glEnd();
}
float camPosX, camPosZ;
float Radius = 3.0;
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//2.2.1 orthographic projection
	//glOrtho(0.4, 0.6, -0.6, -0.4, -1.5, 1.5);
	//glOrtho(1.5, -1.5, 1.5, -1.5, -1.5, 1.5);
	//2.2.2 perspective projection
	gluPerspective(30, 1.0, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(3.0 ,3.0 ,3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//glTranslatef(0.5, -0.5, -1.5);

	//2.3 View Changing
	camPosX = sin(clock() / 1000.0)*Radius;
	camPosZ = cos(clock() / 1000.0)*Radius;
	gluLookAt(camPosX, Radius, camPosZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	DrawCube();
	glutSwapBuffers();
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("CUBE");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
}*/

#include<math.h>
#include<time.h>
#include<iostream>
#include<GL/freeglut.h>  

using namespace std;

const float PI = 3.14159265358979323846;
GLfloat length = 0.02f;
static float c = PI / 180.0f; //弧度和角度转换参数  
static int du = 90; //du是视点绕y轴的角度,opengl里默认y轴是上方向  
static float r = 1.5f, h = 0.0f; //r是视点绕y轴的半径,h是视点高度即在y轴上的坐标

class Camera {
public:
	Camera()
	{
		cameraPosX = 0.0f; cameraPosY = 1.0f; cameraPosZ = 3.0f;
		cameraUpX = 0; cameraUpY = 1.0; cameraUpZ = 0;
		cameraFrontX = 0.0f; cameraFrontY = 0.0f, cameraFrontZ = 0.0f;
		cameraRightX = 0.0f; cameraRightY = 0.0f; cameraRightZ = 0.0;
		_pitch = _yaw = 0.0f;
	}
	void moveForward(GLfloat const distance) {
		//cameraPosX += distance;
		//cameraPosY += distance;
		cameraPosZ -= distance;
		cameraFrontZ -= distance;
	}
	void moveBack(GLfloat const distance) {
		//cameraPosX += distance;
		//cameraPosY += distance;
		cameraPosZ += distance;
		cameraFrontZ += distance;
	}
	void moveRight(GLfloat const distance) {
		cameraPosX += distance;
		cameraFrontX += distance;
		//cameraPosY += distance;
		//cameraPosZ += distance;
	}
	void moveLeft(GLfloat const distance) {
		cameraPosX -= distance;
		cameraFrontX -= distance;
		//cameraPosY += distance;
		//cameraPosZ += distance;
	}
	void rotate(GLfloat const pitch, GLfloat const yaw) {
		_pitch += pitch;
		_yaw += yaw;
		cameraFrontX += -sin(_yaw)*cos(_pitch);
		cameraFrontY += sin(_pitch);
		cameraFrontZ += -cos(_yaw)*cos(_pitch);
		if (cameraFrontY > 1.0)
			cameraFrontY = 1.0;
		else if (cameraFrontY < -1.0)
			cameraFrontY = -1.0;
		GLfloat sum = sqrt(pow(cameraFrontX, 2) + pow(cameraFrontY, 2) + pow(cameraFrontZ, 2));
		cameraFrontX /= sum;
		cameraFrontY /= sum;
		cameraFrontZ /= sum;
		cameraRightX = cos(_yaw);
		cameraRightY = 0;
		cameraRightZ = -sin(_yaw);
		sum = sqrt(pow(cameraRightX, 2) + pow(cameraRightY, 2) + pow(cameraRightZ, 2));
		cameraRightX /= sum;
		cameraRightY /= sum;
		cameraRightY /= sum;
	}

	GLfloat pfov, pratio, pnear, pfar;
	GLfloat cameraPosX, cameraPosY, cameraPosZ;
	GLfloat cameraFrontX, cameraFrontY, cameraFrontZ;
	GLfloat cameraRightX, cameraRightY, cameraRightZ;
	GLfloat cameraUpX, cameraUpY, cameraUpZ;
	float mouse_x, mouse_y;
	GLfloat _pitch, _yaw;
};

Camera cam;
// 将立方体的八个顶点保存到一个数组里面   
static const float vertex_list[][3] ={
	-0.05f, -0.05f, -0.05f,
	0.05f, -0.05f, -0.05f,
	-0.05f, 0.05f, -0.05f,
	0.05f, 0.05f, -0.05f,
	-0.05f, -0.05f, 0.05f,
	0.05f, -0.05f, 0.05f,
	-0.05f, 0.05f, 0.05f,
	0.05f, 0.05f, 0.05f,
};

// 将要使用的顶点的序号保存到一个数组里面   
static const GLint index_list[][4] ={
	{ 0, 1, 5, 4 },
	{ 2, 6, 7, 3 },
	{ 0, 4, 6, 2 },
	{ 1, 5, 7, 3 },
	{ 0, 2, 3, 1 },
	{ 4, 6, 7, 5 }
};

//设置每个面的颜色
static const float color_list[][3] = {
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f },
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 1.0f },
};

//初始化
void init() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

// 绘制立方体  
void DrawCube(void)
{
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			glColor3f(color_list[i][0], color_list[i][1], color_list[i][2]);
			glVertex3fv(vertex_list[index_list[i][j]]);
		}
	}
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, 1.0, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.cameraPosX, cam.cameraPosY, cam.cameraPosZ,
		cam.cameraFrontX, cam.cameraFrontY, cam.cameraFrontZ,
		cam.cameraUpX, cam.cameraUpY, cam.cameraUpZ);
	//gluLookAt(cam.cameraPosX, cam.cameraPosY, cam.cameraPosZ, cam.cameraPosX + cam.cameraFrontX, cam.cameraPosY + cam.cameraFrontY, cam.cameraPosZ + cam.cameraFrontZ, cam.cameraUpX, cam.cameraUpY, cam.cameraUpZ);
	glPushMatrix();
	DrawCube();
	glPopMatrix();
	//DrawCube();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	{
		cam.moveForward(length);
		break;
	}
	case 'a':
	{
		cam.moveLeft(length);
		break;
	}
	case 's':
	{
		cam.moveBack(length);
		break;
	}
	case 'd':
	{
		cam.moveRight(length);
		break;
	}
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y) //处理鼠标点击  
{
	if (state == GLUT_DOWN) //第一次鼠标按下时,记录鼠标在窗口中的初始坐标  
		cam.mouse_x = x, cam.mouse_y = y;
}
void mousemove(int x, int y) //处理鼠标拖动  
{
	GLfloat pitch, yaw;
	yaw = (cam.mouse_x - x)*c;
	pitch = (cam.mouse_y - y)*c;
	cam.rotate(pitch, yaw);
	cam.mouse_x = x;
	cam.mouse_y = y;
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("CUBE");
	glutPostRedisplay();
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemove);
	glutIdleFunc(display);
	glutMainLoop();
}