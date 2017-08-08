#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#include <GLFW/glfw3.h>
#include <GL/gl.h>

#define WIDTH 768
#define HEIGHT 768

using namespace std;

int three_pow(int exp){
		int num = 1;

		for(int i = 0; i < exp; i++){
				num *= 3;
		}

		return num;
}

int main(int argc, char * argv[]){

		int max_depth = 5;
		
		glfwInit();
		GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Menger Sponge!", NULL, NULL);

		if(!window){
				return -1;
		}

		glfwMakeContextCurrent(window);
		glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0);

		while(true){
				glClear(GL_COLOR_BUFFER_BIT);
				glColor3f(0.0f, 1.0f, 0.0f);
				glBegin(GL_QUADS);
				chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
				for(int d = 0; d < max_depth; d++){
						double depth = (double) three_pow(d);
						for(int i = 0; i < depth; i++){
								double x_step = WIDTH / depth;
								for(int j = 0; j < depth; j++){
										double y_step = HEIGHT / depth;
										double center_x = x_step*double(i) + x_step/2.0;
										double center_y = y_step*double(j) + y_step/2.0;
										glVertex2i(center_x + x_step/6.0, center_y + y_step/6.0);
										glVertex2i(center_x + x_step/6.0, center_y - y_step/6.0);
										glVertex2i(center_x - x_step/6.0, center_y - y_step/6.0);
										glVertex2i(center_x - x_step/6.0, center_y + y_step/6.0);
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
