void mainImage(in vec2 fragCoord, out vec4 fragColor) {
    vec2 center = iResolution.xy / 2.0;

    float radius = min(iResolution.x, iResolution.y) / 2.0;

    vec3 pixel;
    float alpha = 1.0;

    float distanceToCenter = length(fragCoord - center);

    if(distanceToCenter < radius) {
        pixel = vec3(1., 0., 0.);
    } else {
        pixel = vec3(0., 0., 0.);
    }

    fragColor = vec4(pixel, alpha);
}

void mainImage(in vec2 fragCoord, out vec4 fragColor) {
    float squareSize = 20.0;
    vec3 pixel;

    int i = int(fragCoord.x / squareSize);
    int j = int(fragCoord.y / squareSize);

    if((i + j) % 2 == 0) {
        pixel = vec3(0., 0., 0.);
    } else {
        pixel = vec3(1., 1., 1.);
    }

    fragColor = vec4(pixel, 1.0);
}