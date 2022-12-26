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
 142;
 3.74990;38.72198;69.76170;,
 27.91300;15.40183;18.39346;,
 3.81866;38.60036;11.80042;,
 3.81866;38.60036;11.80042;,
 27.91300;15.40183;18.39346;,
 3.74990;38.72198;69.76170;,
 -19.48490;15.32100;18.10206;,
 3.74990;38.72198;69.76170;,
 -19.48490;15.32100;18.10206;,
 3.88269;1.45147;-31.90998;,
 3.81866;38.60036;11.80042;,
 -19.48490;15.32100;18.10206;,
 3.88269;1.45147;-31.90998;,
 3.88269;1.45147;-31.90998;,
 27.91300;15.40183;18.39346;,
 3.81866;38.60036;11.80042;,
 3.81866;38.60036;11.80042;,
 27.91300;15.40183;18.39346;,
 3.88269;1.45147;-31.90998;,
 40.92560;0.20047;70.06571;,
 11.99631;-20.82950;20.19371;,
 40.79009;-4.38076;12.28573;,
 40.79009;-4.38076;12.28573;,
 11.99631;-20.82950;20.19371;,
 40.92560;0.20047;70.06571;,
 24.58494;24.70227;16.31798;,
 40.92560;0.20047;70.06571;,
 24.58494;24.70227;16.31798;,
 4.97511;2.02524;-32.06399;,
 40.79009;-4.38076;12.28573;,
 24.58494;24.70227;16.31798;,
 4.97511;2.02524;-32.06399;,
 4.97511;2.02524;-32.06399;,
 11.99631;-20.82950;20.19371;,
 40.79009;-4.38076;12.28573;,
 40.79009;-4.38076;12.28573;,
 11.99631;-20.82950;20.19371;,
 4.97511;2.02524;-32.06399;,
 33.37249;-38.02347;59.29132;,
 -8.40479;-18.40560;18.84159;,
 16.63728;-36.00885;3.83492;,
 16.63728;-36.00885;3.83492;,
 -8.40479;-18.40560;18.84159;,
 33.37249;-38.02347;59.29132;,
 36.04255;-8.70978;5.53484;,
 33.37249;-38.02347;59.29132;,
 36.04255;-8.70978;5.53484;,
 -2.84936;1.77553;-34.67818;,
 16.63728;-36.00885;3.83492;,
 36.04255;-8.70978;5.53484;,
 -2.84936;1.77553;-34.67818;,
 -2.84936;1.77553;-34.67818;,
 -8.40479;-18.40560;18.84159;,
 16.63728;-36.00885;3.83492;,
 16.63728;-36.00885;3.83492;,
 -8.40479;-18.40560;18.84159;,
 -2.84936;1.77553;-34.67818;,
 -25.86508;-41.92931;59.34487;,
 -24.43002;2.51983;17.05301;,
 -27.68382;-28.37751;3.01920;,
 -27.68382;-28.37751;3.01920;,
 -24.43002;2.51983;17.05301;,
 -25.86508;-41.92931;59.34487;,
 5.24049;-33.12731;7.27615;,
 -25.86508;-41.92931;59.34487;,
 5.24049;-33.12731;7.27615;,
 -0.15564;4.60470;-34.99421;,
 -27.68382;-28.37751;3.01920;,
 5.24049;-33.12731;7.27615;,
 -0.15564;4.60470;-34.99421;,
 -0.15564;4.60470;-34.99421;,
 -24.43002;2.51983;17.05301;,
 -27.68382;-28.37751;3.01920;,
 -27.68382;-28.37751;3.01920;,
 -24.43002;2.51983;17.05301;,
 -0.15564;4.60470;-34.99421;,
 -49.74445;6.52058;59.43915;,
 -10.37385;25.75883;16.47131;,
 -38.29336;11.71099;2.85751;,
 -38.29336;11.71099;2.85751;,
 -10.37385;25.75883;16.47131;,
 -49.74445;6.52058;59.43915;,
 -25.37870;-18.59788;9.12451;,
 -49.74445;6.52058;59.43915;,
 -25.37870;-18.59788;9.12451;,
 4.70947;2.99805;-34.09488;,
 -38.29336;11.71099;2.85751;,
 -25.37870;-18.59788;9.12451;,
 4.70947;2.99805;-34.09488;,
 4.70947;2.99805;-34.09488;,
 -10.37385;25.75883;16.47131;,
 -38.29336;11.71099;2.85751;,
 -38.29336;11.71099;2.85751;,
 -10.37385;25.75883;16.47131;,
 4.70947;2.99805;-34.09488;,
 3.73401;0.11321;-22.23054;,
 11.85155;4.79988;-24.49240;,
 3.73401;9.48653;-24.49240;,
 3.73401;0.11321;-22.23054;,
 11.85155;-4.57343;-24.49240;,
 3.73401;0.11321;-22.23054;,
 3.73400;-9.26012;-24.49240;,
 3.73401;0.11321;-22.23054;,
 -4.38353;-4.57343;-24.49240;,
 3.73401;0.11321;-22.23054;,
 -4.38353;4.79988;-24.49240;,
 3.73401;0.11321;-22.23054;,
 3.73401;9.48653;-24.49240;,
 17.79401;8.23074;-30.67181;,
 3.73401;16.34829;-30.67181;,
 17.79401;-8.00433;-30.67181;,
 3.73400;-16.12187;-30.67181;,
 -10.32598;-8.00433;-30.67181;,
 -10.32598;8.23074;-30.67181;,
 3.73401;16.34829;-30.67181;,
 19.96909;9.48653;-39.11305;,
 3.73401;18.85988;-39.11305;,
 19.96909;-9.26012;-39.11305;,
 3.73400;-18.63344;-39.11305;,
 -12.50107;-9.26012;-39.11305;,
 -12.50107;9.48653;-39.11305;,
 3.73401;18.85988;-39.11305;,
 17.79401;8.23074;-47.55428;,
 3.73401;16.34829;-47.55428;,
 17.79401;-8.00433;-47.55428;,
 3.73400;-16.12187;-47.55428;,
 -10.32598;-8.00433;-47.55428;,
 -10.32597;8.23074;-47.55428;,
 3.73401;16.34829;-47.55428;,
 11.85155;4.79988;-53.73372;,
 3.73401;9.48653;-53.73372;,
 11.85155;-4.57343;-53.73372;,
 3.73400;-9.26012;-53.73372;,
 -4.38353;-4.57343;-53.73372;,
 -4.38353;4.79988;-53.73372;,
 3.73401;9.48653;-53.73372;,
 3.73401;0.11321;-55.99554;,
 3.73401;0.11321;-55.99554;,
 3.73401;0.11321;-55.99554;,
 3.73401;0.11321;-55.99554;,
 3.73401;0.11321;-55.99554;,
 3.73401;0.11321;-55.99554;;
 
 76;
 3;0,1,2;,
 3;3,4,5;,
 3;6,0,2;,
 3;3,7,8;,
 3;9,6,10;,
 3;10,11,12;,
 3;13,14,15;,
 3;16,17,18;,
 3;19,20,21;,
 3;22,23,24;,
 3;25,19,21;,
 3;22,26,27;,
 3;28,25,29;,
 3;29,30,31;,
 3;32,33,34;,
 3;35,36,37;,
 3;38,39,40;,
 3;41,42,43;,
 3;44,38,40;,
 3;41,45,46;,
 3;47,44,48;,
 3;48,49,50;,
 3;51,52,53;,
 3;54,55,56;,
 3;57,58,59;,
 3;60,61,62;,
 3;63,57,59;,
 3;60,64,65;,
 3;66,63,67;,
 3;67,68,69;,
 3;70,71,72;,
 3;73,74,75;,
 3;76,77,78;,
 3;79,80,81;,
 3;82,76,78;,
 3;79,83,84;,
 3;85,82,86;,
 3;86,87,88;,
 3;89,90,91;,
 3;92,93,94;,
 3;95,96,97;,
 3;98,99,96;,
 3;100,101,99;,
 3;102,103,101;,
 3;104,105,103;,
 3;106,107,105;,
 4;97,96,108,109;,
 4;96,99,110,108;,
 4;99,101,111,110;,
 4;101,103,112,111;,
 4;103,105,113,112;,
 4;105,107,114,113;,
 4;109,108,115,116;,
 4;108,110,117,115;,
 4;110,111,118,117;,
 4;111,112,119,118;,
 4;112,113,120,119;,
 4;113,114,121,120;,
 4;116,115,122,123;,
 4;115,117,124,122;,
 4;117,118,125,124;,
 4;118,119,126,125;,
 4;119,120,127,126;,
 4;120,121,128,127;,
 4;123,122,129,130;,
 4;122,124,131,129;,
 4;124,125,132,131;,
 4;125,126,133,132;,
 4;126,127,134,133;,
 4;127,128,135,134;,
 3;130,129,136;,
 3;129,131,137;,
 3;131,132,138;,
 3;132,133,139;,
 3;133,134,140;,
 3;134,135,141;;
 
 MeshMaterialList {
  6;
  76;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.144000;0.144000;0.144000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.009600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.445600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.765600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.160000;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.800000;0.787200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  92;
  -0.717533;0.651818;-0.245520;,
  0.706309;0.663291;-0.247333;,
  -0.683300;0.555858;-0.473417;,
  0.693686;0.720277;-0.000688;,
  -0.706309;-0.663291;0.247333;,
  -0.693686;-0.720277;0.000688;,
  -0.707052;0.707158;-0.002323;,
  0.717533;-0.651818;0.245520;,
  0.707052;-0.707158;0.002323;,
  0.683300;-0.555858;0.473417;,
  -0.673558;-0.563694;0.478089;,
  0.673558;0.563694;-0.478089;,
  0.819862;0.496391;-0.285345;,
  0.450413;-0.874639;-0.179262;,
  0.718244;0.471189;-0.511964;,
  0.508701;-0.858343;0.066863;,
  -0.450413;0.874639;0.179262;,
  -0.508701;0.858343;-0.066863;,
  0.870389;0.490660;-0.040944;,
  -0.819862;-0.496391;0.285345;,
  -0.870389;-0.490660;0.040944;,
  -0.718244;-0.471189;0.511964;,
  -0.363191;0.834747;0.413871;,
  0.363191;-0.834747;-0.413871;,
  0.724412;-0.484398;-0.490496;,
  -0.612162;-0.784168;-0.101681;,
  0.609029;-0.389913;-0.690689;,
  -0.518914;-0.845508;0.125878;,
  0.612162;0.784168;0.101681;,
  0.518914;0.845508;-0.125878;,
  0.794651;-0.548696;-0.259737;,
  -0.724412;0.484398;0.490496;,
  -0.794651;0.548696;0.259737;,
  -0.609029;0.389913;0.690689;,
  0.666084;0.672453;0.322708;,
  -0.666084;-0.672453;-0.322708;,
  -0.068030;-0.884766;-0.461043;,
  -0.966738;0.182977;-0.178707;,
  -0.021920;-0.747229;-0.664205;,
  -0.995345;0.081334;0.051708;,
  0.966738;-0.182977;0.178707;,
  0.995345;-0.081334;-0.051708;,
  -0.109900;-0.967167;-0.229149;,
  0.068030;0.884766;0.461043;,
  0.109900;0.967167;0.229149;,
  0.021920;0.747229;0.664205;,
  0.876028;-0.272866;0.397642;,
  -0.876028;0.272866;-0.397642;,
  -0.785645;-0.427280;-0.447430;,
  -0.341218;0.909238;-0.238447;,
  -0.641233;-0.407654;-0.650106;,
  -0.446249;0.894871;-0.008223;,
  0.341218;-0.909238;0.238447;,
  0.446249;-0.894871;0.008223;,
  -0.881097;-0.420280;-0.216871;,
  0.785645;0.427280;0.447430;,
  0.881097;0.420280;0.216871;,
  0.641233;0.407654;0.650106;,
  0.214267;-0.865194;0.453353;,
  -0.214267;0.865194;-0.453353;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.459377;0.888242;,
  0.397831;0.229688;0.888242;,
  0.397831;-0.229688;0.888242;,
  -0.000000;-0.459376;0.888242;,
  -0.397832;-0.229688;0.888242;,
  -0.397831;0.229688;0.888242;,
  -0.000000;0.840585;0.541679;,
  0.727968;0.420293;0.541679;,
  0.727968;-0.420293;0.541679;,
  -0.000000;-0.840585;0.541679;,
  -0.727968;-0.420292;0.541679;,
  -0.727968;0.420293;0.541679;,
  -0.000000;1.000000;-0.000000;,
  0.866026;0.500000;-0.000000;,
  0.866025;-0.500000;-0.000000;,
  -0.000000;-1.000000;-0.000000;,
  -0.866025;-0.500000;-0.000000;,
  -0.866026;0.500000;-0.000001;,
  -0.000000;0.840586;-0.541678;,
  0.727969;0.420293;-0.541678;,
  0.727969;-0.420293;-0.541678;,
  -0.000000;-0.840586;-0.541678;,
  -0.727969;-0.420293;-0.541678;,
  -0.727969;0.420293;-0.541678;,
  -0.000000;0.459376;-0.888242;,
  0.397831;0.229688;-0.888242;,
  0.397831;-0.229688;-0.888242;,
  -0.000000;-0.459375;-0.888242;,
  -0.397831;-0.229687;-0.888242;,
  -0.397831;0.229688;-0.888242;,
  -0.000000;0.000000;-1.000000;;
  76;
  3;3,1,1;,
  3;4,4,5;,
  3;0,6,0;,
  3;7,8,7;,
  3;2,0,0;,
  3;7,7,9;,
  3;10,4,4;,
  3;1,1,11;,
  3;15,13,13;,
  3;16,16,17;,
  3;12,18,12;,
  3;19,20,19;,
  3;14,12,12;,
  3;19,19,21;,
  3;22,16,16;,
  3;13,13,23;,
  3;27,25,25;,
  3;28,28,29;,
  3;24,30,24;,
  3;31,32,31;,
  3;26,24,24;,
  3;31,31,33;,
  3;34,28,28;,
  3;25,25,35;,
  3;39,37,37;,
  3;40,40,41;,
  3;36,42,36;,
  3;43,44,43;,
  3;38,36,36;,
  3;43,43,45;,
  3;46,40,40;,
  3;37,37,47;,
  3;51,49,49;,
  3;52,52,53;,
  3;48,54,48;,
  3;55,56,55;,
  3;50,48,48;,
  3;55,55,57;,
  3;58,52,52;,
  3;49,49,59;,
  3;60,62,61;,
  3;60,63,62;,
  3;60,64,63;,
  3;60,65,64;,
  3;60,66,65;,
  3;60,61,66;,
  4;61,62,68,67;,
  4;62,63,69,68;,
  4;63,64,70,69;,
  4;64,65,71,70;,
  4;65,66,72,71;,
  4;66,61,67,72;,
  4;67,68,74,73;,
  4;68,69,75,74;,
  4;69,70,76,75;,
  4;70,71,77,76;,
  4;71,72,78,77;,
  4;72,67,73,78;,
  4;73,74,80,79;,
  4;74,75,81,80;,
  4;75,76,82,81;,
  4;76,77,83,82;,
  4;77,78,84,83;,
  4;78,73,79,84;,
  4;79,80,86,85;,
  4;80,81,87,86;,
  4;81,82,88,87;,
  4;82,83,89,88;,
  4;83,84,90,89;,
  4;84,79,85,90;,
  3;85,86,91;,
  3;86,87,91;,
  3;87,88,91;,
  3;88,89,91;,
  3;89,90,91;,
  3;90,85,91;;
 }
 MeshTextureCoords {
  142;
  0.245100;0.000000;,
  0.500000;0.258180;,
  0.491660;0.517780;,
  0.246540;0.240610;,
  0.746540;0.481930;,
  0.491630;1.000000;,
  0.000000;0.259580;,
  0.492350;0.740610;,
  0.000000;0.479840;,
  0.246500;0.500000;,
  0.000000;0.000000;,
  0.000000;0.239920;,
  0.494430;0.000000;,
  0.247210;0.000000;,
  0.500000;0.241320;,
  0.493080;0.481220;,
  0.245830;0.258890;,
  0.745830;0.517060;,
  0.493010;1.000000;,
  0.245100;0.000000;,
  0.500000;0.258180;,
  0.491660;0.517780;,
  0.246540;0.240610;,
  0.746540;0.481930;,
  0.491630;1.000000;,
  0.000000;0.259580;,
  0.492350;0.740610;,
  0.000000;0.479840;,
  0.246500;0.500000;,
  0.000000;0.000000;,
  0.000000;0.239920;,
  0.494430;0.000000;,
  0.247210;0.000000;,
  0.500000;0.241320;,
  0.493080;0.481220;,
  0.245830;0.258890;,
  0.745830;0.517060;,
  0.493010;1.000000;,
  0.245100;0.000000;,
  0.500000;0.258180;,
  0.491660;0.517780;,
  0.246540;0.240610;,
  0.746540;0.481930;,
  0.491630;1.000000;,
  0.000000;0.259580;,
  0.492350;0.740610;,
  0.000000;0.479840;,
  0.246500;0.500000;,
  0.000000;0.000000;,
  0.000000;0.239920;,
  0.494430;0.000000;,
  0.247210;0.000000;,
  0.500000;0.241320;,
  0.493080;0.481220;,
  0.245830;0.258890;,
  0.745830;0.517060;,
  0.493010;1.000000;,
  0.245100;0.000000;,
  0.500000;0.258180;,
  0.491660;0.517780;,
  0.246540;0.240610;,
  0.746540;0.481930;,
  0.491630;1.000000;,
  0.000000;0.259580;,
  0.492350;0.740610;,
  0.000000;0.479840;,
  0.246500;0.500000;,
  0.000000;0.000000;,
  0.000000;0.239920;,
  0.494430;0.000000;,
  0.247210;0.000000;,
  0.500000;0.241320;,
  0.493080;0.481220;,
  0.245830;0.258890;,
  0.745830;0.517060;,
  0.493010;1.000000;,
  0.245100;0.000000;,
  0.500000;0.258180;,
  0.491660;0.517780;,
  0.246540;0.240610;,
  0.746540;0.481930;,
  0.491630;1.000000;,
  0.000000;0.259580;,
  0.492350;0.740610;,
  0.000000;0.479840;,
  0.246500;0.500000;,
  0.000000;0.000000;,
  0.000000;0.239920;,
  0.494430;0.000000;,
  0.247210;0.000000;,
  0.500000;0.241320;,
  0.493080;0.481220;,
  0.245830;0.258890;,
  0.745830;0.517060;,
  0.493010;1.000000;,
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;;
 }
}