#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


class drawObjects
{
private:
	/*void triangle();
	void wheel(int lod);
	void grid(float xSize, float zSize);*/

public:

	void triangle()
	{
		glBegin(GL_TRIANGLES);
		glColor3ub(255, 0, 0);
		glVertex3f(0, 0, 0);

		glColor3ub(0, 255, 0);
		glVertex3f(1, 0, 0);

		glColor3ub(0, 0, 255);
		glVertex3f(0.5, 1, 0);
		glEnd();

	}

	void wheel(int lod)
	{

		glBegin(GL_POLYGON);

		glVertex3f(0, 0, 0);

		for (int i = 0; i <= lod; i++)
		{
			glVertex3f(cos((i * 360 / (float)lod) * 3.14 / 180.0), sin((i * 360 / (float)lod) * 3.14 / 180.0), 0);
		}

		glEnd();

	}

	void grid(float xSize, float zSize)
	{
		glColor3ub(255, 255, 255);
		glLineWidth(1);

		glBegin(GL_LINES);
		for (int i = -zSize / 2.0; i <= zSize / 2.0; i++) {
			glVertex3f(-xSize / 2.0, 0, i);
			glVertex3f(xSize / 2.0, 0, i);
		}

		for (int i = -xSize / 2.0; i <= xSize / 2.0; i++) {
			glVertex3f(i, 0, -zSize / 2.0);
			glVertex3f(i, 0, zSize / 2.0);
		}

		glEnd();

		glLineWidth(2);

		glBegin(GL_LINES);
		glColor3ub(255, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);

		glColor3ub(0, 255, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);

		glColor3ub(0, 0, 255);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1);
		glEnd();

		glColor3ub(255, 255, 255);


	}

};

