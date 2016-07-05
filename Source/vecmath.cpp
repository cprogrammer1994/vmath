#include "vecmath.h"

#include <cmath>

float Length(const Vector & v) {
	return sqrt(v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2]);
}

Vector Normal(const Vector & v) {
	float length = sqrt(v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2]);
	return {
		v.v[0] / length,
		v.v[1] / length,
		v.v[2] / length,
	};
}

Vector Cross(const Vector & a, const Vector & b) {
	return {
		a.v[1] * b.v[2] - b.v[1] * a.v[2],
		a.v[2] * b.v[0] - b.v[2] * a.v[0],
		a.v[0] * b.v[1] - b.v[0] * a.v[1],
	};
}

float Dot(const Vector & a, const Vector & b) {
	return a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2];
}

Vector operator * (const Vector & v, const float & f) {
	return {
		v.v[0] * f,
		v.v[1] * f,
		v.v[2] * f,
	};
}

Vector operator / (const Vector & v, const float & f) {
	return {
		v.v[0] / f,
		v.v[1] / f,
		v.v[2] / f,
	};
}

Vector operator + (const Vector & a, const Vector & b) {
	return {
		a.v[0] + b.v[0],
		a.v[1] + b.v[1],
		a.v[2] + b.v[2],
	};
}

Vector operator - (const Vector & a, const Vector & b) {
	return {
		a.v[0] - b.v[0],
		a.v[1] - b.v[1],
		a.v[2] - b.v[2],
	};
}

Vector operator * (const Matrix & m, const Vector & v) {
	return {
		m.m[0] * v.v[0] + m.m[1] * v.v[1] + m.m[2] * v.v[2] + m.m[3],
		m.m[4] * v.v[0] + m.m[5] * v.v[1] + m.m[6] * v.v[2] + m.m[7],
		m.m[8] * v.v[0] + m.m[9] * v.v[1] + m.m[10] * v.v[2] + m.m[11],
	};
}

Matrix operator * (const Matrix & a, const Matrix & b) {
    return {
        a.m[0] * b.m[0] + a.m[4] * b.m[1] + a.m[8] * b.m[2] + a.m[12] * b.m[3],
        a.m[1] * b.m[0] + a.m[5] * b.m[1] + a.m[9] * b.m[2] + a.m[13] * b.m[3],
        a.m[2] * b.m[0] + a.m[6] * b.m[1] + a.m[10] * b.m[2] + a.m[14] * b.m[3],
        a.m[3] * b.m[0] + a.m[7] * b.m[1] + a.m[11] * b.m[2] + a.m[15] * b.m[3],
        a.m[0] * b.m[4] + a.m[4] * b.m[5] + a.m[8] * b.m[6] + a.m[12] * b.m[7],
        a.m[1] * b.m[4] + a.m[5] * b.m[5] + a.m[9] * b.m[6] + a.m[13] * b.m[7],
        a.m[2] * b.m[4] + a.m[6] * b.m[5] + a.m[10] * b.m[6] + a.m[14] * b.m[7],
        a.m[3] * b.m[4] + a.m[7] * b.m[5] + a.m[11] * b.m[6] + a.m[15] * b.m[7],
        a.m[0] * b.m[8] + a.m[4] * b.m[9] + a.m[8] * b.m[10] + a.m[12] * b.m[11],
        a.m[1] * b.m[8] + a.m[5] * b.m[9] + a.m[9] * b.m[10] + a.m[13] * b.m[11],
        a.m[2] * b.m[8] + a.m[6] * b.m[9] + a.m[10] * b.m[10] + a.m[14] * b.m[11],
        a.m[3] * b.m[8] + a.m[7] * b.m[9] + a.m[11] * b.m[10] + a.m[15] * b.m[11],
        a.m[0] * b.m[12] + a.m[4] * b.m[13] + a.m[8] * b.m[14] + a.m[12] * b.m[15],
        a.m[1] * b.m[12] + a.m[5] * b.m[13] + a.m[9] * b.m[14] + a.m[13] * b.m[15],
        a.m[2] * b.m[12] + a.m[6] * b.m[13] + a.m[10] * b.m[14] + a.m[14] * b.m[15],
        a.m[3] * b.m[12] + a.m[7] * b.m[13] + a.m[11] * b.m[14] + a.m[15] * b.m[15],
	};
}

Matrix Perspective(float fovy, float ratio, float znear, float zfar) {
	float zmul = (-2.0 * znear * zfar) / (zfar - znear);
	float ymul = 1.0 / tanf(fovy * 3.14159265 / 360);
	float xmul = ymul / ratio;

	return {
		xmul, 0.0, 0.0, 0.0,
		0.0, ymul, 0.0, 0.0,
        0.0, 0.0, -1.0, -1.0,
        0.0, 0.0, zmul, 0.0,
	};
}

Matrix LookAt(const Vector & eye, const Vector & center, const Vector & up) {
	Vector forward = Normal(center - eye);
	Vector side = Normal(Cross(forward, up));
	Vector upward = Cross(side, forward);
    return {
        side.v[0], upward.v[0], -forward.v[0], 0,
        side.v[1], upward.v[1], -forward.v[1], 0,
        side.v[2], upward.v[2], -forward.v[2], 0,
        -Dot(eye, side), -Dot(eye, upward), Dot(eye, forward), 1,
    };
}
