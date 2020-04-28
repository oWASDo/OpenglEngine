#s vertex start
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 norm;

out float lambert;

void main() {

	//gl_Position = vec4(position.x + (norm.x * 0.1), position.y - 1 + (norm.y* 0.1), position.z + (norm.z* 0.1), 1);
	vec3 light_vector = vec3(0, 0, 1);
	lambert = dot(norm, light_vector);
	float x = position.x;
	float y = position.y;
	float z = position.z;

	x = (cos(0)*x) - (sin(0)*y);
	y = (sin(0)*x) + (cos(0)*y);

	x = (cos(180) * x) + (sin(180)* z);
	z = -(sin(180) * x) + (cos(180)* z);

	y = (cos(0)*y) - (sin(0)*z);
	z = (sin(0)*y) + (cos(0)* z);

	//	lambert = clamp(lambert, 0, 1);
	gl_Position = vec4(x, y , z, 1);
	//gl_Position = vec4(position.x, position.y - 1, position.z, 1);


}
#s vertex end



#s fragment start
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 c;

in float lambert;
void main() {

	vec3 col = vec3(1, 0, 0) * 1;
	color = vec4(col, 1.0);
}

#s fragment end