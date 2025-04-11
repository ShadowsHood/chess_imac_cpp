#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightPos2;
uniform vec3 lightColor2;
uniform vec3 viewPos;
//
uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Ns;

uniform bool useTexture;
uniform sampler2D map_Kd;

uniform vec3 objectColor;

void main() {

    vec3 diffuseColor = useTexture ? texture(map_Kd, TexCoords).rgb : Kd;

    //
    // 1st light source
    //

    // Ambient
    vec3 ambient = Ka * (lightColor * 0.25);

    // Diffuse
    vec3 L = normalize(lightPos - FragPos);
    vec3 N = normalize(Normal);
    float diff = max(dot(L, N), 0.0);
    vec3 diffuse = diff * diffuseColor * lightColor;

    // Specular
    vec3 V = normalize(viewPos - FragPos);
    vec3 H = normalize(L + V);
    float spec = pow(max(dot(N, H), 0.0), Ns);
    vec3 specular = spec * Ks * lightColor;

    vec3 result = (ambient + diffuse + specular);

    //
    // 2nd light source
    //

    // Ambient
    vec3 ambient2 = Ka * (lightColor2 * 0.25);

    // Diffuse
    vec3 L2 = normalize(lightPos2 - FragPos);
    float diff2 = max(dot(L2, N), 0.0);
    vec3 diffuse2 = diff2 * diffuseColor * lightColor2;

    // Specular
    vec3 H2 = normalize(L2 + V);
    float spec2 = pow(max(dot(N, H2), 0.0), Ns);
    vec3 specular2 = spec2 * Ks * lightColor2;

    vec3 result2 = (ambient2 + diffuse2 + specular2);

    // Combine both light sources

    // => Blinn-Phong
    vec3 finalResult = (result + result2) * objectColor;

    FragColor = vec4(finalResult, 1.0);
}
