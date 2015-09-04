#include "RenderingGeometryApp.h"

bool RenderingGeometryApp::StartUp()
{
	if (!glfwInit())
	{
		return false;
	}

	mWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

	if (nullptr == mWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(mWindow);


	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();
		return false;
	}

	//Gizmos::create();
	


	InitCamera();


	if (DEBUG_MODE)
	{
		int major = ogl_GetMajorVersion();
		int minor = ogl_GetMinorVersion();
		printf("GL: %i.%i\n", major, minor);
	}

	glClearColor(CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, CLEAR_COLOR.a);
	glEnable(GL_DEPTH_TEST);

	//init model transforms


	return true;
}


void RenderingGeometryApp::ShutDown()
{
	delete mCamera;
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

bool RenderingGeometryApp::Update()
{
	return true;
}

void RenderingGeometryApp::Draw()
{
	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

void RenderingGeometryApp::InitCamera()
{
	mCamera = new FlyCamera(mWindow);
	mCamera->SetSpeed(10.0f);
	mCamera->SetRotationSpeed(10.0f);
	mCamera->SetPerspective(CAMERA_FOV, (float)WINDOW_WIDTH / WINDOW_HEIGHT, CAMERA_NEAR, CAMERA_FAR);
	mCamera->SetLookAt(CAMERA_FROM, CAMERA_TO, CAMERA_UP);
}

void RenderingGeometryApp::GenerateGrid(uint rows, uint cols)
{
	Vertex* vertices = new Vertex[rows * cols];
	for (uint r = 0; r < rows; r++)
	{
		for (uint c = 0; c < cols; c++)
		{
			vertices[r * cols + c].position = vec4((float)c, 0, (float)r, 1);

			vec3 color = vec3(sinf((c / (float)(cols - 1))*(r / (float)(rows - 1))));

			vertices[r*cols + c].color = vec4(color, 1);
		}
	}

	uint* indeces = new uint[(rows - 1) * (cols - 1) * 6];
	uint index = 0;
	for (uint r = 0; r < (rows - 1); r++)
	{
		for (uint c = 0; c < (cols - 1); c++)
		{
			//triangle 1
			indeces[index++] = r*cols + c;
			indeces[index++] = (r + 1)*cols + c;
			indeces[index++] = (r + 1)*cols + (c + 1);

			//triangle 2
			indeces[index++] = r*cols + c;
			indeces[index++] = (r + 1)*cols + (c + 1);
			indeces[index++] = r*cols + (c + 1);
		}
	}

	//create and bind buffers to a VAO
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mIBO);
	glGenVertexArrays(1, &mVAO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1)*(cols - 1) * 6 * sizeof(uint), indeces, GL_STATIC_DRAW);
	

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	delete vertices;
}