#version 450

struct triangle{
    mat3 invm;
    uvec3 vertices;
    float edgl;
};

struct pyramid{
    mat3 invm;
    uvec4 vertices;
    float edgl;
};

uniform vec3 dinpal[204];
uniform vec3 xyzpal[204];
//uniform uvec2 lines[5570];

layout (std430, binding=1) restrict readonly buffer edges{
    uvec2 lines[];
};

layout (std430, binding=2, column_major) restrict readonly buffer tris{
    triangle triangles[];
};

layout (std430, binding=3, column_major) restrict readonly buffer pyras{
    pyramid pyramids[];
};

in vec3 incol;
layout(location = 0) out uvec4 cols;
layout(location = 1) out uvec4 mix;
#define PI 3.14159265359
#define E 2.71828182846

vec3 srgb2xyz(vec3 srgb){
    vec3 rgb = srgb/12.92;
    if(srgb.r>0.04045)rgb.r=pow((srgb.r+0.055)/1.055, 2.4);
    if(srgb.g>0.04045)rgb.g=pow((srgb.g+0.055)/1.055, 2.4);
    if(srgb.b>0.04045)rgb.b=pow((srgb.b+0.055)/1.055, 2.4);
    vec3 xyz = rgb*mat3(0.4124564, 0.3575761, 0.1804375,
    0.2126729, 0.7151522, 0.0721750,
    0.0193339, 0.1191920, 0.9503041);
    return xyz / vec3(0.95047, 1, 1.08883);
}

vec3 xyz2din(vec3 n){
    vec3 v;
    v.x = ( n.x > 0.008856 ) ? pow( n.x, 1.0 / 3.0 ) : ( 7.787 * n.x ) + ( 16.0 / 116.0 );
    v.y = ( n.y > 0.008856 ) ? pow( n.y, 1.0 / 3.0 ) : ( 7.787 * n.y ) + ( 16.0 / 116.0 );
    v.z = ( n.z > 0.008856 ) ? pow( n.z, 1.0 / 3.0 ) : ( 7.787 * n.z ) + ( 16.0 / 116.0 );
    vec3 lab = vec3(( 116.0 * v.y ) - 16.0, 500.0 * ( v.x - v.y ), 200.0 * ( v.y - v.z ));
    vec3 din;
    din.x = 105.51 * log(1+0.0158*lab.x);
    vec2 ef = lab.yz * mat2(     cos(16*PI/180),     sin(16*PI/180),
                            -0.7*sin(16*PI/180), 0.7*cos(16*PI/180));
    float G = length(ef);
    float k=log(1+0.045*G)/0.045;
    din.yz = (k/G)*ef;
    return din;
}

void main(){
    vec3 xyzcol = srgb2xyz(incol);
    vec3 dincol = xyz2din(xyzcol);
    uvec4 indices = uvec4(251);
    vec4 mf = vec4(0);
    float cd = 9999999;
    for(int i = 0; i < dinpal.length(); i++){
        vec3 tv = dincol-dinpal[i];
        float dis = dot(tv,tv);
        if(dis < cd){
            cd=dis;
            indices=i.xxxx;
            mf=vec4(0,0,0,0.125);
        }
    }
    for(uint i = 0; i < lines.length(); i++){
        vec3 a = xyzpal[lines[i].x], b = xyzpal[lines[i].y];
        vec3 ab = b-a;
        for(uint mr = 0; mr <= 64; mr++){
            float pl = float(mr)/64.;
            vec3 pp = xyz2din(a+pl*ab);
            float dis = dot(dincol-pp, dincol-pp)+0.01*length(ab);
            if (dis < cd){
                cd=dis;
                indices = lines[i].xyyy;
                mf=vec4(pl, 0, 0, 0.25);
            }
        }
    }
    float tel = 999999999999999.;
    for(uint i = 0; i < pyramids.length(); i++){
        vec3 a = xyzpal[pyramids[i].vertices.x], b = xyzpal[pyramids[i].vertices.y], c = xyzpal[pyramids[i].vertices.z], d = xyzpal[pyramids[i].vertices.w];
        vec3 ab = a-b, ac=a-c, ad=a-d;
        vec3 dat = (xyzcol-a) * pyramids[i].invm;
        if(dat.x <= -0.0001 || dat.y <= -0.0001 || dat.z <= -0.0001 || dat.x+dat.y+dat.z > 1.0001) continue;
        if(pyramids[i].edgl < tel){
            cd=0;
            tel = pyramids[i].edgl;
            indices = pyramids[i].vertices;
            mf = vec4(dat.xyz,0.5);
        }
    }
    cols = indices+uvec4(4);
    mix = uvec4(64*vec4(1.-mf.z-mf.y-mf.x, 1.-mf.z-mf.y, 1.-mf.z, mf.w));
}


