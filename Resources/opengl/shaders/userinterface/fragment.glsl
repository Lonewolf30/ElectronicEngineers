#version 130

in vec2 textCoords;
in vec2 windowAspect;
in float radius;

uniform sampler2D img;

out vec4 out_Color;

void main(void)
{
    out_Color = texture(img, textCoords);
    vec2 r = (windowAspect / 2.0) - radius;
    vec2 pos = textCoords - 0.5f;
    pos = pos * windowAspect;

    if (abs(pos.x) > r.x && abs(pos.y) > r.y)
    {
        vec2 distance = abs(pos) - r;

        if (length(distance) > radius)
        out_Color = vec4(1,0,1,0);
    }
}