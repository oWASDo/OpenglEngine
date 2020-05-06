#s vertex start
#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 uv;


out float lambert;
out vec3 nor;
out vec2 uvs;

void main() {

	uvs = uv;
	nor = norm;
	float x = position.x;
	float y = position.y;
	float z = position.z;

	/*x = (cos(0)*x) - (sin(0)*y);
	y = (sin(0)*x) + (cos(0)*y);

	x = (cos(45) * x) + (sin(90)* z);
	z = -(sin(90) * x) + (cos(90)* z);

	y = (cos(0)*y) - (sin(0)*z);
	z = (sin(0)*y) + (cos(0)* z);*/

	gl_Position = vec4(x, y - 9, z, 10);


}
#s vertex end



#s fragment start
#version 430 core
layout(location = 0) out vec4 color;

struct FakeVector {
	float x;
	float y;
	float z;
};
struct Lights_Struct {
	float intensity;
	FakeVector direction;
};
layout(std430, binding = 10) buffer Lights
{
	float NumOfDirectLight;
	Lights_Struct lightsArray[];

};
vec4 ApplyLight(vec3 normal ,vec4 color) {

	vec4 outColor = color;
	float intensit;

	for (float f = 0; f < NumOfDirectLight; f += 1) {
		//work
		vec3 dir = vec3(lightsArray[int(f)].direction.x, lightsArray[int(f)].direction.y, lightsArray[int(f)].direction.z);

		float dotProd;
		dotProd = dot(normal, dir);

		intensit += clamp(dotProd, -0.01, 1.0);// *lightsArray[int(f)].intensity;

		intensit = clamp(intensit,0,1);
		/*if (intensit > 1) {
			intensit = 1;
		}*/
		//end work



	}


	return outColor * intensit;
}


in float lambert;
in vec2 uvs;
in vec3 nor;

uniform sampler2D TextureAlbedo;



void main() {

	vec4 outColor;
	outColor = texture(TextureAlbedo, uvs);
	outColor = ApplyLight(nor ,outColor);
	color = outColor;
}

#s fragment end



