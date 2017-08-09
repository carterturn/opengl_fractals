#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#include <GLFW/glfw3.h>
#include <GL/gl.h>

#define WIDTH 768
#define HEIGHT 768

using namespace std;

int main(int argc, char * argv[]){

		int max_depth = 2048;
		
		glfwInit();
		GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Logistic Bifurcation!", NULL, NULL);

		if(!window){
				return -1;
		}

		glfwMakeContextCurrent(window);
		glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0);

		while(true){
				glClear(GL_COLOR_BUFFER_BIT);
				glColor3f(0.0f, 1.0f, 0.0f);
				glBegin(GL_POINTS);
				chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

				for(int i = 0; i < WIDTH; i++){
						double r = 4.0 * double(i) / ((double) WIDTH);
						double x = 0.6;
						for(int d = 0; d < max_depth; d++){
								x = r * x * (1 - x);
								if(d >= max_depth * 0.95){
										glVertex2i(i, x * HEIGHT);
								}
						}
				}

				cout << chrono::duration_cast<chrono::duration<double>>
						(chrono::high_resolution_clock::now() - start).count() << "\n";
				glEnd();
				glfwSwapBuffers(window);
				this_thread::sleep_for(chrono::milliseconds(100));
		}

		return 0;
}
