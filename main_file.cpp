  /*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/
#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdio.h>
#include <Camera.h>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myCube.h"
#include "Floor.h"
#include "Wall.h"
#include "Tigerbot.h"
#include "Tigermid.h"
#include "Tigertop.h"
#include "Eiffel.h"
#include "Pisa.h"


float speed_x = 0;
float aspectRatio=1;
float camera_speed = 0.05;
ShaderProgram *sp;
bool firstMouse = true;
Camera camera(glm::vec3(0.0f, 2.0f, -20.0f));
GLuint tex0, tex1, tex2, tex3, tex4, tex5,tex6,tex7,tex8,tex9,tex10,tex11;


float lastX;
float lastY;

/*static std::vector<Vertex> te;
te = loadOBJ("/tank/Tiger_I.obj");
*/


float kat(int radian) {

	return radian * PI / 180;
}

void draw(float ver[] , float nor[], float texture[], int count , GLint textur_num , glm::mat4 V , glm::mat4 P , glm::mat4 M , glm::vec3 pos) {

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
	//glUniform3f(sp->u("Camera_pos"), pos.x , pos.y , pos.z);
	glUniformMatrix3fv(sp->u("Camera_pos"),1,false, glm::value_ptr(pos));
	
	glEnableVertexAttribArray(sp->a("vertex")); 
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, ver); 

	glEnableVertexAttribArray(sp->a("normal"));  
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, nor); 

	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texture);
	glEnableVertexAttribArray(sp->a("texCoord0"));

	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textur_num);


	glDrawArrays(GL_TRIANGLES, 0, count); 

	glDisableVertexAttribArray(sp->a("vertex"));  
	glDisableVertexAttribArray(sp->a("normal"));  
	glDisableVertexAttribArray(sp->a("texCoord0"));

}




//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pamięci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}


void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {


	
    if (action==GLFW_PRESS) {
        if (key==GLFW_KEY_L) speed_x=- 0.1;
		if (key==GLFW_KEY_P) speed_x= 0.1;
		if (key == GLFW_KEY_SPACE) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    //    if (key==GLFW_KEY_UP) speed_y=PI/2;
    //    if (key==GLFW_KEY_DOWN) speed_y=-PI/2;
    }
    if (action==GLFW_RELEASE) {
        if (key==GLFW_KEY_L) speed_x=0;
        if (key==GLFW_KEY_P) speed_x=0;
		if (key == GLFW_KEY_SPACE) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //    if (key==GLFW_KEY_UP) speed_y=0;
    //    if (key==GLFW_KEY_DOWN) speed_y=0;
    }


	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, camera_speed);
	}
		
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, camera_speed);
	}
		
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, camera_speed);
	}
		
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, camera_speed);
	}
		
	camera.Position.y = 2.0f;

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}



void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height==0) return;
    aspectRatio=(float)width/(float)height;
	float lastX = (float)width /2;
	float lastY = (float)height/2;
    glViewport(0,0,width,height);
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window,keyCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	sp=new ShaderProgram("v_simplest.glsl",NULL,"f_simplest.glsl");
	tex0 = readTexture("./textures/PzVl_Tiger_I.png");
	tex1 = readTexture("./textures/PzVI_Tiger_I_track.png");
	tex2 = readTexture("./textures/Wood.png");
	tex3 = readTexture("./textures/wall3.png");
	tex4 = readTexture("./textures/wall2.png");
	tex5 = readTexture("./textures/Statue.png");
	tex6 = readTexture("./textures/Eiffel.png");
	tex7 = readTexture("./textures/obraz1.png");
	tex8 = readTexture("./textures/obraz2.png");
	tex9 = readTexture("./textures/obraz3.png");
	tex10 = readTexture("./textures/obraz4.png");
	tex11 = readTexture("./textures/pisa.png");
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************

    delete sp;
}




//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle) {
	

	//std::vector<Vertex> model = loadOBJ("Tiger_I.obj");
	

	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glm::mat4 V= camera.GetViewMatrix();
	glm::mat4 P = glm::perspective(glm::radians(camera.Zoom), aspectRatio, 0.01f, 50.0f);
	glm::mat4 M = glm::mat4(1.0f);

	
    sp->use();//Aktywacja programu cieniującego
  

	M = glm::scale(M, glm::vec3(4, 4, 4));
	draw(FloorVertex, FloorNormals, FloorTextures, FloorVertexCount, tex2, V, P, M , camera.Position);
	M = glm::rotate(M, kat(45), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 M2 = M;
	M = glm::scale(M, glm::vec3(0.5f, 1.0f, 1.0f));
	draw(WallVertex, WallNormals, WallTextures, WallVertexCount, tex3, V, P, M ,camera.Position);
	M = glm::rotate(M2, kat(90), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(0.5f, 1.0f, 1.0f));
	draw(WallVertex, WallNormals, WallTextures, WallVertexCount, tex4, V, P, M , camera.Position); 


	M = glm::mat4(1.0f);
	M = glm::rotate(M, kat(45), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(M, glm::vec3(7.0f, 0.0f, 7.0f));
	M = glm::rotate(M, kat(15), glm::vec3(0.0f, 1.0f, 0.0f));
	//M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
	//M = glm::scale(M, glm::vec3(0.01f, 0.01f, 0.01f));
	draw(TigerbotVertex,TigerbotNormals,TigerbotTextures,TigerbotVertexCount, tex1, V ,P ,M ,camera.Position);
	draw(TigermidVertex,TigermidNormals,TigermidTextures,TigermidVertexCount, tex0 , V  , P, M, camera.Position);
	M = glm::rotate(M, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	draw(TigertopVertex, TigertopNormals, TigertopTextures, TigertopVertexCount, tex0, V, P, M, camera.Position);



	M = glm::mat4(1.0f);
	M = glm::rotate(M, kat(45), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(M, glm::vec3(-7.0f, 0.0f, -7.0f));
	M = glm::scale(M, glm::vec3(2, 2, 2));
	draw(EiffelVertex, EiffelNormals, EiffelTextures, EiffelVertexCount, tex6, V, P, M, camera.Position);
	

	M = glm::mat4(1.0f);
	M = glm::rotate(M, kat(45), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(M, glm::vec3(-7.0f, 0.0f, 7.0f));
	M = glm::rotate(M,kat(15), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(0.3f, 0.3f, 0.3f));
	

	M = glm::mat4(1.0f);
	//M = glm::rotate(M, 1.57f / 2, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(M, glm::vec3(7.0f, 2.0f, -7.0f));
	M = glm::rotate(M,kat(45), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(1.0f, 1.0f, 0.4f));
	draw(myCubeVertices, myCubeVertexNormals, myCubeTexCoords, myCubeVertexCount, tex7, V, P, M, camera.Position);

	M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(4.0f, 3.0f, -4.0f));
	M = glm::rotate(M,kat(45), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(1.0f, 1.0f, 0.4f));
	draw(myCubeVertices, myCubeVertexNormals, myCubeTexCoords, myCubeVertexCount, tex8, V, P, M, camera.Position);

	M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(-3.0f, 3.0f, -3.0f));
	M = glm::rotate(M, -kat(45), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(1.0f, 1.0f, 0.4f));
	draw(myCubeVertices, myCubeVertexNormals, myCubeTexCoords, myCubeVertexCount, tex9, V, P, M, camera.Position);


	M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(-6.0f, 2.0f, -6.0f));
	M = glm::rotate(M, -kat(45), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(1.0f, 1.0f, 0.4f));
	draw(myCubeVertices, myCubeVertexNormals, myCubeTexCoords, myCubeVertexCount, tex10, V, P, M, camera.Position);

	M = glm::mat4(1.0f);
	draw(PisaVertex, PisaNormals, PisaTextures, PisaVertexCount, tex11, V, P, M, camera.Position);
	M = glm::rotate(M, kat(45), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(M, glm::vec3(-7.0f, 0.0f, 7.0f));
	M = glm::scale(M, glm::vec3(0.03f, 0.03f, 0.03f));
	draw(PisaVertex, PisaNormals, PisaTextures, PisaVertexCount, tex11, V, P, M, camera.Position);

    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni

}


int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	float angle_x=0; //Aktualny kąt obrotu obiektu
	//float angle_y=0; //Aktualny kąt obrotu obiektu
	glfwSetTime(0); //Zeruj timer
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
        angle_x+=speed_x*glfwGetTime(); //Zwiększ/zmniejsz kąt obrotu na podstawie prędkości i czasu jaki upłynał od poprzedniej klatki
        //angle_y+=speed_y*glfwGetTime(); //Zwiększ/zmniejsz kąt obrotu na podstawie prędkości i czasu jaki upłynał od poprzedniej klatki
        glfwSetTime(0); //Zeruj timer
		drawScene(window , angle_x); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
