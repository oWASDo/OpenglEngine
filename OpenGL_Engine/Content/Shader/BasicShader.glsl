#s vertex start
#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 uv;

out float lambert;
out vec2 uvs;
out vec3 Light;


void main() {

	uvs = uv;
	vec3 light_vector = vec3(0, 3, 2);
	Light = light_vector;
	lambert = dot(norm, light_vector);
	float x = position.x;
	float y = position.y + Col.y;
	float z = position.z;

	x = (cos(0)*x) - (sin(0)*y);
	y = (sin(0)*x) + (cos(0)*y);

	x = (cos(180) * x) + (sin(180)* z);
	z = -(sin(180) * x) + (cos(180)* z);

	y = (cos(0)*y) - (sin(0)*z);
	z = (sin(0)*y) + (cos(0)* z);

	gl_Position = vec4(x, y - 9, z, 10);


}
#s vertex end



#s fragment start
#version 420 core

layout(location = 0) out vec4 color;
in float lambert;
in vec2 uvs;


in vec3 Light;
uniform sampler2D TextureAlbedo;
uniform vec3 Col;


void main() {

	vec4 outColor;
		outColor = texture(TextureAlbedo, uvs);
		//float lambImage = dot(normal.xyz, Light);
		outColor *= lambert;

	color = outColor;
}

#s fragment end