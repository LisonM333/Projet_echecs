#version 330

in vec3 vNormal_vs;
in vec3 vPosition_vs;
in vec2 vTexCoords;

out vec4 fFragColor;

// Material properties
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

// Light properties
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong(){
    vec3 Li = normalize(uLightIntensity);
    vec3 wi = normalize(uLightDir_vs);

    vec3 N = normalize(vNormal_vs);

    vec3 w0 = normalize(-vPosition_vs);
    vec3 halfVector = normalize(wi + w0);

    float diffusion = max(dot(N, wi), 0.0);
    vec3 diffusion_part = uKd * diffusion;

    float specular = pow(max(dot(N, halfVector), 0.0), uShininess);
    vec3 specular_part = uKs * specular;

    return Li*(diffusion_part + specular_part);
}

void main(){
    fFragColor = vec4(blinnPhong(), 1.0);
}