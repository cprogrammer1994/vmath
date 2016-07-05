#pragma once

struct Vector {
	union {
		float v[3];
		struct {
			float x, y, z;
		};
	};
};

struct Matrix {
	float m[16];
};

float Length(const Vector & v);
Vector Normal(const Vector & v);
Vector Cross(const Vector & a, const Vector & b);
float Dot(const Vector & a, const Vector & b);

Vector operator * (const Vector & v, const float & f);
Vector operator / (const Vector & v, const float & f);
Vector operator + (const Vector & a, const Vector & b);
Vector operator - (const Vector & a, const Vector & b);
Vector operator * (const Matrix & m, const Vector & v);
Matrix operator * (const Matrix & a, const Matrix & b);

Matrix Perspective(float fovy, float ratio, float znear, float zfar);
Matrix LookAt(const Vector & eye, const Vector & center, const Vector & up);
