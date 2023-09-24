/*#pragma once
//My shaders--------------------------------------------------------------------
struct shader {
    GLuint ID;
    shader();
    shader(const char* vertexShaderSource, const char* fragmentShaderSource);
    void activateS();
    void deleteS();
};
//My shaders----------------------------------------------------------------------

//---------------------------------------------------------------------TRANSFORMACIONES---------------------------------------------------------------------
struct Mtransformaciones {
    float rot_x[4][4], rot_y[4][4], rot_z[4][4], T[4][4], S[4][4], temp[3];
    float* res;

    Mtransformaciones();
    float* multiplicacion(float matriz1[3], float matriz2[4][4], bool vector);
    void changing_vectors(float*& vertices, int size, float matriz[4][4], bool vector);
    void Rotacion_x(float angle, float*& vertices, int size);
    void Rotacion_xINV(float angle, float*& vertices, int size);
    void Rotacion_y(float angle, float*& vertices, int size);
    void Rotacion_yINV(float angle, float*& vertices, int size);
    void Rotacion_z(float angle, float*& vertices, int size);
    void Rotacion_zINV(float angle, float*& vertices, int size);
    void Translation(float tx, float ty, float tz, float*& vertices, int size);
    void TranslationINV(float tx, float ty, float tz, float*& vertices, int size);
    void Scale(float sx, float sy, float sz, float*& vertices, int size);
    void ScaleINV(float sx, float sy, float sz, float*& vertices, int size);
    float** multiplicacion2(float matriz1[4][4], float matriz2[4][4]);
};
//---------------------------------------------------------------------TRANSFORMACIONES---------------------------------------------------------------------

//-----------------CLASE FUNCIONES-------------------------------------------------------------
struct Funciones : public Mtransformaciones {
    Funciones();
    float circDegree;
    void Circunferencia(float*& vertices, int size, float radio, bool Inv);
};
//-----------------CLASE FUNCIONES-------------------------------------------------------------

//---------------------------------------------------------------------Figura---------------------------------------------------------------------
struct Figure {
    float* vertices, * vertices_legacy, *vertices_convert;
    unsigned int* indicesTriangulos;
    unsigned int* indicesContorno;
    int vSize, i1Size, i2Size;
    unsigned int VBO, EBO1, EBO2;
    Funciones Transform;

    Figure();
    Figure(unsigned int VBO, unsigned int EBO1);
    Figure(unsigned int VBO, unsigned int EBO1, unsigned int EBO2);
    void setVertices(int size, float* vertices);
    void setContorno(int size, unsigned int* indices);
    void setTriangulos(int size, unsigned int* indices);
    void reset();
    void createVer_VBO_Local();
    void createVer_VBO();
    void createCon_EBO2();
    void createTri_EBO1();
    void update_buffers();
    void update_convertedbuffers();
    void Update_vertices(float matriz[4][4]);
    void r_x(float angle);
    void r_xINV(float angle);
    void r_y(float angle);
    void r_yINV(float angle);
    void r_z(float angle);
    void r_zINV(float angle);
    void t(float tx, float ty, float tz);
    void t_INV(float tx, float ty, float tz);
    void s(float sx, float sy, float sz);
    void s_INV(float sx, float sy, float sz);
    void Circunferencia(float radio, bool Inv);
    void print();
};
//---------------------------------------------------------------------Figura---------------------------------------------------------------------

void create_circle(int angle, Figure& Circulo);*/