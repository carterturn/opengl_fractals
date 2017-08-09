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

		int max_depth = 6;
		if(argc > 1){
				max_depth = atoi(argv[1]);
		}
		
		glfwInit();
		GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Hilbert Curve!", NULL, NULL);

		if(!window){
				return -1;
		}

		glfwMakeContextCurrent(window);
		glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0);

		while(true){
				glClear(GL_COLOR_BUFFER_BIT);
				glColor3f(0.0f, 1.0f, 0.0f);
				glBegin(GL_LINES);
				chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
				
				vector<point> points;
				points.push_back({.x = WIDTH/4.0, .y = HEIGHT/4.0});
				points.push_back({.x = WIDTH/4.0, .y = HEIGHT*3.0/4.0});
				points.push_back({.x = WIDTH*3.0/4.0, .y = HEIGHT*3.0/4.0});
				points.push_back({.x = WIDTH*3.0/4.0, .y = HEIGHT/4.0});

				for(int d = 0; d < max_depth; d++){
						vector<point> new_points;

						for(int i = 0; i < points.size(); i += 4){
								if(abs(points[i+1].x - points[i].x) < abs(points[i+1].y - points[i].y)){
										double offset = (points[i+1].y - points[i].y) / 4.0;
										
										double x = points[i].x;
										double y = points[i].y;
										new_points.push_back({.x = x - offset, .y = y - offset});
										new_points.push_back({.x = x + offset, .y = y - offset});
										new_points.push_back({.x = x + offset, .y = y + offset});
										new_points.push_back({.x = x - offset, .y = y + offset});
										
										x = points[i+1].x;
										y = points[i+1].y;
										new_points.push_back({.x = x - offset, .y = y - offset});
										new_points.push_back({.x = x - offset, .y = y + offset});
										new_points.push_back({.x = x + offset, .y = y + offset});
										new_points.push_back({.x = x + offset, .y = y - offset});

										x = points[i+2].x;
										y = points[i+2].y;
										new_points.push_back({.x = x - offset, .y = y - offset});
										new_points.push_back({.x = x - offset, .y = y + offset});
										new_points.push_back({.x = x + offset, .y = y + offset});
										new_points.push_back({.x = x + offset, .y = y - offset});

										x = points[i+3].x;
										y = points[i+3].y;
										new_points.push_back({.x = x + offset, .y = y + offset});
										new_points.push_back({.x = x - offset, .y = y + offset});
										new_points.push_back({.x = x - offset, .y = y - offset});
										new_points.push_back({.x = x + offset, .y = y - offset});
								}
								else{
										double offset = (points[i+1].x - points[i].x) / 4.0;
										
										double x = points[i].x;
										double y = points[i].y;
										new_points.push_back({.x = x - offset, .y = y - offset});
										new_points.push_back({.x = x - offset, .y = y + offset});
										new_points.push_back({.x = x + offset, .y = y + offset});
										new_points.push_back({.x = x + offset, .y = y - offset});
										
										x = points[i+1].x;
										y = points[i+1].y;
										new_points.push_back({.x = x - offset, .y = y - offset});
										new_points.push_back({.x = x + offset, .y = y - offset});
										new_points.push_back({.x = x + offset, .y = y + offset});
										new_points.push_back({.x = x - offset, .y = y + offset});

										x = points[i+2].x;
										y = points[i+2].y;
										new_points.push_back({.x = x - offset, .y = y - offset});
										new_points.push_back({.x = x + offset, .y = y - offset});
										new_points.push_back({.x = x + offset, .y = y + offset});
										new_points.push_back({.x = x - offset, .y = y + offset});

										x = points[i+3].x;
										y = points[i+3].y;
										new_points.push_back({.x = x + offset, .y = y + offset});
										new_points.push_back({.x = x + offset, .y = y - offset});
										new_points.push_back({.x = x - offset, .y = y - offset});
										new_points.push_back({.x = x - offset, .y = y + offset});
								}
						}

						points = new_points;
				}
				glVertex2i(points[0].x, points[0].y);
				for(int i = 1; i < points.size() - 1; i++){
						glVertex2i(points[i].x, points[i].y);
						glVertex2i(points[i].x, points[i].y);
				}
				glVertex2i(points[points.size()-1].x, points[points.size()-1].y);

				cout << chrono::duration_cast<chrono::duration<double>>
						(chrono::high_resolution_clock::now() - start).count() << "\n";
				glEnd();
				glfwSwapBuffers(window);
				this_thread::sleep_for(chrono::milliseconds(100));
		}

		return 0;
}
