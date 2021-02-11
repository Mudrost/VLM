/* This file is part of an educational VLM project which is released under GNU General Public License v3.0 license
	For full details, check https://github.com/Mudrost/VLM/blob/main/LICENSE
*/

#include "Vetores.h"
#include <math.h>

Vetor3D Vetor3D::operator+ (const Vetor3D& vec) {
	return Vetor3D(x + vec.x, y + vec.y, z + vec.z);
}
Vetor3D Vetor3D::operator- (const Vetor3D& vec) {
	return Vetor3D(x + vec.x, y + vec.y, z + vec.z);
}
Vetor3D Vetor3D::operator* (const Vetor3D& vec) {
	double i = y * vec.z - z * vec.y;
	double j = z * vec.x - x * vec.z;
	double k = x * vec.y - y * vec.x;
	return Vetor3D(i, j, k);
}
Vetor3D Vetor3D::operator* (const double value) {
	return Vetor3D(x*value, y*value, z*value);
}
Vetor3D Vetor3D::operator/ (const double value) {
	return Vetor3D(x/value, y/value, z/value);
}
double Vetor3D::mod() {
	return sqrt(square());
}
double Vetor3D::square() {
	return ((x * x) + (y * y) + (z * z));
}
double Vetor3D::dot(Vetor3D vec) {
	return ((x * vec.x) + (y * vec.y) + (z * vec.z));
}