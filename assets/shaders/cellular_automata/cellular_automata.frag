#version 430 core
out vec4 FragColor;

uniform sampler2D uPrevState;

void main() {
    ivec2 size = textureSize(uPrevState, 0);
    ivec2 coord = ivec2(gl_FragCoord.xy); // integer texel coord

    int aliveNeighbors = 0;
    for (int y = -1; y <= 1; ++y) {
        for (int x = -1; x <= 1; ++x) {
            if (x == 0 && y == 0) continue;
            ivec2 nCoord = coord + ivec2(x, y);

            // wrap around
            nCoord = (nCoord + size) % size;

            aliveNeighbors += texelFetch(uPrevState, nCoord, 0).r > 0.5 ? 1 : 0;
        }
    }

    float currentState = texelFetch(uPrevState, coord, 0).r;
    float nextState = currentState;

    if (currentState > 0.5) {
        nextState = (aliveNeighbors == 2 || aliveNeighbors == 3) ? 1.0 : 0.0;
    } else {
        nextState = (aliveNeighbors == 3) ? 1.0 : 0.0;
    }

    FragColor = vec4(nextState, nextState, nextState, 1.0);
}
