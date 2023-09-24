/*#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include "myLib.h"

//--------------------------------------------My shaders--------------------------
shader::shader() :ID(0) {}
shader::shader(const char* vertexShaderSource, const char* fragmentShaderSource) {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
void shader::activateS() {
    glUseProgram(ID);
}
void shader::deleteS() {
    glDeleteProgram(ID);
}
//--------------------------------------------My shaders--------------------------

//-----------------CLASE Transformaciones-------------------------------------------------------------
Mtransformaciones::Mtransformaciones() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rot_x[i][j] = 0;
            rot_y[i][j] = 0;
            rot_z[i][j] = 0;
            T[i][j] = 0;
            S[i][j] = 0;
        }
    }
    res = new float[3];
    for (int i = 0; i < 3; i++) {
        temp[i] = 0;
        res[i] = 0;
    }
}

float* Mtransformaciones::multiplicacion(float matriz1[3], float matriz2[4][4], bool vector) {
    float temp[4][1];
    float new_matriz1[4][1];
    for (int i = 0; i < 3; i++) {
        new_matriz1[i][0] = matriz1[i];
        for (int j = 0; j < 1; j++) {
            temp[i][j] = 0;
        }
    }
    !vector ? new_matriz1[3][0] = 0 : new_matriz1[3][0] = 1;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 1; j++) {
            for (int k = 0; k < 4; k++) {
                temp[i][j] += matriz2[i][k] * new_matriz1[k][j];
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        matriz1[i] = temp[i][0];
    }

    return matriz1;
}

float** Mtransformaciones::multiplicacion2(float matriz1[4][4], float matriz2[4][4]) {
    float **temp=new float*[4];
    for (int i = 0; i < 4; i++) {
        temp[i] = new float[4];
        for (int j = 0; j < 4; j++) {
            temp[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                temp[i][j] += matriz2[i][k] * matriz1[k][j];
            }
        }
    }

    return temp;
}

void Mtransformaciones::changing_vectors(float*& vertices, int size, float matriz[4][4], bool vector) {
    for (int i = 0; i < size; i += 3) {
        temp[0] = vertices[i];
        temp[1] = vertices[i + 1];
        temp[2] = vertices[i + 2];
        res = multiplicacion(temp, matriz, vector);
        vertices[i] = res[0];
        vertices[i + 1] = res[1];
        vertices[i + 2] = res[2];
    }
}

//Rotacion en x
void Mtransformaciones::Rotacion_x(float angle, float*& vertices, int size) {
    //Convertimos a grados
    float degree = angle * (3.141592653589793238463 / 180);
    //Construimos la matrix rotacion_x con el angulo 
    rot_x[0][0] = 1;
    rot_x[1][1] = cos(degree); rot_x[1][2] = -sin(degree);
    rot_x[2][1] = sin(degree); rot_x[2][2] = cos(degree);
    //Multiplicamos por todos los vectores recibidos y actualizamos nuestra matriz
    changing_vectors(vertices, size, rot_x, 0);
}

void Mtransformaciones::Rotacion_xINV(float angle, float*& vertices, int size) {
    //Convertimos a grados
    float degree = angle * (3.141592653589793238463 / 180);
    //Construimos la matrix rotacion_x con el angulo 
    rot_x[0][0] = 1;
    rot_x[1][1] = cos(degree); rot_x[2][1] = -sin(degree);
    rot_x[1][2] = sin(degree); rot_x[2][2] = cos(degree);
    //Multiplicamos por todos los vectores recibidos y actualizamos nuestra matriz
    changing_vectors(vertices, size, rot_x, 0);
}

void Mtransformaciones::Rotacion_y(float angle, float*& vertices, int size) {
    float degree = angle * (3.141592653589793238463 / 180);
    rot_y[0][0] = cos(degree); rot_y[0][2] = sin(degree);
    rot_y[1][1] = 1;
    rot_y[2][0] = -sin(degree); rot_y[2][2] = cos(degree);
    changing_vectors(vertices, size, rot_y, 0);
}

void Mtransformaciones::Rotacion_yINV(float angle, float*& vertices, int size) {
    //Convertimos a grados
    float degree = angle * (3.141592653589793238463 / 180);
    //Construimos la matrix rotacion_x con el angulo 
    rot_y[0][0] = cos(degree); rot_y[2][0] = sin(degree);
    rot_y[1][1] = 1;
    rot_y[0][2] = -sin(degree); rot_y[2][2] = cos(degree);
    //Multiplicamos por todos los vectores recibidos y actualizamos nuestra matriz
    changing_vectors(vertices, size, rot_y, 0);
}

void Mtransformaciones::Rotacion_z(float angle, float*& vertices, int size) {
    float degree = angle * (3.141592653589793238463 / 180);
    rot_z[0][0] = cos(degree); rot_z[0][1] = -sin(degree);
    rot_z[1][0] = sin(degree); rot_z[1][1] = cos(degree);
    rot_z[2][2] = 1;
    changing_vectors(vertices, size, rot_z, 0);
}

void Mtransformaciones::Rotacion_zINV(float angle, float*& vertices, int size) {
    //Convertimos a grados
    float degree = angle * (3.141592653589793238463 / 180);
    //Construimos la matrix rotacion_x con el angulo 
    rot_z[0][0] = cos(degree); rot_z[1][0] = -sin(degree);
    rot_z[0][1] = sin(degree); rot_z[1][1] = cos(degree);
    rot_z[2][2] = 1;
    //Multiplicamos por todos los vectores recibidos y actualizamos nuestra matriz
    changing_vectors(vertices, size, rot_z, 0);
}

void Mtransformaciones::Translation(float tx, float ty, float tz, float*& vertices, int size) {
    T[0][0] = 1; T[0][3] = tx;
    T[1][1] = 1; T[1][3] = ty;
    T[2][2] = 1; T[2][3] = tz;
    changing_vectors(vertices, size, T, 1);
}

void Mtransformaciones::TranslationINV(float tx, float ty, float tz, float*& vertices, int size) {
    T[0][0] = 1; T[0][3] = -tx;
    T[1][1] = 1; T[1][3] = -ty;
    T[2][2] = 1; T[2][3] = -tz;
    changing_vectors(vertices, size, T, 1);
}

void Mtransformaciones::Scale(float sx, float sy, float sz, float*& vertices, int size) {
    S[0][0] = sx;
    S[1][1] = sy;
    S[2][2] = sz;
    changing_vectors(vertices, size, S, 0);
}

void Mtransformaciones::ScaleINV(float sx, float sy, float sz, float*& vertices, int size) {
    S[0][0] = 1 / sx;
    S[1][1] = 1 / sy;
    S[2][2] = 1 / sz;
    changing_vectors(vertices, size, S, 0);
}
//-----------------CLASE Transformaciones-------------------------------------------------------------

//-----------------CLASE FUNCIONES-------------------------------------------------------------
Funciones::Funciones() :circDegree(0) {}
void Funciones::Circunferencia(float*& vertices, int size, float radio, bool Inv) {
    float Degree;
    for (int i = 0; i < size; i += 3) {
        //Usa seno y coseno para sacar la forma circular
        if (!Inv) {
            Degree = circDegree * (3.141592653589793238463 / 180);
            circDegree += 1;
            Translation(cos(Degree) * radio, sin(Degree) * radio, 0, vertices, size);
        }
        else {
            Degree = circDegree * (3.141592653589793238463 / 180);
            circDegree -= 1;
            TranslationINV(cos(Degree) * radio, sin(Degree) * radio, 0, vertices, size);
        }
        
    }
}
//-----------------CLASE FUNCIONES-------------------------------------------------------------

//-----------------CLASE FIGURA-----------------------------------------------------------------------------
Figure::Figure() :vertices(NULL), vertices_legacy(NULL),vertices_convert(NULL), indicesTriangulos(NULL), indicesContorno(NULL), vSize(0), i1Size(0), i2Size(0), VBO(0), EBO1(0), EBO2(0)
{}

Figure::Figure(unsigned int VBO, unsigned int EBO1) :vertices(NULL), vertices_legacy(NULL), vertices_convert(NULL), indicesTriangulos(NULL), indicesContorno(NULL), vSize(0), i1Size(0), i2Size(0), EBO2(0)
{
    this->VBO = VBO;
    this->EBO1 = EBO1;
}

Figure::Figure(unsigned int VBO, unsigned int EBO1, unsigned int EBO2) :vertices(NULL), vertices_legacy(NULL), vertices_convert(NULL), indicesTriangulos(NULL), indicesContorno(NULL), vSize(0), i1Size(0), i2Size(0)
{
    this->VBO = VBO;
    this->EBO1 = EBO1;
    this->EBO2 = EBO2;
}

void Figure::setVertices(int size, float* vertices) {
    vSize = size;
    this->vertices = new float[vSize];
    this->vertices_convert = new float[vSize];
    for (int i = 0; i < vSize; i++) {
        this->vertices[i] = vertices[i];
    }
    this->vertices_legacy = vertices;
}

void Figure::setContorno(int size, unsigned int* indices) {
    i2Size = size;
    this->indicesContorno = indices;
}

void Figure::setTriangulos(int size, unsigned int* indices) {
    i1Size = size;
    this->indicesTriangulos = indices;
}

void Figure::reset() {
    for (int i = 0; i < vSize; i++) {
        this->vertices[i] = this->vertices_legacy[i];
    }
}

//Crea la figura en el VBO
void Figure::createVer_VBO() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vSize * sizeof(float), vertices, GL_STATIC_DRAW);
}

//Crea la figura en el VBO
void Figure::createVer_VBO_Local() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vSize * sizeof(float), vertices_convert, GL_STATIC_DRAW);
}

//Crea los indices del contorno en EBO2
void Figure::createCon_EBO2() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i2Size * sizeof(int), indicesContorno, GL_STATIC_DRAW);
}

//Crea los indices del triangulo en EBO1
void Figure::createTri_EBO1() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i1Size * sizeof(int), indicesTriangulos, GL_STATIC_DRAW);
}

void Figure::update_buffers() {
    createVer_VBO();
    createCon_EBO2();
    createTri_EBO1();
}

void Figure::update_convertedbuffers() {
    createVer_VBO_Local();
    createCon_EBO2();
    createTri_EBO1();
}

void Figure::Update_vertices(float matriz[4][4]) {
    for (int i = 0; i < vSize; i++) {
        this->vertices_convert[i] = this->vertices[i];
    }
    Transform.changing_vectors(vertices_convert, vSize, matriz, 1);
}

void Figure::r_x(float angle) { Transform.Rotacion_x(angle, vertices, vSize); }
void Figure::r_xINV(float angle) { Transform.Rotacion_xINV(angle, vertices, vSize); }
void Figure::r_y(float angle) { Transform.Rotacion_y(angle, vertices, vSize); }
void Figure::r_yINV(float angle) { Transform.Rotacion_yINV(angle, vertices, vSize); }
void Figure::r_z(float angle) { Transform.Rotacion_z(angle, vertices, vSize); }
void Figure::r_zINV(float angle) { Transform.Rotacion_zINV(angle, vertices, vSize); }
void Figure::t(float tx, float ty, float tz) { Transform.Translation(tx, ty, tz, vertices, vSize); }
void Figure::t_INV(float tx, float ty, float tz) { Transform.TranslationINV(tx, ty, tz, vertices, vSize); }
void Figure::s(float sx, float sy, float sz) { Transform.Scale(sx, sy, sz, vertices, vSize); }
void Figure::s_INV(float sx, float sy, float sz) { Transform.ScaleINV(sx, sy, sz, vertices, vSize); }

void Figure::Circunferencia(float radio, bool Inv) { Transform.Circunferencia(vertices, vSize, radio, Inv); }

void Figure::print() {
    for (int i = 0; i < vSize; i += 3) {
        std::cout << "x: " << vertices_convert[i] << " y: " << vertices_convert[i + 1] << " z: " << vertices_convert[i + 2] << std::endl;
    }
}
//-----------------CLASE FIGURA-----------------------------------------------------------------------------

void create_circle(int angle, Figure& Circulo) {
    //Numero de iteraciones que tendremos
    int iterations = 360 / angle;
    //Punto x inicial, y punto y inicial, la magnitud siempre sera la misma
    //currentangle mantiene un seguimiento del angulo en total, hasta llegar a 360
    //degree solo convierte de angulo a radian, la funcion cos y sin toman como parametro radianes.
    float pointx = 0.1f, pointy = 0.0f, magnitude = 0.1f, currentAngle = 0.0, degree = 0.0;
    //Creo los vectores de vertices e indices.
    float* vertices_circulo = new float[(iterations * 3) + 6];
    unsigned int* indices_circulo = new unsigned int[(iterations * 3) + 3];
    unsigned int* indices2_circulo = new unsigned int[iterations * 2];
    //El primer punto sera en el centro (para luego usarlo en los indices y crear triangulos)
    vertices_circulo[0] = 0.0f;
    vertices_circulo[1] = 0.0f;
    vertices_circulo[2] = 0.0f;

    //Luego nuestro segundo punto sera x=0.4
    vertices_circulo[3] = pointx;
    vertices_circulo[4] = pointy;
    vertices_circulo[5] = 0.0f;

    //Creando vertices
    //empezamos en 6 porque ya creamos 2 puntos, luego recorremos de 3 en 3 para ir punto por punto
    for (int i = 6; i <= iterations * 3 + 3; i += 3) {
        //sumamos el angulo (hasta llegar a 360)
        currentAngle += angle;
        //convertimos a radianes
        degree = currentAngle * (3.141592653589793238463 / 180);
        //por trigonometria, x sera hipotenusa*cos(angulo)
        //y sera hipotenusa*sin(angulo) e hipotenusa sera la magnitud (que nunca cambia)
        pointx = magnitude * cos(degree);
        pointy = magnitude * sin(degree);
        //creamos los puntos
        vertices_circulo[i] = pointx;
        vertices_circulo[i + 1] = pointy;
        vertices_circulo[i + 2] = 0.0f;
    }

    //Creando indices
    for (int i = 0, count = 1; i <= iterations * 3; i += 3, count++) {
        //siempre los triangulos usaron el punto del centro del circulo
        indices_circulo[i] = 0;
        indices_circulo[i + 1] = count;
        indices_circulo[i + 2] = count + 1;
    }
    for (int i = 0, count = 1; i < iterations * 2; i += 2, count++) {
        //siempre los triangulos usaron el punto del centro del circulo
        indices2_circulo[i] = count;
        indices2_circulo[i + 1] = count + 1;
    }

    Circulo.setVertices((iterations * 3 + 6), vertices_circulo);
    Circulo.setTriangulos((iterations * 3 + 3), indices_circulo);
    Circulo.setContorno((iterations * 2), indices2_circulo);

    Circulo.update_buffers();
}*/