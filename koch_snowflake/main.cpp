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

		int max_depth = 1;
		if(argc > 1){
				max_depth = atoi(argv[1]);
		}
		
		glfwInit();
		GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Koch Snowflake!", NULL, NULL);

		if(!window){
				return -1;
		}

		glfwMakeContextCurrent(window);
		glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0);

		double side_length = (HEIGHT * 3.0/2.0) / sqrt(3.0);
		double width_offset = (WIDTH - side_length) / 2.0;

		while(true){
				glClear(GL_COLOR_BUFFER_BIT);
				glColor3f(0.0f, 1.0f, 0.0f);
				glBegin(GL_LINES);
				chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
				vector<point> points;

				points.push_back({.x = width_offset, .y = HEIGHT/4.0});
				points.push_back({.x = WIDTH - width_offset, .y = HEIGHT/4.0});
				points.push_back({.x = WIDTH/2, .y = HEIGHT});
				for(int d = 0; d < max_depth; d++){
						vector<point> new_points;
						for(int i = 0; i < points.size(); i++){
								double x1 = points[i].x;
								double x2 = points[(i+1)%points.size()].x;
								double y1 = points[i].y;
								double y2 = points[(i+1)%points.size()].y;
								double rx1 = (x2 - x1) / 3.0 + x1;
								double ry1 = (y2 - y1) / 3.0 + y1;
								double rx2 = 2.0 * (x2 - x1) / 3.0 + x1;
								double ry2 = 2.0 * (y2 - y1) / 3.0 + y1;
								new_points.push_back(points[i]);
								new_points.push_back({.x = rx1, .y = ry1});
								if(abs(ry1 - ry2) < 0.0000001){
										new_points.push_back({.x = (rx2 - rx1) / 2.0 + rx1,
																.y = ry1 + (rx1 - rx2) * sqrt(3.0) / 2.0});
								}
								else if((x2 > x1) == (y1 > y2)){
										new_points.push_back({.x = rx1 + (rx1 - rx2), .y = ry2});
								}
								else{
										new_points.push_back({.x = rx2 + (rx2 - rx1), .y = ry1});
								}
								new_points.push_back({.x = rx2, .y = ry2});
						}
						points = new_points;
				}
				glVertex2i(points[points.size()-1].x, points[points.size()-1].y);
				for(int i = 0; i < points.size(); i++){
						glVertex2i(points[i].x, points[i].y);
						glVertex2i(points[i].x, points[i].y);
				}
				glVertex2i(points[0].x, points[0].y);
				cout << chrono::duration_cast<chrono::duration<double>>
						(chrono::high_resolution_clock::now() - start).count() << "\n";
				glEnd();
				glfwSwapBuffers(window);
				this_thread::sleep_for(chrono::milliseconds(100));
		}

		return 0;
}
