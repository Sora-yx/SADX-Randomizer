#pragma once


typedef unsigned short  word;


struct SubtitleThing { //idk, ask SADX, most of the variables here are incorrect, but using this struct with the function does work fine in game... so... yeah.
    char field_0;
    char gap1;
    word px;
    word py;
    word field_6;
    word field_8;
    word sx;
    word sy;
    word width;
    word height;
    word field_12;
    word field_14;
    word field_16;
    word field_18;
    word field_1A;
    NJS_BGRA colorA;
    NJS_COLOR colorB;
    float scale;
    NJS_TEXINFO data_or_d3dtexture;
    char gbix;
    NJS_TEXLIST tlist;
    NJS_TEXNAME texname;
    float flags;
};


FunctionPointer(void, DoSomethingRelatedToText, (SubtitleThing* a1, const char* a2), 0x40e570);
void DoSomethingRelatedToText_r(SubtitleThing* a1, const char* a2);
void Init_Subtitles();
