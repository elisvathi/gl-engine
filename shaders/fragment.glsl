#version 330 core
out vec3 color;
in vec3 fragmentColor;
in vec3 fragmentNormal;
in float lightDistance;
in vec2 UV;
uniform sampler2D G_Texture;
uniform int G_EnableTexture;
uniform vec3 G_LightColor;
uniform vec3 G_LightDirection;
uniform vec3 G_CameraDirection;

void main()
{

  vec3 E = normalize(-G_CameraDirection);
  vec3 R = reflect(-G_LightDirection, fragmentNormal);

  float cosTheta = clamp(dot(E, R), 0 ,1);

	if (G_EnableTexture == 1) {
		// color = fragmentColor;
		color = texture(G_Texture, UV).rgb;
	} else {
		color = fragmentColor;
	}
  color = (fragmentNormal + vec3(1,1,1))/2;
  // vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * color;
  vec3 MaterialAmbientColor = vec3(0,0,0);
  color = MaterialAmbientColor +  color * G_LightColor * cosTheta / lightDistance;  
  // color = G_LightColor;
  // // color = color * fragmentNormal;
  // color = fragmentNormal;
}
