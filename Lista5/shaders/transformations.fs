#version 450 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D ourTexture1;

uniform int channel;        // Image filter channel
uniform vec3 modifier;      // Modifier
uniform vec3 resolution;    // Resolution of window

void main()
{
    // Red
    if (channel == 1) {
        color = vec4(1.0, 0.0, 0.0, 1.0);
    }

    // Green
    else if (channel == 2) {
        color = vec4(0.0, 1.0, 0.0, 1.0);
    }

    // Blue
    else if (channel == 3) {
        color = vec4(0.0, 0.0, 1.0, 1.0);
    }

    // GreyScale
    else if (channel == 4) {
        color = texture(ourTexture1, TexCoord);
        float grey = color.r * 0.2125 + color.g * 0.7154 + color.b * 0.0721;
        color = vec4(grey, grey, grey, 1.0);
    }

    // Colorized
    else if (channel == 5) {
        color = texture(ourTexture1, TexCoord);
        color = vec4(color.r + modifier.r, color.g + modifier.g, color.b + modifier.b, 1.0);    // use modifier to apply color
    }

    // Inverted
    else if (channel == 6) {
        color = texture(ourTexture1, TexCoord);
        float invertR = 1.0 - color.r;
        float invertG = 1.0 - color.g;
        float invertB = 1.0 - color.b;
        color = vec4(invertR, invertG, invertB, 1.0);
    }

    // Binary (Black and White)
    else if (channel == 7) {
        color = texture(ourTexture1, TexCoord);
        float grey = color.r * 0.2125 + color.g * 0.7154 + color.b * 0.0721;    // converts to grey first

        if (grey < 0.5) {                           // turn to black and white depending on the grey result
            color = vec4(0.0, 0.0, 0.0, 1.0);
        }
        else {
            color = vec4(1.0, 1.0, 1.0, 1.0);
        }
    }

    // My filter
     else if (channel == 8) {
        color = texture(ourTexture1, TexCoord);
        float greyR = color.r * 0.2125;             // convert to grey
        float greyG = color.g * 0.7154;
        float greyB = color.b * 0.0721;
        color = vec4(greyR / modifier.r, greyG + modifier.g, greyB / modifier.b, 1.0);  // use grey with modifier
    }

    // Vignette
     else if (channel == 9) {
        vec4 texColor = texture2D(ourTexture1, TexCoord);
        vec2 position = (gl_FragCoord.xy / resolution.xy) - vec2(0.63, 0.17);   // position for effect
        position.x *= resolution.x / resolution.y;                              // correct aspect ratio
        float len = length(position);

	    float vignette = smoothstep(0.2, 0.1, len);                             // smoothstep(RADIUS, SOFTENESS, len)
        texColor.rgb = mix(texColor.rgb, texColor.rgb * vignette, 0.9);         //apply vignette with opacity
	    
	    color = texColor;
    }
}