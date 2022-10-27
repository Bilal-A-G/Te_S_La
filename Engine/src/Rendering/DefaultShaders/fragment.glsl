#version 330 core
in vec3 colour;
in vec3 outNormal;
in vec3 outPosition;
in vec3 viewerPosition;

out vec4 frag_colour;
void main()
{
    vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightPos = vec3(10.0f, 5.0f, 0.0f);
    float specStrength = 0.2f;
    
    vec3 normVec = normalize(outNormal);
    
    float ambientStrength = 0.3f;
    vec3 ambientLight = ambientStrength * lightColour;
    
    vec3 lightDir = normalize(lightPos - outPosition);
    float incidentAngle = max(dot(lightDir, normVec), 0.0f);
    vec3 diffuseLight = incidentAngle * lightColour;
    
    vec3 viewDir = viewerPosition - outPosition;
    vec3 reflectDir = reflect(-lightDir, normVec);
    
    float shinyness = 20;
    float specular = pow(max(dot(viewDir, reflectDir), 0.0f), shinyness);
    vec3 specularLight = specStrength * specular * lightColour;
  
    vec3 totalLight = (ambientLight + diffuseLight + specularLight) * colour;
    frag_colour = vec4(totalLight, 0.0f);
}