xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 426;
 -4.76566;1.00872;-39.12061;,
 -4.76566;1.00872;-50.65677;,
 -4.76566;-0.98796;-50.65677;,
 -4.76566;-0.98796;-39.12061;,
 3.16726;0.99834;-40.03115;,
 3.16726;-0.99834;-40.03115;,
 -1.78227;-0.99834;-49.60949;,
 -1.78227;0.99834;-49.60949;,
 -4.76566;1.00872;-26.05033;,
 -4.76566;-0.98796;-26.05033;,
 -4.76566;-0.98796;-0.29674;,
 -4.76566;1.00872;-0.29674;,
 5.66440;0.99834;-25.95829;,
 5.66440;0.99834;-0.20470;,
 5.66440;-0.99834;-0.20470;,
 5.66440;-0.99834;-25.95829;,
 -1.91754;1.00872;-49.65423;,
 -4.76566;1.00872;-50.65677;,
 -4.76566;1.00872;-39.12061;,
 1.81057;1.00872;-39.28975;,
 3.16726;0.99834;-40.03115;,
 -1.78227;0.99834;-49.60949;,
 -1.91754;1.00872;-49.65423;,
 -1.78227;0.99834;-49.60949;,
 -1.78227;-0.99834;-49.60949;,
 -1.91754;-0.98796;-49.65423;,
 -4.76566;-0.98796;-50.65677;,
 -4.76566;1.00872;-50.65677;,
 -4.76566;1.00872;-26.05033;,
 4.39466;1.00872;-26.05033;,
 5.66440;0.99834;-25.95829;,
 -1.91754;-0.98796;-49.65423;,
 -1.78227;-0.99834;-49.60949;,
 3.16726;-0.99834;-40.03115;,
 1.81057;-0.98796;-39.28975;,
 -4.76566;-0.98796;-39.12061;,
 -4.76566;-0.98796;-50.65677;,
 4.39466;1.00872;-0.29674;,
 5.66440;-0.99834;-25.95829;,
 4.39466;-0.98796;-26.05033;,
 -4.76566;-0.98796;-26.05033;,
 4.39466;1.00872;-0.29674;,
 -4.76566;1.00872;-0.29674;,
 -4.76566;-0.98796;-0.29674;,
 4.39466;-0.98796;-0.29674;,
 5.66440;-0.99834;-0.20470;,
 5.66440;0.99834;-0.20470;,
 4.39466;-0.98796;-0.29674;,
 5.82049;1.10858;-9.25662;,
 9.65471;1.10858;0.00000;,
 9.65471;-1.10858;0.00000;,
 5.82049;-1.10858;-9.25662;,
 5.82049;1.10858;9.25662;,
 5.82049;-1.10858;9.25662;,
 -2.61718;1.28750;-3.97446;,
 0.19319;1.28750;-2.81037;,
 0.19319;-1.28750;-2.81037;,
 -2.61718;-1.28750;-3.97446;,
 1.35729;1.28750;0.00000;,
 1.35729;-1.28750;0.00000;,
 0.19319;1.28750;2.81037;,
 0.19319;-1.28750;2.81037;,
 -2.61718;1.28750;3.97446;,
 -2.61718;-1.28750;3.97446;,
 -5.42755;1.28750;2.81037;,
 -5.42755;-1.28750;2.81037;,
 -6.59164;1.28750;0.00000;,
 -6.59164;-1.28750;0.00000;,
 -5.42755;1.28750;-2.81037;,
 -5.42755;-1.28750;-2.81037;,
 -2.61718;1.28750;-3.97446;,
 -2.61718;-1.28750;-3.97446;,
 -2.61718;1.28750;0.00000;,
 -2.61718;1.28750;0.00000;,
 -2.61718;1.28750;0.00000;,
 -2.61718;1.28750;0.00000;,
 -2.61718;1.28750;0.00000;,
 -2.61718;1.28750;0.00000;,
 -2.61718;1.28750;0.00000;,
 -2.61718;1.28750;0.00000;,
 -2.61718;-1.28750;0.00000;,
 -2.61718;-1.28750;0.00000;,
 -2.61718;-1.28750;0.00000;,
 -2.61718;-1.28750;0.00000;,
 -2.61718;-1.28750;0.00000;,
 -2.61718;-1.28750;0.00000;,
 -2.61718;-1.28750;0.00000;,
 -2.61718;-1.28750;0.00000;,
 2.24295;1.10858;-5.67907;,
 -3.43613;1.10858;0.00000;,
 4.77330;1.10858;0.00000;,
 2.67750;-1.10858;-6.11362;,
 -3.43613;-1.10858;0.00000;,
 4.73539;1.10858;0.00000;,
 -3.43613;1.10858;0.00000;,
 2.04851;1.10858;5.48463;,
 2.04851;1.10858;5.48463;,
 1.94271;-1.10858;5.37883;,
 4.55504;-1.10858;0.00000;,
 2.60243;-1.10858;-6.03855;,
 4.55502;-1.10858;0.00000;,
 4.57776;-1.10858;0.00000;,
 4.56406;-1.10858;0.02795;,
 1.94271;-1.10858;5.37883;,
 -3.43613;-1.10858;0.00000;,
 5.16655;1.10858;-8.60268;,
 8.76244;1.10858;0.00000;,
 5.24598;-1.10858;-8.68211;,
 8.71557;1.10858;0.00000;,
 5.10039;1.10858;8.53651;,
 5.10039;1.10858;8.53651;,
 5.08019;-1.10858;8.51631;,
 5.08019;-1.10858;8.51631;,
 8.68547;-1.10858;0.00000;,
 8.69140;-1.10858;0.00000;,
 5.21261;-1.10858;-8.64874;,
 -3.47560;1.14797;19.46807;,
 -3.96355;1.14797;19.46807;,
 -3.96355;-1.14797;19.46807;,
 -3.47560;-1.14797;19.46807;,
 -3.47560;1.14797;-2.30166;,
 -3.47560;-1.14797;-2.30166;,
 -3.96355;-1.14797;-2.30166;,
 -3.96355;1.14797;-2.30166;,
 -3.47560;1.14797;6.06486;,
 -3.47560;1.14797;-2.30166;,
 -3.96355;1.14797;-2.30166;,
 -3.96355;1.14797;6.06486;,
 -3.96355;1.14797;16.80598;,
 -3.47560;1.14797;16.80598;,
 -3.96355;1.14797;6.06486;,
 -3.96355;1.14797;-2.30166;,
 -3.96355;-1.14797;-2.30166;,
 -3.96355;-1.14797;6.06486;,
 -3.96355;-1.14797;16.80598;,
 -3.96355;1.14797;16.80598;,
 -1.07554;1.14797;6.06486;,
 -1.25758;1.14797;16.80598;,
 -1.25758;-1.14797;16.80598;,
 -1.07554;-1.14797;6.06486;,
 -1.07554;-1.14797;-2.30166;,
 -1.07554;1.14797;-2.30166;,
 -3.96355;-1.14797;6.06486;,
 -3.96355;-1.14797;-2.30166;,
 -3.47560;-1.14797;-2.30166;,
 -3.47560;-1.14797;6.06486;,
 -3.47560;-1.14797;16.80598;,
 -3.96355;-1.14797;16.80598;,
 -1.62515;1.14797;6.06486;,
 -1.62515;1.14797;16.80598;,
 -1.25758;1.14797;16.80598;,
 -1.07554;1.14797;6.06486;,
 -1.07554;1.14797;-2.30166;,
 -1.62515;1.14797;-2.30166;,
 -1.62515;1.14797;-2.30166;,
 -1.07554;1.14797;-2.30166;,
 -1.07554;-1.14797;-2.30166;,
 -1.62515;-1.14797;-2.30166;,
 -1.62515;1.14797;19.46807;,
 -1.62515;-1.14797;19.46807;,
 -0.76069;-1.14797;19.46807;,
 -0.76069;1.14797;19.46807;,
 -1.62515;-1.14797;-2.30166;,
 -1.07554;-1.14797;-2.30166;,
 -1.07554;-1.14797;6.06486;,
 -1.62515;-1.14797;6.06486;,
 -1.25758;-1.14797;16.80598;,
 -1.62515;-1.14797;16.80598;,
 -0.76069;-1.14797;17.96131;,
 -0.76069;1.14797;17.96131;,
 -0.76069;1.14797;19.46807;,
 -0.76069;-1.14797;19.46807;,
 -0.76069;-1.14797;17.96131;,
 -1.62515;-1.14797;19.46807;,
 -1.62515;-1.14797;17.96131;,
 -0.76069;1.14797;17.96131;,
 -1.62515;1.14797;17.96131;,
 -1.62515;1.14797;19.46807;,
 -3.47560;-1.14797;19.46807;,
 -3.47560;-1.14797;17.96131;,
 -3.47560;1.14797;17.96131;,
 -3.47560;1.14797;19.46807;,
 -3.96355;-1.14797;19.46807;,
 -3.96355;-1.14797;17.96131;,
 -3.96355;1.14797;17.96131;,
 -3.96355;1.14797;19.46807;,
 -3.96355;-1.14797;17.96131;,
 -3.96355;1.14797;17.96131;,
 -0.02516;1.10306;-24.18414;,
 0.37864;1.10306;-24.01687;,
 0.37864;-1.10306;-24.01687;,
 -0.02516;-1.10306;-24.18414;,
 0.54590;1.10306;-23.61307;,
 0.54590;-1.10306;-23.61307;,
 0.37864;1.10306;-23.20928;,
 0.37864;-1.10306;-23.20928;,
 -0.02516;1.10306;-23.04200;,
 -0.02516;-1.10306;-23.04200;,
 -0.42896;1.10306;-23.20928;,
 -0.42896;-1.10306;-23.20928;,
 -0.59622;1.10306;-23.61307;,
 -0.59622;-1.10306;-23.61307;,
 -0.42896;1.10306;-24.01687;,
 -0.42896;-1.10306;-24.01687;,
 -0.02516;1.10306;-24.18414;,
 -0.02516;-1.10306;-24.18414;,
 -0.02516;1.10306;-23.61307;,
 -0.02516;1.10306;-23.61307;,
 -0.02516;1.10306;-23.61307;,
 -0.02516;1.10306;-23.61307;,
 -0.02516;1.10306;-23.61307;,
 -0.02516;1.10306;-23.61307;,
 -0.02516;1.10306;-23.61307;,
 -0.02516;1.10306;-23.61307;,
 -0.02516;-1.10306;-23.61307;,
 -0.02516;-1.10306;-23.61307;,
 -0.02516;-1.10306;-23.61307;,
 -0.02516;-1.10306;-23.61307;,
 -0.02516;-1.10306;-23.61307;,
 -0.02516;-1.10306;-23.61307;,
 -0.02516;-1.10306;-23.61307;,
 -0.02516;-1.10306;-23.61307;,
 1.91289;1.10306;-19.37674;,
 2.31669;1.10306;-19.20947;,
 2.31669;-1.10306;-19.20947;,
 1.91289;-1.10306;-19.37674;,
 2.48395;1.10306;-18.80567;,
 2.48395;-1.10306;-18.80567;,
 2.31669;1.10306;-18.40188;,
 2.31669;-1.10306;-18.40188;,
 1.91289;1.10306;-18.23460;,
 1.91289;-1.10306;-18.23460;,
 1.50909;1.10306;-18.40188;,
 1.50909;-1.10306;-18.40188;,
 1.34183;1.10306;-18.80567;,
 1.34183;-1.10306;-18.80567;,
 1.50909;1.10306;-19.20947;,
 1.50909;-1.10306;-19.20947;,
 1.91289;1.10306;-19.37674;,
 1.91289;-1.10306;-19.37674;,
 1.91289;1.10306;-18.80567;,
 1.91289;1.10306;-18.80567;,
 1.91289;1.10306;-18.80567;,
 1.91289;1.10306;-18.80567;,
 1.91289;1.10306;-18.80567;,
 1.91289;1.10306;-18.80567;,
 1.91289;1.10306;-18.80567;,
 1.91289;1.10306;-18.80567;,
 1.91289;-1.10306;-18.80567;,
 1.91289;-1.10306;-18.80567;,
 1.91289;-1.10306;-18.80567;,
 1.91289;-1.10306;-18.80567;,
 1.91289;-1.10306;-18.80567;,
 1.91289;-1.10306;-18.80567;,
 1.91289;-1.10306;-18.80567;,
 1.91289;-1.10306;-18.80567;,
 -1.94657;1.10306;-19.37674;,
 -1.54277;1.10306;-19.20947;,
 -1.54277;-1.10306;-19.20947;,
 -1.94657;-1.10306;-19.37674;,
 -1.37552;1.10306;-18.80567;,
 -1.37552;-1.10306;-18.80567;,
 -1.54277;1.10306;-18.40188;,
 -1.54277;-1.10306;-18.40188;,
 -1.94657;1.10306;-18.23460;,
 -1.94657;-1.10306;-18.23460;,
 -2.35037;1.10306;-18.40188;,
 -2.35037;-1.10306;-18.40188;,
 -2.51763;1.10306;-18.80567;,
 -2.51763;-1.10306;-18.80567;,
 -2.35037;1.10306;-19.20947;,
 -2.35037;-1.10306;-19.20947;,
 -1.94657;1.10306;-19.37674;,
 -1.94657;-1.10306;-19.37674;,
 -1.94657;1.10306;-18.80567;,
 -1.94657;1.10306;-18.80567;,
 -1.94657;1.10306;-18.80567;,
 -1.94657;1.10306;-18.80567;,
 -1.94657;1.10306;-18.80567;,
 -1.94657;1.10306;-18.80567;,
 -1.94657;1.10306;-18.80567;,
 -1.94657;1.10306;-18.80567;,
 -1.94657;-1.10306;-18.80567;,
 -1.94657;-1.10306;-18.80567;,
 -1.94657;-1.10306;-18.80567;,
 -1.94657;-1.10306;-18.80567;,
 -1.94657;-1.10306;-18.80567;,
 -1.94657;-1.10306;-18.80567;,
 -1.94657;-1.10306;-18.80567;,
 -1.94657;-1.10306;-18.80567;,
 -2.09151;1.10306;-30.31385;,
 -1.68771;1.10306;-30.14658;,
 -1.68771;-1.10306;-30.14658;,
 -2.09151;-1.10306;-30.31385;,
 -1.52045;1.10306;-29.74279;,
 -1.52045;-1.10306;-29.74279;,
 -1.68771;1.10306;-29.33899;,
 -1.68771;-1.10306;-29.33899;,
 -2.09151;1.10306;-29.17172;,
 -2.09151;-1.10306;-29.17172;,
 -2.49530;1.10306;-29.33899;,
 -2.49530;-1.10306;-29.33899;,
 -2.66256;1.10306;-29.74279;,
 -2.66256;-1.10306;-29.74279;,
 -2.49530;1.10306;-30.14658;,
 -2.49530;-1.10306;-30.14658;,
 -2.09151;1.10306;-30.31385;,
 -2.09151;-1.10306;-30.31385;,
 -2.09151;1.10306;-29.74279;,
 -2.09151;1.10306;-29.74279;,
 -2.09151;1.10306;-29.74279;,
 -2.09151;1.10306;-29.74279;,
 -2.09151;1.10306;-29.74279;,
 -2.09151;1.10306;-29.74279;,
 -2.09151;1.10306;-29.74279;,
 -2.09151;1.10306;-29.74279;,
 -2.09151;-1.10306;-29.74279;,
 -2.09151;-1.10306;-29.74279;,
 -2.09151;-1.10306;-29.74279;,
 -2.09151;-1.10306;-29.74279;,
 -2.09151;-1.10306;-29.74279;,
 -2.09151;-1.10306;-29.74279;,
 -2.09151;-1.10306;-29.74279;,
 -2.09151;-1.10306;-29.74279;,
 1.75381;1.10306;-30.31385;,
 2.15761;1.10306;-30.14658;,
 2.15761;-1.10306;-30.14658;,
 1.75381;-1.10306;-30.31385;,
 2.32487;1.10306;-29.74279;,
 2.32487;-1.10306;-29.74279;,
 2.15761;1.10306;-29.33899;,
 2.15761;-1.10306;-29.33899;,
 1.75381;1.10306;-29.17172;,
 1.75381;-1.10306;-29.17172;,
 1.35001;1.10306;-29.33899;,
 1.35001;-1.10306;-29.33899;,
 1.18275;1.10306;-29.74279;,
 1.18275;-1.10306;-29.74279;,
 1.35001;1.10306;-30.14658;,
 1.35001;-1.10306;-30.14658;,
 1.75381;1.10306;-30.31385;,
 1.75381;-1.10306;-30.31385;,
 1.75381;1.10306;-29.74279;,
 1.75381;1.10306;-29.74279;,
 1.75381;1.10306;-29.74279;,
 1.75381;1.10306;-29.74279;,
 1.75381;1.10306;-29.74279;,
 1.75381;1.10306;-29.74279;,
 1.75381;1.10306;-29.74279;,
 1.75381;1.10306;-29.74279;,
 1.75381;-1.10306;-29.74279;,
 1.75381;-1.10306;-29.74279;,
 1.75381;-1.10306;-29.74279;,
 1.75381;-1.10306;-29.74279;,
 1.75381;-1.10306;-29.74279;,
 1.75381;-1.10306;-29.74279;,
 1.75381;-1.10306;-29.74279;,
 1.75381;-1.10306;-29.74279;,
 -0.53309;1.10306;-36.57061;,
 -0.12929;1.10306;-36.40333;,
 -0.12929;-1.10306;-36.40333;,
 -0.53309;-1.10306;-36.57061;,
 0.03797;1.10306;-35.99954;,
 0.03797;-1.10306;-35.99954;,
 -0.12929;1.10306;-35.59574;,
 -0.12929;-1.10306;-35.59574;,
 -0.53309;1.10306;-35.42847;,
 -0.53309;-1.10306;-35.42847;,
 -0.93689;1.10306;-35.59574;,
 -0.93689;-1.10306;-35.59574;,
 -1.10415;1.10306;-35.99954;,
 -1.10415;-1.10306;-35.99954;,
 -0.93689;1.10306;-36.40333;,
 -0.93689;-1.10306;-36.40333;,
 -0.53309;1.10306;-36.57061;,
 -0.53309;-1.10306;-36.57061;,
 -0.53309;1.10306;-35.99954;,
 -0.53309;1.10306;-35.99954;,
 -0.53309;1.10306;-35.99954;,
 -0.53309;1.10306;-35.99954;,
 -0.53309;1.10306;-35.99954;,
 -0.53309;1.10306;-35.99954;,
 -0.53309;1.10306;-35.99954;,
 -0.53309;1.10306;-35.99954;,
 -0.53309;-1.10306;-35.99954;,
 -0.53309;-1.10306;-35.99954;,
 -0.53309;-1.10306;-35.99954;,
 -0.53309;-1.10306;-35.99954;,
 -0.53309;-1.10306;-35.99954;,
 -0.53309;-1.10306;-35.99954;,
 -0.53309;-1.10306;-35.99954;,
 -0.53309;-1.10306;-35.99954;,
 -2.58725;1.71941;-3.08793;,
 -0.44043;1.71941;-2.19869;,
 -0.44043;-1.71941;-2.19869;,
 -2.58725;-1.71941;-3.08793;,
 0.44881;1.71941;-0.05187;,
 0.44881;-1.71941;-0.05187;,
 -0.44043;1.71941;2.09496;,
 -0.44043;-1.71941;2.09496;,
 -2.58725;1.71941;2.98420;,
 -2.58725;-1.71941;2.98420;,
 -4.73407;1.71941;2.09496;,
 -4.73407;-1.71941;2.09496;,
 -5.62331;1.71941;-0.05187;,
 -5.62331;-1.71941;-0.05187;,
 -4.73407;1.71941;-2.19869;,
 -4.73407;-1.71941;-2.19869;,
 -2.58725;1.71941;-3.08793;,
 -2.58725;-1.71941;-3.08793;,
 -2.58725;1.71941;-0.05187;,
 -2.58725;1.71941;-0.05187;,
 -2.58725;1.71941;-0.05187;,
 -2.58725;1.71941;-0.05187;,
 -2.58725;1.71941;-0.05187;,
 -2.58725;1.71941;-0.05187;,
 -2.58725;1.71941;-0.05187;,
 -2.58725;1.71941;-0.05187;,
 -2.58725;-1.71941;-0.05187;,
 -2.58725;-1.71941;-0.05187;,
 -2.58725;-1.71941;-0.05187;,
 -2.58725;-1.71941;-0.05187;,
 -2.58725;-1.71941;-0.05187;,
 -2.58725;-1.71941;-0.05187;,
 -2.58725;-1.71941;-0.05187;,
 -2.58725;-1.71941;-0.05187;;
 
 273;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,0,3,9;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,15,5,4;,
 4;16,17,18,19;,
 4;16,19,20,21;,
 4;22,23,24,25;,
 4;22,25,26,27;,
 4;19,18,28,29;,
 4;19,29,30,20;,
 4;31,32,33,34;,
 4;31,34,35,36;,
 4;29,28,11,37;,
 4;29,37,13,30;,
 4;34,33,38,39;,
 4;34,39,40,35;,
 4;41,42,43,44;,
 4;41,44,45,46;,
 4;39,38,14,47;,
 4;39,47,10,40;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;54,55,56,57;,
 4;55,58,59,56;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 3;72,55,54;,
 3;73,58,55;,
 3;74,60,58;,
 3;75,62,60;,
 3;76,64,62;,
 3;77,66,64;,
 3;78,68,66;,
 3;79,70,68;,
 3;80,57,56;,
 3;81,56,59;,
 3;82,59,61;,
 3;83,61,63;,
 3;84,63,65;,
 3;85,65,67;,
 3;86,67,69;,
 3;87,69,71;,
 3;88,89,90;,
 4;88,91,92,89;,
 3;93,94,95;,
 4;96,89,92,97;,
 3;98,92,99;,
 3;100,101,102;,
 4;100,102,103,104;,
 4;105,88,90,106;,
 4;105,106,49,48;,
 4;105,48,51,107;,
 4;105,107,91,88;,
 4;108,93,95,109;,
 4;108,109,52,49;,
 4;110,96,97,111;,
 4;110,111,53,52;,
 4;112,103,101,113;,
 4;112,113,50,53;,
 4;114,98,99,115;,
 4;114,115,51,50;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;124,127,128,129;,
 4;130,131,132,133;,
 4;130,133,134,135;,
 4;136,137,138,139;,
 4;136,139,140,141;,
 4;142,143,144,145;,
 4;142,145,146,147;,
 4;148,124,129,149;,
 4;148,149,150,151;,
 4;148,151,152,153;,
 4;148,153,125,124;,
 4;154,155,156,157;,
 4;154,157,121,120;,
 4;158,116,119,159;,
 4;158,159,160,161;,
 4;162,163,164,165;,
 4;162,165,145,144;,
 4;165,164,166,167;,
 4;165,167,146,145;,
 4;168,138,137,169;,
 4;168,169,170,171;,
 4;172,171,173,174;,
 4;172,174,167,166;,
 4;175,150,149,176;,
 4;175,176,177,170;,
 4;174,173,178,179;,
 4;174,179,146,167;,
 4;176,149,129,180;,
 4;176,180,181,177;,
 4;179,178,182,183;,
 4;179,183,147,146;,
 4;180,129,128,184;,
 4;180,184,185,181;,
 4;186,182,185,187;,
 4;186,187,135,134;,
 4;188,189,190,191;,
 4;189,192,193,190;,
 4;192,194,195,193;,
 4;194,196,197,195;,
 4;196,198,199,197;,
 4;198,200,201,199;,
 4;200,202,203,201;,
 4;202,204,205,203;,
 3;206,189,188;,
 3;207,192,189;,
 3;208,194,192;,
 3;209,196,194;,
 3;210,198,196;,
 3;211,200,198;,
 3;212,202,200;,
 3;213,204,202;,
 3;214,191,190;,
 3;215,190,193;,
 3;216,193,195;,
 3;217,195,197;,
 3;218,197,199;,
 3;219,199,201;,
 3;220,201,203;,
 3;221,203,205;,
 4;222,223,224,225;,
 4;223,226,227,224;,
 4;226,228,229,227;,
 4;228,230,231,229;,
 4;230,232,233,231;,
 4;232,234,235,233;,
 4;234,236,237,235;,
 4;236,238,239,237;,
 3;240,223,222;,
 3;241,226,223;,
 3;242,228,226;,
 3;243,230,228;,
 3;244,232,230;,
 3;245,234,232;,
 3;246,236,234;,
 3;247,238,236;,
 3;248,225,224;,
 3;249,224,227;,
 3;250,227,229;,
 3;251,229,231;,
 3;252,231,233;,
 3;253,233,235;,
 3;254,235,237;,
 3;255,237,239;,
 4;256,257,258,259;,
 4;257,260,261,258;,
 4;260,262,263,261;,
 4;262,264,265,263;,
 4;264,266,267,265;,
 4;266,268,269,267;,
 4;268,270,271,269;,
 4;270,272,273,271;,
 3;274,257,256;,
 3;275,260,257;,
 3;276,262,260;,
 3;277,264,262;,
 3;278,266,264;,
 3;279,268,266;,
 3;280,270,268;,
 3;281,272,270;,
 3;282,259,258;,
 3;283,258,261;,
 3;284,261,263;,
 3;285,263,265;,
 3;286,265,267;,
 3;287,267,269;,
 3;288,269,271;,
 3;289,271,273;,
 4;290,291,292,293;,
 4;291,294,295,292;,
 4;294,296,297,295;,
 4;296,298,299,297;,
 4;298,300,301,299;,
 4;300,302,303,301;,
 4;302,304,305,303;,
 4;304,306,307,305;,
 3;308,291,290;,
 3;309,294,291;,
 3;310,296,294;,
 3;311,298,296;,
 3;312,300,298;,
 3;313,302,300;,
 3;314,304,302;,
 3;315,306,304;,
 3;316,293,292;,
 3;317,292,295;,
 3;318,295,297;,
 3;319,297,299;,
 3;320,299,301;,
 3;321,301,303;,
 3;322,303,305;,
 3;323,305,307;,
 4;324,325,326,327;,
 4;325,328,329,326;,
 4;328,330,331,329;,
 4;330,332,333,331;,
 4;332,334,335,333;,
 4;334,336,337,335;,
 4;336,338,339,337;,
 4;338,340,341,339;,
 3;342,325,324;,
 3;343,328,325;,
 3;344,330,328;,
 3;345,332,330;,
 3;346,334,332;,
 3;347,336,334;,
 3;348,338,336;,
 3;349,340,338;,
 3;350,327,326;,
 3;351,326,329;,
 3;352,329,331;,
 3;353,331,333;,
 3;354,333,335;,
 3;355,335,337;,
 3;356,337,339;,
 3;357,339,341;,
 4;358,359,360,361;,
 4;359,362,363,360;,
 4;362,364,365,363;,
 4;364,366,367,365;,
 4;366,368,369,367;,
 4;368,370,371,369;,
 4;370,372,373,371;,
 4;372,374,375,373;,
 3;376,359,358;,
 3;377,362,359;,
 3;378,364,362;,
 3;379,366,364;,
 3;380,368,366;,
 3;381,370,368;,
 3;382,372,370;,
 3;383,374,372;,
 3;384,361,360;,
 3;385,360,363;,
 3;386,363,365;,
 3;387,365,367;,
 3;388,367,369;,
 3;389,369,371;,
 3;390,371,373;,
 3;391,373,375;,
 4;392,393,394,395;,
 4;393,396,397,394;,
 4;396,398,399,397;,
 4;398,400,401,399;,
 4;400,402,403,401;,
 4;402,404,405,403;,
 4;404,406,407,405;,
 4;406,408,409,407;,
 3;410,393,392;,
 3;411,396,393;,
 3;412,398,396;,
 3;413,400,398;,
 3;414,402,400;,
 3;415,404,402;,
 3;416,406,404;,
 3;417,408,406;,
 3;418,395,394;,
 3;419,394,397;,
 3;420,397,399;,
 3;421,399,401;,
 3;422,401,403;,
 3;423,403,405;,
 3;424,405,407;,
 3;425,407,409;;
 
 MeshMaterialList {
  7;
  273;
  1,
  0,
  1,
  1,
  0,
  0,
  1,
  0,
  6,
  0,
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  6,
  6,
  0,
  1,
  3,
  3,
  3,
  6,
  6,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  4,
  4,
  4,
  3,
  4,
  6,
  4,
  4,
  3,
  0,
  4,
  4,
  3,
  3,
  1,
  4,
  3,
  4,
  3,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\479673fd194cff95abe42d0780bb86fe_t.jpeg";
   }
  }
  Material {
   0.495686;0.495686;0.495686;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\479673fd194cff95abe42d0780bb86fe_t.jpeg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.357647;0.357647;0.357647;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\metal_00010.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\download.png";
   }
  }
  Material {
   0.241600;0.241600;0.241600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\OC\\Downloads\\479673fd194cff95abe42d0780bb86fe_t.jpeg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  103;
  -1.000000;0.000000;0.000000;,
  0.649273;0.000000;-0.760555;,
  1.000000;0.000000;0.000000;,
  0.947240;0.000000;-0.320525;,
  0.996147;0.000000;-0.087695;,
  0.023201;0.999694;-0.008580;,
  0.013508;0.999898;-0.004647;,
  0.323034;0.000000;-0.946387;,
  0.003952;0.999992;-0.000357;,
  -0.013508;-0.999898;0.004647;,
  0.004087;0.999992;0.000000;,
  -0.003952;-0.999992;0.000357;,
  -0.036172;0.000000;0.999346;,
  0.000000;1.000000;0.000000;,
  0.027017;0.999592;-0.009293;,
  0.046389;0.998776;-0.017155;,
  0.332031;0.000000;-0.943269;,
  0.007904;0.999969;-0.000714;,
  -0.023202;-0.999694;0.008580;,
  -0.046389;-0.998776;0.017155;,
  -0.027017;-0.999592;0.009294;,
  0.000000;-1.000000;-0.000000;,
  0.008175;0.999967;0.000000;,
  -0.007904;-0.999969;0.000714;,
  0.000000;0.000000;1.000000;,
  -0.072298;0.000000;0.997383;,
  -0.008175;-0.999967;0.000000;,
  -0.004087;-0.999992;0.000000;,
  0.000000;1.000000;0.000000;,
  0.923879;0.000000;-0.382684;,
  1.000000;0.000000;0.000000;,
  0.923879;0.000000;0.382684;,
  -0.707106;0.000000;-0.707107;,
  0.000000;0.000000;-1.000000;,
  0.707106;0.000000;-0.707108;,
  0.707106;0.000000;0.707108;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  -0.707107;-0.000000;-0.707106;,
  -0.707107;0.000000;0.707107;,
  -0.707107;-0.000000;-0.707106;,
  -0.707109;0.000000;0.707104;,
  -0.707106;-0.000000;0.707107;,
  -0.707107;-0.000000;-0.707107;,
  -0.707112;0.000000;0.707102;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.981123;0.000000;-0.193386;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.999964;0.000000;0.008473;,
  0.979449;0.000000;-0.201692;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.707114;0.000000;-0.707099;,
  1.000000;0.000000;0.000004;,
  0.707119;0.000000;0.707094;,
  0.000000;0.000000;1.000000;,
  -0.707119;0.000000;0.707094;,
  -1.000000;0.000000;0.000004;,
  -0.707114;0.000000;-0.707100;,
  0.000000;-1.000000;-0.000000;,
  -0.707119;0.000000;0.707094;,
  -1.000000;0.000000;0.000004;,
  -0.707114;0.000000;-0.707100;,
  0.707122;0.000000;-0.707092;,
  1.000000;0.000000;0.000004;,
  0.707127;0.000000;0.707087;,
  -1.000000;0.000000;0.000004;,
  -0.707114;0.000000;-0.707099;,
  -0.000004;0.000000;-1.000000;,
  0.707111;0.000000;-0.707102;,
  1.000000;0.000000;-0.000004;,
  0.707114;0.000000;0.707099;,
  -0.000004;0.000000;1.000000;,
  -0.707117;0.000000;0.707097;,
  -1.000000;0.000000;-0.000004;,
  -0.707114;0.000000;-0.707099;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.707114;0.000000;0.707099;,
  -1.000000;0.000000;-0.000004;,
  -0.707111;0.000000;-0.707102;,
  -0.000000;0.000000;-1.000000;,
  0.707118;0.000000;-0.707096;,
  0.707114;0.000000;0.707100;,
  0.000000;0.000000;1.000000;,
  -0.707118;0.000000;-0.707096;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;-0.000001;,
  0.707107;0.000000;0.707106;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707106;,
  -1.000000;0.000000;-0.000001;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;;
  273;
  4;0,0,0,0;,
  4;3,3,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;4,2,2,4;,
  4;4,4,3,3;,
  4;5,13,13,6;,
  4;5,6,14,15;,
  4;7,1,1,7;,
  4;7,7,16,16;,
  4;6,13,13,8;,
  4;6,8,17,14;,
  4;18,19,20,9;,
  4;18,9,21,21;,
  4;8,13,13,10;,
  4;8,10,22,17;,
  4;9,20,23,11;,
  4;9,11,21,21;,
  4;12,24,24,12;,
  4;12,12,25,25;,
  4;11,23,26,27;,
  4;11,27,21,21;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;33,34,34,33;,
  4;34,30,30,34;,
  4;30,35,35,30;,
  4;35,36,36,35;,
  4;36,37,37,36;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,33,33,39;,
  3;28,28,28;,
  3;28,28,28;,
  3;28,28,28;,
  3;28,28,28;,
  3;28,28,28;,
  3;28,28,28;,
  3;28,28,28;,
  3;28,28,28;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;28,28,28;,
  4;41,41,32,32;,
  3;28,28,28;,
  4;42,45,45,42;,
  3;40,40,40;,
  3;40,40,40;,
  4;40,40,40,40;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;43,46,46,43;,
  4;43,43,41,41;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;44,42,42,44;,
  4;44,44,47,47;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;50,50,50,50;,
  4;48,48,48,48;,
  4;51,51,51,51;,
  4;51,51,51,51;,
  4;53,53,53,53;,
  4;53,53,53,53;,
  4;55,52,52,55;,
  4;55,55,49,49;,
  4;54,54,54,54;,
  4;54,54,54,54;,
  4;51,51,51,51;,
  4;51,51,51,51;,
  4;51,51,51,51;,
  4;51,51,51,51;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;50,50,50,50;,
  4;50,50,50,50;,
  4;54,54,54,54;,
  4;54,54,54,54;,
  4;54,54,54,54;,
  4;54,54,54,54;,
  4;56,52,52,56;,
  4;56,56,49,49;,
  4;54,54,54,54;,
  4;54,54,54,54;,
  4;51,51,51,51;,
  4;51,51,51,51;,
  4;54,54,54,54;,
  4;54,54,54,54;,
  4;51,51,51,51;,
  4;51,51,51,51;,
  4;54,54,54,54;,
  4;54,54,54,54;,
  4;51,51,51,51;,
  4;51,51,51,51;,
  4;53,53,53,53;,
  4;53,53,53,53;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;62,63,63,62;,
  4;63,64,64,63;,
  4;64,65,65,64;,
  4;65,58,58,65;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;62,67,67,62;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,58,58,69;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  4;58,70,70,58;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,62,62,72;,
  4;62,63,63,62;,
  4;63,73,73,63;,
  4;73,74,74,73;,
  4;74,58,58,74;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,81,81,80;,
  4;81,82,82,81;,
  4;82,75,75,82;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  4;83,76,76,83;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,84,84,78;,
  4;84,85,85,84;,
  4;85,86,86,85;,
  4;86,87,87,86;,
  4;87,83,83,87;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  4;88,89,89,88;,
  4;89,77,77,89;,
  4;77,90,90,77;,
  4;90,91,91,90;,
  4;91,85,85,91;,
  4;85,86,86,85;,
  4;86,92,92,86;,
  4;92,88,88,92;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  4;94,95,95,94;,
  4;95,96,96,95;,
  4;96,97,97,96;,
  4;97,98,98,97;,
  4;98,99,99,98;,
  4;99,100,100,99;,
  4;100,101,101,100;,
  4;101,94,94,101;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;102,102,102;,
  3;102,102,102;,
  3;102,102,102;,
  3;102,102,102;,
  3;102,102,102;,
  3;102,102,102;,
  3;102,102,102;,
  3;102,102,102;;
 }
 MeshTextureCoords {
  426;
  0.783150;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.783150;1.000000;,
  0.216850;0.000000;,
  0.216850;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.519500;0.000000;,
  0.519500;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.480500;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.480500;1.000000;,
  0.867230;1.000000;,
  0.000000;1.000000;,
  0.000000;0.783150;,
  0.867230;0.783150;,
  1.000000;0.783150;,
  1.000000;1.000000;,
  0.867230;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.867230;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.519500;,
  0.867230;0.519500;,
  1.000000;0.519500;,
  0.867230;0.000000;,
  1.000000;0.000000;,
  1.000000;0.216850;,
  0.867230;0.216850;,
  0.000000;0.216850;,
  0.000000;0.000000;,
  0.867230;0.000000;,
  1.000000;0.480500;,
  0.867230;0.480500;,
  0.000000;0.480500;,
  0.132770;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.132770;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.867230;1.000000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.125000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.149160;0.000000;,
  0.187500;0.000000;,
  0.226690;0.000000;,
  0.146220;1.000000;,
  0.187500;1.000000;,
  0.273490;0.000000;,
  0.312500;0.000000;,
  0.349530;0.000000;,
  0.298600;0.000000;,
  0.296450;1.000000;,
  0.225650;1.000000;,
  0.146730;1.000000;,
  0.274350;1.000000;,
  0.274240;1.000000;,
  0.274630;1.000000;,
  0.348820;1.000000;,
  0.312500;1.000000;,
  0.129420;0.000000;,
  0.245740;0.000000;,
  0.128880;1.000000;,
  0.254480;0.000000;,
  0.370140;0.000000;,
  0.360410;0.000000;,
  0.360000;1.000000;,
  0.370000;1.000000;,
  0.254630;1.000000;,
  0.245400;1.000000;,
  0.129100;1.000000;,
  0.831040;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.831040;1.000000;,
  0.168960;0.000000;,
  0.168960;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.168960;0.615680;,
  0.168960;1.000000;,
  0.000000;1.000000;,
  0.000000;0.615680;,
  0.000000;0.122280;,
  0.168960;0.122280;,
  0.615680;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.615680;1.000000;,
  0.122280;1.000000;,
  0.122280;0.000000;,
  0.384320;0.000000;,
  0.877720;0.000000;,
  0.877720;1.000000;,
  0.384320;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.384320;,
  0.000000;0.000000;,
  0.168960;0.000000;,
  0.168960;0.384320;,
  0.168960;0.877720;,
  0.000000;0.877720;,
  0.809690;0.615680;,
  0.809690;0.122280;,
  1.000000;0.122280;,
  1.000000;0.615680;,
  1.000000;1.000000;,
  0.809690;1.000000;,
  0.809690;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.809690;1.000000;,
  0.190310;0.000000;,
  0.190310;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.809690;0.000000;,
  1.000000;0.000000;,
  1.000000;0.384320;,
  0.809690;0.384320;,
  1.000000;0.877720;,
  0.809690;0.877720;,
  0.930790;1.000000;,
  0.930790;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.930790;,
  0.809690;1.000000;,
  0.809690;0.930790;,
  1.000000;0.069210;,
  0.809690;0.069210;,
  0.809690;0.000000;,
  0.168960;1.000000;,
  0.168960;0.930790;,
  0.168960;0.069210;,
  0.168960;0.000000;,
  0.000000;1.000000;,
  0.000000;0.930790;,
  0.000000;0.069210;,
  0.000000;0.000000;,
  0.069210;1.000000;,
  0.069210;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}