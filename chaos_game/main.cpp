#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#include <GLFW/glfw3.h>
#include <GL/gl.h>

#define WIDTH 768
#define HEIGHT 768

using namespace std;

struct point{
		double x;
		double y;
};

int main(int argc, char * argv[]){

		int depth = 131072;
		if(argc > 1){
				depth = atoi(argv[1]);
		}
		
		glfwInit();
		GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Chaos Game!", NULL, NULL);

		if(!window){
				return -1;
		}

		glfwMakeContextCurrent(window);
		glOrtho(-WIDTH/2, WIDTH/2, 0, HEIGHT, -1.0, 1.0);

		int num_corners = 3;
		point corners[num_corners];
		corners[0].x = 0;
		corners[0].y = HEIGHT;
		corners[1].x = WIDTH/2;
		corners[1].y = 0;
		corners[2].x = -WIDTH/2;
		corners[2].y = 0;

		default_random_engine rand;
		uniform_real_distribution<double> height_dist(0.0, (double) HEIGHT);
		uniform_real_distribution<double> width_dist((double) -WIDTH/2.0, (double) WIDTH/2.0);
		uniform_int_distribution<int> corner_dist(0, num_corners-1);

		while(true){
				glClear(GL_COLOR_BUFFER_BIT);
				glBegin(GL_POINTS);
				chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
				point p;
				p.x = width_dist(rand);
				p.y = height_dist(rand);
				for(int i = 0; i < depth; i++){
						int corner = corner_dist(rand);
						p.x = p.x - (p.x - corners[corner].x) / 2.0;
						p.y = p.y - (p.y - corners[corner].y) / 2.0;

						if(i > 32){
								if(p.y > HEIGHT/2){
										glColor3f(0.0f, 1.0f, 0.0f);
								}
								else{
										if(p.x > 0){
												glColor3f(1.0f, 0.0f, 0.0f);
										}
										else{
												glColor3f(0.0f, 0.0f, 1.0f);
										}
								}
								glVertex2i(p.x, p.y);
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
