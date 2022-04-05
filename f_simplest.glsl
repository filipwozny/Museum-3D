#version 330


out vec4 pixelColor; 

uniform sampler2D textureMap0;
in vec2 iTexCoord0;
in vec3 camera;
in vec3 nc;
in vec3 position;

 
#define NUMBER 3


vec3 pointLightPositions1 = vec3( -5.0f,  0.5f,  -2.5f);
vec3 pointLightPositions2 = vec3( 5.0f,  0.5f,  2.5f);
vec3 pointLightPositions3 = vec3( -5.0f,  0.5f,  0.5f);


vec3 CalcPointLight(vec3 light, vec3 normal, vec3 fragPos, vec3 viewDir){

        vec3 lightDir = normalize(light - fragPos);
        // światło rozproszone
        float diff = max(dot(normal, lightDir), 0.0);
        // światło lustrzane
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0),0.2);
        // tłumienie
        float distance    = length(light - fragPos);
        float attenuation = 1.0 / ( 1.0 + 0.1 * distance + 0.00032 * (distance * distance));    
        // połącz wyniki
        vec3 ambient  = vec3(0.2f, 0.2f, 0.2f)  * vec3(texture(textureMap0,iTexCoord0)) ;
        vec3 diffuse  = vec3(0.8f, 0.8f, 0.8f)  * diff * vec3(texture(textureMap0,iTexCoord0)) ;
        vec3 specular = vec3(0.8f,0.8f,0.8f) * spec * vec3(texture(textureMap0,iTexCoord0)) ;
        ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;
        return (ambient + diffuse + specular);



}



void main(void) {

        vec3 norm = nc; 
        vec3 viewDir = normalize(camera - position);
        vec3 result = vec3(0,0,0);
 
        
        result += CalcPointLight(pointLightPositions1, nc, position, viewDir);  
        result += CalcPointLight(pointLightPositions2, nc, position, viewDir);    
        result += CalcPointLight(pointLightPositions3, nc, position, viewDir);    
        
               

        pixelColor = vec4(result, 0);



}
